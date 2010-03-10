#include "StdAfx.h"

#include <windows.h>
#include <GL/glut.h>
#include <vector>

#include "Renderer.h"
#include "XMLReader.h"
#include "Util.h"
#include "DirectionalGyro.h"
#include "Terrain.h"

#ifndef PI
#define PI 3.14159265359
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
	aircraft->draw();
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
	stat[0] = fs->BODY_ANG_PSI / PI * 180.0;
	stat[1] = fs->BODY_ANG_THETA / PI * 180.0;
	stat[2] = fs->BODY_ANG_PHI / PI * 180.0;
	
	stat[3] = fs->BODY_ANG_P;
	stat[4] = fs->BODY_ANG_Q;
	stat[5] = fs->BODY_ANG_R;

	stat[6] = fs->BODY_ACC_X;
	stat[7] = fs->BODY_ACC_Y;
	stat[8] = fs->BODY_ACC_Z;
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
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_COLOR_BUFFER_BIT);	
	glDisable(GL_LIGHTING);	
	glColor3f(0.8f, 0.8f, 1.0f);
	glRasterPos3f(-0.8f, 1.0f, -2.0f);
	glPrint(base, "Rate(dec/sec)");
	glRasterPos3f(-0.8f, 0.9f, -2.0f);
	glPrint(base, "X");
	glRasterPos3f(-0.8f, 0.8f, -2.0f);
	glPrint(base, "Y");
	glRasterPos3f(-0.8f, 0.7f, -2.0f);
	glPrint(base, "Z");
	
	glRasterPos3f(-0.1f, 1.0f, -2.0f);
	glPrint(base, "Acceleration(g)");
	
	glRasterPos3f(-1.7f, 0.9f, -2.0f);
	glPrint(base, "Heading  ");
	glRasterPos3f(-1.7f, 0.8f, -2.0f);
	glPrint(base, "Pitch       ");
	glRasterPos3f(-1.7f, 0.7f, -2.0f);
	glPrint(base, "Roll        ");

	for (int i = 0; i < length; i++) {
		if (i >= 0 && i <= 2) {
			glRasterPos3f(-1.2f, 0.9f - 0.1f * (i % 3), -2.0f);
			glPrint(base, "%3.2f", stat[i]);
		} else if (i >= 3 && i <= 5) {
			glRasterPos3f(-0.7f, 0.9f - 0.1f * (i % 3), -2.0f);
			glPrint(base, "%3.1f", stat[i]);
		} else if (i >= 6 && i <= 8) {
			glRasterPos3f(-0.1f, 0.9f - 0.1f * (i % 3), -2.0f);
			glPrint(base, "%3.3f", stat[i]);
		}
	}
	glEnable(GL_LIGHTING);	
	glPopAttrib();
	glPopMatrix();
}

// Draw function
void Renderer::draw(LPRECT lpRect)
{
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
		// Current we just focus on this branch.
		glViewport(0, 0, lpRect->right, lpRect->bottom);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0, (GLdouble) lpRect->right / (GLdouble) lpRect->bottom, 1.0, 100000.0);
		// Clear the depth buffer.
		glClear(GL_DEPTH_BUFFER_BIT);
		draw();
	}
}