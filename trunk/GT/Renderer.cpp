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

#ifndef PI
#define PI 3.14159265359
#endif

#ifndef ANGLE_LABEL_WIDTH 
#define ANGLE_LABEL_WIDTH 0.25f
#endif

#ifndef ANGLE_VALUE_WIDTH
#define ANGLE_VALUE_WIDTH 0.25f
#endif

#ifndef RATE_LABEL_WIDTH
#define RATE_LABEL_WIDTH 0.1f
#endif

#ifndef RATE_VALUE_WIDTH
#define RATE_VALUE_WIDTH 0.25f
#endif

#ifndef UNIT_WIDTH
#define UNIT_WIDTH 0.2f
#endif

#ifndef LETTER_WIDTH
#define LETTER_WIDTH 0.1f
#endif

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
}


void Renderer::draw(void)
{
	if (!panel)
		return;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera->Look();

	// Draw fonts
	drawFonts();

	glDisable(GL_DEPTH_TEST);
	// Draw instruments
	panel->draw();

	// Draw aircraft
	aircraft->draw(lpRect);
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

// Update the instruments' data.
void Renderer::updateInstrumentsData()
{
	if (!stat || length <= 0)
		return;

	// And here we just update heading, pitch and roll
	// Heading
	panel->updateDirectonalGyro(stat[0]);
	// Pitch
	panel->updateAttitudeGyro(stat[1], TRUE);
	// Roll
	panel->updateAttitudeGyro(stat[2], FALSE);

	// Aircraft model also should update xrot, yrot, zrot
	aircraft->update(stat);
}

BOOL Renderer::updateInstrumentsData(CString aLine)
{
	if (aLine.IsEmpty() || !getFlyStatistics(aLine, stat, length)) 
		return FALSE;

	// And here we just update heading, pitch and roll
	// Heading
	panel->updateDirectonalGyro(stat[0]);
	// Pitch
	panel->updateAttitudeGyro(stat[1], TRUE);
	// Roll
	panel->updateAttitudeGyro(stat[2], FALSE);

	// Aircraft model also should update xrot, yrot, zrot
	aircraft->update(stat);

	return TRUE;
}

// Update the instruments' data.
void Renderer::updateInstrumentsData(FlyState *fs)
{
	if (!fs) {
		return;
	}
	// First update stat array
	updateStat(fs);
	// Then we update the instruments' data
	updateInstrumentsData();
}

// Update stat array by fs
void Renderer::updateStat(FlyState* fs) 
{
	// Should transform radian into angle
	//stat[0] = fs->BODY_ANG_PSI / PI * 180.0;
	//stat[1] = fs->BODY_ANG_THETA / PI * 180.0;
	//stat[2] = fs->BODY_ANG_PHI / PI * 180.0;
	//
	//stat[3] = fs->BODY_ANG_P;
	//stat[4] = fs->BODY_ANG_Q;
	//stat[5] = fs->BODY_ANG_R;

	//stat[6] = fs->BODY_ACC_X;
	//stat[7] = fs->BODY_ACC_Y;
	//stat[8] = fs->BODY_ACC_Z;
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
	static LONG originRight = lpRect->right;
	static LONG originBottom = lpRect->bottom;

	/*
	 * We just handle the X-axis' coordinate and Y-axis' coordinate
	 */
	static float xPos = -1.6f;
	static float yPos = 1.1f;
	// Calculate the difference
	float xDiff, yDiff;
	xDiff = float(originRight - lpRect->right)/ originRight * abs(xPos);
	yDiff = float(originBottom - lpRect->bottom) / originBottom * abs(yPos);
	
	originRight = lpRect->right;
	originBottom = lpRect->bottom;
	
	xPos = xPos + xDiff; 
	yPos = yPos - yDiff;

	glPushAttrib(GL_COLOR_BUFFER_BIT);	
	glDisable(GL_LIGHTING);	
	glColor3f(1.0f, 1.0f, 1.0f);

	/*
	 * 0.1f is the height of a letter
	 * And make the 0.25f the width of angles
	 */

	/*
	 * The angle column
	 */
	glRasterPos3f(xPos, yPos - LETTER_WIDTH, -2.0f);
	glPrint(base, "Heading");
	glRasterPos3f(xPos, yPos - LETTER_WIDTH * 2, -2.0f);
	glPrint(base, "Pitch");
	glRasterPos3f(xPos, yPos - LETTER_WIDTH * 3, -2.0f);
	glPrint(base, "Roll");
	TRACE(_T("xPos: %f\n"), xPos);
	/*
	 * Rate column
	 */
	float rateX = xPos + ANGLE_LABEL_WIDTH + ANGLE_VALUE_WIDTH;
	glRasterPos3f(rateX, yPos, -2.0f);
	glPrint(base, "Rate(dec/sec)");
	glRasterPos3f(rateX, yPos - LETTER_WIDTH, -2.0f);
	glPrint(base, "X");
	glRasterPos3f(rateX, yPos - LETTER_WIDTH * 2, -2.0f);
	glPrint(base, "Y");
	glRasterPos3f(rateX, yPos - LETTER_WIDTH * 3, -2.0f);
	glPrint(base, "Z");
	
	/*
	 * Acceleration(g) column
	 */
	float accX = xPos + ANGLE_LABEL_WIDTH + ANGLE_VALUE_WIDTH + RATE_LABEL_WIDTH + RATE_VALUE_WIDTH + UNIT_WIDTH;
	glRasterPos3f(accX, yPos, -2.0f);
	glPrint(base, "Acceleration(g)");
	
	

	for (int i = 0; i < length; i++) {
		if (i >= 0 && i <= 2) {
			glRasterPos3f(xPos + ANGLE_LABEL_WIDTH, yPos - LETTER_WIDTH * (i % 3 + 1), -2.0f);
			glPrint(base, "%3.2f", stat[i]);
		} else if (i >= 3 && i <= 5) {
			glRasterPos3f(rateX + RATE_LABEL_WIDTH, yPos - LETTER_WIDTH * (i % 3 + 1), -2.0f);
			glPrint(base, "%3.1f", stat[i]);
		} else if (i >= 6 && i <= 8) {
			glRasterPos3f(accX, yPos - LETTER_WIDTH * (i % 3 + 1), -2.0f);
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
		//if (isExperiment) {
		//	draw();
		//} else if(isGyro) {
		//	drawWithoutInstruments();
		//}
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
			default:
				break;
		}
	}
}

/*
 * This function will be invoked when IMU test starts
 */
void Renderer::drawWithoutInstruments(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera->Look();

	// Draw fonts
	drawFonts();

	glDisable(GL_DEPTH_TEST);
	// Draw aircraft without terrains
	aircraft->draw(lpRect, FALSE);
}

void Renderer::updateAircraft(IMUTestData* itd)
{
	aircraft->update(itd);
}

void Renderer::updateAircraft(pOPTTRACETestData otd)
{
	aircraft->update(otd);
}

void Renderer::drawPath(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera->Look();
	glTranslatef(0.0f, 0.0f, -5.0f);
	// Draw path
	if (pPath) {
		std::vector<PathPointData*>::iterator iter;
		glBegin(GL_LINES);
		for (iter = pPath->begin(); iter != pPath->end(); iter++) {
			if (*iter) {
				glVertex3f((*iter)->Coordinate_X, (*iter)->Coordinate_Y, (*iter)->Coordinate_Z);
			}
		}
		glEnd();
	}
}