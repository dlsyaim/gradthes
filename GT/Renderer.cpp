#include "StdAfx.h"

#include <windows.h>
#include <GL/glut.h>
#include <vector>

#include "Renderer.h"
#include "XMLReader.h"
#include "Util.h"
#include "DirectionalGyro.h"
#include "Terrain.h"
#include "GTView.h"
#include "Scene.h"

#ifndef PI
#define PI 3.14159265359
#endif

#ifndef ANGLE_LABEL_WIDTH 
#define ANGLE_LABEL_WIDTH 65.0f
#endif

#ifndef ANGLE_VALUE_WIDTH
#define ANGLE_VALUE_WIDTH 50.0f
#endif

#ifndef RATE_LABEL_WIDTH
#define RATE_LABEL_WIDTH 25.0f
#endif

#ifndef RATE_VALUE_WIDTH
#define RATE_VALUE_WIDTH 25.0f
#endif

#ifndef UNIT_WIDTH
#define UNIT_WIDTH 100.0f
#endif

#ifndef LETTER_WIDTH
#define LETTER_WIDTH 20.0f
#endif

#define LEFT_MARGIN 2.0f
#define TOP_MARGIN 20.0f



//#define RADIAN_TO_ANGLE()

Renderer::Renderer(void):length(0)
{	
}

Renderer::Renderer(int _length):length(_length)
{
	// Create panel.
	panel = new Panel();

	// Create and initialize the camera
	camera = new CCamera();

	// Used to store the nine flight state variable.
	stat = new double[length + 1];
	memset(stat, 0.0, (length + 1) * sizeof(double));

	// Default do not use multiport
	isMultiport = FALSE;

	// Setup aircraft mode.
	aircraft = new Aircraft();	

	// Initialize the illumination and material
	initializeIlluminationAndMaterial();

	// Initial path is empty
	pPath = NULL;

	// Default is FALSE
	selectedPoint = NULL;
	// Default is none
	navi = -1;

	// Initialize
	qobj = NULL;
}

// Load configuration.
BOOL Renderer::loadConfiguration()
{
	// Load panel configuration.
	XMLReader *xmlReader = new XMLReader();
	xmlReader->initializeParser();
	xmlReader->loadPanel("..\\Instruments\\generic_trans_mini_Panel.xml", panel);
	delete xmlReader;

	aircraft->loadAircraft("..\\meshes\\bi_plane.wrl");	

	return TRUE;
}

Renderer::~Renderer(void)
{		
	if (stat)
		delete[] stat;
	if (panel)
		delete panel;
	if (camera)
		delete camera;
	if (aircraft)
	    delete aircraft;

	if (qobj)
		gluDeleteQuadric(qobj);
}

/*
 * Draw funtions with drawing instruments
 */
void Renderer::draw(void)
{
	if (!panel)
		return;

	/*
	 * First when we draw the text, we use the gluOrtho2D
	 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, lpRect->right, 0, lpRect->bottom);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera->Look();

	// Draw fonts
	drawFonts();

	/*
	 * Then when we draw the 3-D model , we use the gluPerspective
	 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble) lpRect->right / (GLdouble) lpRect->bottom, 1.0, 100000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera->Look();
	

	glDisable(GL_DEPTH_TEST);
	// Draw instruments
	panel->draw(lpRect);

	// Draw aircraft
	aircraft->draw(lpRect, FALSE, TRUE);
}

// Initialize the illumination and material
void Renderer::initializeIlluminationAndMaterial(void)
{
	GLfloat mat_ambient[]= { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat mat_diffuse[]= { 0.4f, 0.4f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };	
	GLfloat mat_emission[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat mat_shininess[] = {5.0f};
	GLfloat mat_no[] = {0.0f, 0.0f, 0.0f, 1.0f};
	
	GLfloat light0_position[] = {0.0f, 0.0f, 1.0f, 0.0f};
	GLfloat light0_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light0_diffuse[]= { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light0_specular[]= { 0.8f, 0.8f, 0.8f, 1.0f };
	
	GLfloat lmodel_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_no);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);		
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

/*
 * Update the instruments' data.
 */
void Renderer::updateInstrumentsData()
{
	// And here we just update heading, pitch and roll
	// Heading
	panel->updateDirectonalGyro(stat[0]);
	// Pitch
	panel->updateAttitudeGyro(stat[1], TRUE);
	// Roll
	panel->updateAttitudeGyro(stat[2], FALSE);
}


/*
 * Update stat array by FlyState, IMUTestData and OPTTRACETestData
 */
void Renderer::updateStat(pFlyState fs) 
{
	/*
	 * Should transform radian into angle
	 */
	stat[0] = fs->psi / PI * 180.0;
	stat[1] = fs->theta / PI * 180.0;
	stat[2] = fs->phi / PI * 180.0;
	
	stat[3] = fs->N_Speed;
	stat[4] = fs->E_Speed;
	stat[5] = fs->D_Speed;

	stat[6] = fs->N_Speed_ACC;
	stat[7] = fs->E_Speed_ACC;
	stat[8] = fs->D_Speed_ACC;
}

void Renderer::updateStat(pIMUTestData itd)
{
	stat[0] = itd->psi / PI * 180.0;
	stat[1] = itd->theta / PI * 180.0;
	stat[2] = itd->phi / PI * 180.0;
	
	stat[3] = itd->N_Speed;
	stat[4] = itd->E_Speed;
	stat[5] = itd->D_Speed;

	stat[6] = itd->N_Acc;
	stat[7] = itd->E_Acc;
	stat[8] = itd->D_Acc;
}
void Renderer::updateStat(pOPTTRACETestData otd)
{
	stat[0] = otd->psi / PI * 180.0;
	stat[1] = otd->theta / PI * 180.0;
	stat[2] = otd->phi / PI * 180.0;
	
	stat[3] = otd->N_Speed;
	stat[4] = otd->E_Speed;
	stat[5] = otd->D_Speed;

	stat[6] = otd->N_Acc;
	stat[7] = otd->E_Acc;
	stat[8] = otd->D_Acc;
}

void Renderer::updateCamera(void)
{
	// Here we just response for mouse move events
	camera->Update();
}

void Renderer::updateCamera(LPPOINT lpPoint)
{
	// Here we just response for mouse move events
	camera->Update(lpPoint);
}

void Renderer::updateCamera(int virtualKey)
{
	camera->Update(virtualKey);
}

// Draw fonts.
void Renderer::drawFonts()
{
	// When the client area minimized, just return.
	if (lpRect->right == 0 || lpRect->bottom == 0)
		return;
	
	glPushMatrix();
	glLoadIdentity();
	
	/*
	 * Because this LPRECT represents the client area's size, so upper-left cornor is (0, 0)
	 */
	/*
	 * The following codes is commented for the using gluOrtho2D
	 */
	//static LONG originRight = lpRect->right;
	//static LONG originBottom = lpRect->bottom;

	///*
	// * We just handle the X-axis' coordinate and Y-axis' coordinate
	// */
	float xPos = LEFT_MARGIN;
	float yPos = lpRect->bottom - TOP_MARGIN;
	//// Calculate the difference
	//float xDiff, yDiff;
	//xDiff = float(originRight - lpRect->right)/ originRight * abs(xPos);
	//yDiff = float(originBottom - lpRect->bottom) / originBottom * abs(yPos);
	//
	//originRight = lpRect->right;
	//originBottom = lpRect->bottom;
	//
	//xPos = xPos + xDiff; 
	//yPos = yPos - yDiff;

	glPushAttrib(GL_COLOR_BUFFER_BIT);	
	glDisable(GL_LIGHTING);	
	glColor3f(1.0f, 1.0f, 1.0f);

	/*
	 * 0.1f is the height of a letter
	 * And make the 0.25f the width of angles
	 */

	///*
	// * Testing codes
	// */
	//glRasterPos3f(lpRect->right / 2, lpRect->bottom / 2, 0.0f);
	//glPrint(base, "Here we are");

	/*
	 * The angle column
	 */
	glRasterPos3f(xPos, yPos - LETTER_WIDTH, 0.0f);
	glPrint(base, "Heading");
	glRasterPos3f(xPos, yPos - LETTER_WIDTH * 2, 0.0f);
	glPrint(base, "Pitch");
	glRasterPos3f(xPos, yPos - LETTER_WIDTH * 3, 0.0f);
	glPrint(base, "Roll");
	TRACE(_T("xPos: %f\n"), xPos);
	/*
	 * Rate column
	 */
	float rateX = xPos + ANGLE_LABEL_WIDTH + ANGLE_VALUE_WIDTH;
	glRasterPos3f(rateX, yPos, 0.0f);
	glPrint(base, "Rate(dec/sec)");
	glRasterPos3f(rateX, yPos - LETTER_WIDTH, 0.0f);
	glPrint(base, "X");
	glRasterPos3f(rateX, yPos - LETTER_WIDTH * 2, 0.0f);
	glPrint(base, "Y");
	glRasterPos3f(rateX, yPos - LETTER_WIDTH * 3, 0.0f);
	glPrint(base, "Z");
	
	/*
	 * Acceleration(g) column
	 */
	float accX = xPos + ANGLE_LABEL_WIDTH + ANGLE_VALUE_WIDTH + RATE_LABEL_WIDTH + RATE_VALUE_WIDTH + UNIT_WIDTH;
	glRasterPos3f(accX, yPos, 0.0f);
	glPrint(base, "Acceleration(g)");
	
	for (int i = 0; i < length; i++) {
		if (i >= 0 && i <= 2) {
			glRasterPos3f(xPos + ANGLE_LABEL_WIDTH, yPos - LETTER_WIDTH * (i % 3 + 1), 0.0f);
			glPrint(base, "%3.2f", stat[i]);
		} else if (i >= 3 && i <= 5) {
			glRasterPos3f(rateX + RATE_LABEL_WIDTH, yPos - LETTER_WIDTH * (i % 3 + 1), 0.0f);
			glPrint(base, "%3.1f", stat[i]);
		} else if (i >= 6 && i <= 8) {
			glRasterPos3f(accX, yPos - LETTER_WIDTH * (i % 3 + 1), 0.0f);
			glPrint(base, "%3.3f", stat[i]);
		}
	}
	glEnable(GL_LIGHTING);	
	glPopAttrib();
	glPopMatrix();
}

// Draw function
//void Renderer::draw(LPRECT lpRect, BOOL isExperiment/* = FALSE*/, BOOL isGyro/* = FALSE*/)
//{
//	if (isMultiport) {
//		for (int i = 0; i < 4; i++) {
//			switch (i) {
//				case 0:
//					glViewport(0, lpRect->bottom / 2, lpRect->right / 2, lpRect->bottom / 2);
//					glMatrixMode(GL_PROJECTION);
//					glLoadIdentity();
//					//gluPerspective(60.0, (GLdouble) lpRect->right / (GLdouble) lpRect->bottom, 1.0, 100000.0);
//					gluOrtho2D(0, lpRect->right / 2, 0, lpRect->bottom / 2);					
//					break;
//				case 1:
//					glViewport(lpRect->right / 2, lpRect->bottom / 2, lpRect->right / 2, lpRect->bottom / 2);
//					glMatrixMode(GL_PROJECTION);
//					glLoadIdentity();
//					gluPerspective(60.0, (GLdouble) lpRect->right / (GLdouble) lpRect->bottom, 1.0, 100000.0);
//					//gluOrtho2D(0, lpRect->right / 2, 0, lpRect->bottom / 2);					
//					break;
//				case 2:
//					glViewport(lpRect->right / 2, 0, lpRect->right / 2, lpRect->bottom / 2);
//					glMatrixMode(GL_PROJECTION);
//					glLoadIdentity();
//					gluPerspective(60.0, (GLdouble) lpRect->right / (GLdouble) lpRect->bottom, 1.0, 100000.0);
//					break;
//				case 3:
//					glViewport(0, 0, lpRect->right / 2, lpRect->bottom / 2);
//					glMatrixMode(GL_PROJECTION);
//					glLoadIdentity();
//					gluPerspective(60.0, (GLdouble) lpRect->right / (GLdouble) lpRect->bottom, 1.0, 100000.0);
//					break;
//				default:
//					break;
//			}
//			
//			switch (i) {
//				case 0:					
//					// Test codes
//					glMatrixMode(GL_MODELVIEW);
//					glLoadIdentity();
//					glClear(GL_DEPTH_BUFFER_BIT);
//					glColor3f(1.0f, 1.0f, 1.0f);
//					glBegin(GL_QUADS);			
//					glVertex2i(10, 10);
//					glVertex2i(20, 10);
//					glVertex2i(20, 10 + 20);
//					glVertex2i(10, 10 + 20);
//					glEnd();	
//					break;
//				case 1:					
//					// Establish a 3-d model
//					glMatrixMode(GL_MODELVIEW);
//					glLoadIdentity();
//					camera->Look();
//					glClear(GL_DEPTH_BUFFER_BIT);
//					aircraft->draw(lpRect);
//					break;
//				case 2:
//					break;
//				case 3:
//					// Clear the depth buffer.
//					glClear(GL_DEPTH_BUFFER_BIT);
//					draw();
//					break;
//				default:
//					break;
//			}
//		}
//	} else {
//		// Currently we just focus on this branch.
//		glViewport(0, 0, lpRect->right, lpRect->bottom);
//		glMatrixMode(GL_PROJECTION);
//		glLoadIdentity();
//		gluPerspective(60.0, (GLdouble) lpRect->right / (GLdouble) lpRect->bottom, 1.0, 100000.0);
//		// Clear the depth buffer.
//		glClear(GL_DEPTH_BUFFER_BIT);
//		if (isExperiment) {
//			draw();
//		} else if(isGyro) {
//			drawWithoutInstruments();
//		}
//	}
//}

void Renderer::draw(LPRECT lpRect, int renderMode)
{
	if (lpRect)
		this->lpRect = lpRect;
	if (isMultiport) {
		for (int i = 0; i < 4; i++) {
			switch (i) {
				case 0:
					glViewport(0, lpRect->bottom / 2, lpRect->right / 2, lpRect->bottom / 2);
					glMatrixMode(GL_PROJECTION);
					glLoadIdentity();
					//gluPerspective(60.0, (GLdouble) lpRect->right / (GLdouble) lpRect->bottom, 1.0, 100000.0);
					gluOrtho2D(0, lpRect->right / 2, 0, lpRect->bottom / 2);					
					break;
				case 1:
					glViewport(lpRect->right / 2, lpRect->bottom / 2, lpRect->right / 2, lpRect->bottom / 2);
					glMatrixMode(GL_PROJECTION);
					glLoadIdentity();
					gluPerspective(60.0, (GLdouble) lpRect->right / (GLdouble) lpRect->bottom, 1.0, 100000.0);
					//gluOrtho2D(0, lpRect->right / 2, 0, lpRect->bottom / 2);					
					break;
				case 2:
					glViewport(lpRect->right / 2, 0, lpRect->right / 2, lpRect->bottom / 2);
					glMatrixMode(GL_PROJECTION);
					glLoadIdentity();
					gluPerspective(60.0, (GLdouble) lpRect->right / (GLdouble) lpRect->bottom, 1.0, 100000.0);
					break;
				case 3:
					glViewport(0, 0, lpRect->right / 2, lpRect->bottom / 2);
					glMatrixMode(GL_PROJECTION);
					glLoadIdentity();
					gluPerspective(60.0, (GLdouble) lpRect->right / (GLdouble) lpRect->bottom, 1.0, 100000.0);
					break;
				default:
					break;
			}
			
			switch (i) {
				case 0:					
					// Test codes
					glMatrixMode(GL_MODELVIEW);
					glLoadIdentity();
					glClear(GL_DEPTH_BUFFER_BIT);
					glColor3f(1.0f, 1.0f, 1.0f);
					glBegin(GL_QUADS);			
					glVertex2i(10, 10);
					glVertex2i(20, 10);
					glVertex2i(20, 10 + 20);
					glVertex2i(10, 10 + 20);
					glEnd();	
					break;
				case 1:					
					// Establish a 3-d model
					glMatrixMode(GL_MODELVIEW);
					glLoadIdentity();
					camera->Look();
					glClear(GL_DEPTH_BUFFER_BIT);
					aircraft->draw(lpRect);
					break;
				case 2:
					break;
				case 3:
					// Clear the depth buffer.
					glClear(GL_DEPTH_BUFFER_BIT);
					draw();
					break;
				default:
					break;
			}
		}
	} else {
		// Currently we just focus on this branch.
		glViewport(0, 0, lpRect->right, lpRect->bottom);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0, (GLdouble) lpRect->right / (GLdouble) lpRect->bottom, 1.0, 100000.0);
		// Clear the depth buffer.
		glClear(GL_DEPTH_BUFFER_BIT);
		
		switch (renderMode) {
			case CGTView::FLIGHT_PATH_SET:
				drawPath();
				break;
			case CGTView::IMU_TEST:
				drawWithoutInstruments();
				break;
			case CGTView::OPT_TEST:
				drawWithoutInstruments();
				break;
			case CGTView::FLIGHT_EXPERIMENT:
				draw();
				break;
			case CGTView::DATA_PROCESS:
				draw();
				break;
			default:
				break;
		}
	}
}

/*
 * This function will be invoked when IMU or OPT test starts
 */
void Renderer::drawWithoutInstruments(void)
{
	/*
	 * First when we draw the text, we use the gluOrtho2D
	 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, lpRect->right, 0, lpRect->bottom);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera->Look();

	/*
	 * Test codes
	 */
	/*int sideLength = 400;
	glBegin(GL_QUADS);
		glVertex3f(lpRect->right / 2 - sideLength / 2, lpRect->bottom / 2 - sideLength / 2, -1.0f);
		glVertex3f(lpRect->right / 2 + sideLength / 2, lpRect->bottom / 2 - sideLength / 2, -1.0f);
		glVertex3f(lpRect->right / 2 + sideLength / 2, lpRect->bottom / 2 + sideLength / 2, -1.0f);
		glVertex3f(lpRect->right / 2 - sideLength / 2, lpRect->bottom / 2 + sideLength / 2, -1.0f);
	glEnd();*/
	// Draw text
	drawFonts();

	/*
	 * After drawing text, we use gluPerspective
	 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble) lpRect->right / (GLdouble) lpRect->bottom, 1.0, 100000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera->Look();

	glDisable(GL_DEPTH_TEST);
	// Draw aircraft without terrains
	aircraft->draw(lpRect, FALSE);
}


void Renderer::drawPath(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera->Look();
	glTranslatef(0.0f, 0.0f, -100.0f);
	glRotatef( 30.0f, 1.0f, 0.0f, 0.0f);
	glRotatef( -45.0f, 0.0f, 1.0f, 0.0f);
	Scene::drawCoordinateSystem(lpRect);
	// Then draw a grid
	Scene::drawGrid(lpRect);

	glDisable(GL_LIGHTING);
	if (pPath) {
		glPushAttrib(GL_POINT_BIT | GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 1.0f, 1.0f);

		std::vector<PathPointData*>::iterator iter;
		// Draw lines
		glBegin(GL_LINE_STRIP);
		for (iter = pPath->begin(); iter != pPath->end(); iter++) {
			if (*iter) {
				glVertex3f((*iter)->Coordinate_X, (*iter)->Coordinate_Y, (*iter)->Coordinate_Z);
			}
		}
		glEnd();
		// Draw points
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		for (iter = pPath->begin(); iter != pPath->end(); iter++) {
			if (*iter) {
				glVertex3f((*iter)->Coordinate_X, (*iter)->Coordinate_Y, (*iter)->Coordinate_Z);
			}
		}
		glEnd();
		glPopAttrib();
	}
	glEnable(GL_LIGHTING);

	if (selectedPoint) {
		drawNavigator();
	}
}

void Renderer::updateData(void)
{
	updateInstrumentsData();

	aircraft->update(stat);
}

void Renderer::updateData(CString aLine)
{
	if (aLine.IsEmpty() || !getFlyStatistics(aLine, stat, length)) 
		return;

	updateInstrumentsData();

	aircraft->update(stat);

}

void Renderer::updateData(pFlyState fs)
{
	aircraft->update(fs);

	/*
	 * We should update the stat first
	 */
	updateStat(fs);

	updateInstrumentsData();
}

void Renderer::updateData(pIMUTestData itd)
{
	aircraft->update(itd);

	updateStat(itd);
}

void Renderer::updateData(pOPTTRACETestData otd)
{
	aircraft->update(otd);
	
	updateStat(otd);
}

void Renderer::drawNavigator(void)
{
	const double baseRadius = 1.0;
	const double topRadius = 0.0;
	const double length = 2.5;
	if (!qobj)
		qobj = gluNewQuadric();

	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);

	glDisable(GL_LIGHTING);
	glPushMatrix();
	glPushAttrib(GL_COLOR_BUFFER_BIT);

	// First translate to the selected point
	glTranslatef(selectedPoint->Coordinate_X, selectedPoint->Coordinate_Y, selectedPoint->Coordinate_Z);
	// Second draw the x-axis navigator
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	if (navi == 1)
		glColor3f(1.0f, 1.0f, 1.0f);
	else 
		glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, NAVIGATOR_LENGTH);
	glEnd();

	glTranslatef(0.0f, 0.0f, NAVIGATOR_LENGTH);	
	gluCylinder(qobj, baseRadius, topRadius, length, 10, 10);
	glPopMatrix();

	// Third draw the y-axis navigator
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	if (navi == 2)
		glColor3f(1.0f, 1.0f, 1.0f);
	else 
		glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, NAVIGATOR_LENGTH);
	glEnd();
	glTranslatef(0.0f, 0.0f, NAVIGATOR_LENGTH);	
	gluCylinder(qobj, baseRadius, topRadius, length, 10, 10);
	glPopMatrix();

	// Forth draw the z-axis navigator
	glPushMatrix();
	if (navi == 3)
		glColor3f(1.0f, 1.0f, 1.0f);
	else 
		glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, NAVIGATOR_LENGTH);
	glEnd();
	glTranslatef(0.0f, 0.0f, NAVIGATOR_LENGTH);	
	gluCylinder(qobj, baseRadius, topRadius, length, 10, 10);
	glPopMatrix();

	glPopAttrib();
	glPopMatrix();
}
