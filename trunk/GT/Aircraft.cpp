#include "StdAfx.h"
#include <windows.h>
#include <GL/glut.h>
#include "Aircraft.h"
#include "Scene.h"
#include "Terrain.h"
#include "Texture.h"


Aircraft::Aircraft(void):
meshes(0),
xrot(0.0),
yrot(0.0),
zrot(0.0),
x(0.0),
y(0.0),
z(0.0)
{
	terrain = new Terrain();
}

Aircraft::~Aircraft(void)
{
	if (terrain)
		delete terrain;
}

void Aircraft::loadAircraft(void)
{

}

void Aircraft::loadAircraft(char *filePath)
{
	meshes = loadVRML(filePath);

	terrain->LoadRawFile("..\\terrains\\terrain.raw");
	terrain->getTerrainTex()->loadTexture("..\\Instruments\\Textures\\Terrain.tga");
}

// Attention: This function needs to be consummated
void Aircraft::drawWithAutoSize(LPRECT lpRect)
{
	// When the client area minimized, just return.
	if (lpRect->right == 0 || lpRect->bottom == 0)
		return;
	/*
	 * Because this LPRECT represents the client area's size, so upper-left cornor is (0, 0)
	 */
	static LONG originRight = lpRect->right;
	static LONG originBottom = lpRect->bottom;

	static float distance = -600.0f;
	// Calculate the differences
	float diff;
	diff = max((float) originRight / lpRect->right, (float) originBottom / lpRect->bottom);
	if (diff == 1.0f) {
		diff = min ((float) originRight / lpRect->right, (float) originBottom / lpRect->bottom);
	}
	originRight = lpRect->right;
	originBottom = lpRect->bottom;
	distance = distance * diff;

	glPushMatrix();
	glDisable(GL_BLEND);
	glColor3f(1.0f, 1.0f, 1.0f);
	/*
	 * Whe the client area's size changes, then the aircraft must update acoordingly.
	 * And to accommplish this target, we just traslate deeper towards Z-axis negative direction to make
	 * the aircaft smaller
	 */
	// First translate 600.0f towards Z-axis negative direction
	glTranslatef(0.0f, 0.0f, distance);
	// Then translate 50.0f towards Y-axis negative direction
	glTranslatef(0.0f, -150.0f, 0.0f);

	// To make the aircraft's head toward left
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(-xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(-yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(-zrot, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
		for ( int i = 0; i < (int)meshes.size(); i++ ) {
			for ( int j = 0; j < (int)meshes[i].numFaces; j++ ) {
				glNormal3f(meshes[i].normals[(int) meshes[i].faces[j].x].x, meshes[i].normals[(int) meshes[i].faces[j].x].y, meshes[i].normals[(int) meshes[i].faces[j].x].z);
				glVertex3f(meshes[i].vertices[(int) meshes[i].faces[j].x].x, meshes[i].vertices[(int) meshes[i].faces[j].x].y, meshes[i].vertices[(int) meshes[i].faces[j].x].z);

				glNormal3f(meshes[i].normals[(int) meshes[i].faces[j].y].x, meshes[i].normals[(int) meshes[i].faces[j].y].y, meshes[i].normals[(int) meshes[i].faces[j].y].z);
				glVertex3f(meshes[i].vertices[(int) meshes[i].faces[j].y].x, meshes[i].vertices[(int) meshes[i].faces[j].y].y, meshes[i].vertices[(int) meshes[i].faces[j].y].z);

				glNormal3f(meshes[i].normals[(int) meshes[i].faces[j].z].x, meshes[i].normals[(int) meshes[i].faces[j].z].y, meshes[i].normals[(int) meshes[i].faces[j].z].z);
				glVertex3f(meshes[i].vertices[(int) meshes[i].faces[j].z].x, meshes[i].vertices[(int) meshes[i].faces[j].z].y, meshes[i].vertices[(int) meshes[i].faces[j].z].z);
			}
		}
	glEnd();
	glEnable(GL_BLEND);
	glPopMatrix();
}

// Attention: This function needs to be consummated
void Aircraft::drawWithInstruments(LPRECT lpRect)
{
	// When the client area minimized, just return.
	if (lpRect->right == 0 || lpRect->bottom == 0)
		return;
	/*
	 * Because this LPRECT represents the client area's size, so upper-left cornor is (0, 0)
	 */
	static LONG originRight = lpRect->right;
	static LONG originBottom = lpRect->bottom;

	const float x_offset = 300.0f;
	const float y_offset = -50.0f;

	static float distance = -600.0f;
	// Calculate the differences
	float diff;
	diff = max((float) originRight / lpRect->right, (float) originBottom / lpRect->bottom);
	if (diff == 1.0f) {
		diff = min ((float) originRight / lpRect->right, (float) originBottom / lpRect->bottom);
	}
	originRight = lpRect->right;
	originBottom = lpRect->bottom;
	distance = distance * diff;

	glPushMatrix();
	glDisable(GL_BLEND);
	glColor3f(1.0f, 1.0f, 1.0f);
	/*
	 * Whe the client area's size changes, then the aircraft must update acoordingly.
	 * And to accommplish this target, we just traslate deeper towards Z-axis negative direction to make
	 * the aircaft smaller
	 */
	// First translate 600.0f towards Z-axis negative direction
	glTranslatef(x_offset, y_offset, distance);


	// To make the aircraft's head toward left
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(-xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(-yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(-zrot, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
		for ( int i = 0; i < (int)meshes.size(); i++ ) {
			for ( int j = 0; j < (int)meshes[i].numFaces; j++ ) {
				glNormal3f(meshes[i].normals[(int) meshes[i].faces[j].x].x, meshes[i].normals[(int) meshes[i].faces[j].x].y, meshes[i].normals[(int) meshes[i].faces[j].x].z);
				glVertex3f(meshes[i].vertices[(int) meshes[i].faces[j].x].x, meshes[i].vertices[(int) meshes[i].faces[j].x].y, meshes[i].vertices[(int) meshes[i].faces[j].x].z);

				glNormal3f(meshes[i].normals[(int) meshes[i].faces[j].y].x, meshes[i].normals[(int) meshes[i].faces[j].y].y, meshes[i].normals[(int) meshes[i].faces[j].y].z);
				glVertex3f(meshes[i].vertices[(int) meshes[i].faces[j].y].x, meshes[i].vertices[(int) meshes[i].faces[j].y].y, meshes[i].vertices[(int) meshes[i].faces[j].y].z);

				glNormal3f(meshes[i].normals[(int) meshes[i].faces[j].z].x, meshes[i].normals[(int) meshes[i].faces[j].z].y, meshes[i].normals[(int) meshes[i].faces[j].z].z);
				glVertex3f(meshes[i].vertices[(int) meshes[i].faces[j].z].x, meshes[i].vertices[(int) meshes[i].faces[j].z].y, meshes[i].vertices[(int) meshes[i].faces[j].z].z);
			}
		}
	glEnd();
	glEnable(GL_BLEND);
	glPopMatrix();
}

void Aircraft::update(double *stat) {
	yrot = stat[0];
	xrot = stat[1];
	zrot = stat[2];
}

void Aircraft::update(FlyState *fs) {
	/***** Attention this is a radian *****/
	yrot = fs->psi * 180 / PI;
	xrot = fs->theta * 180 / PI;
	zrot = fs->phi * 180 / PI;
}

void Aircraft::update(IMUTestData *itd)
{
	yrot = itd->psi * 180 / PI;
	xrot = itd->theta * 180 / PI;
	zrot = itd->phi * 180 / PI;
}

void Aircraft::update(pOPTTRACETestData otd)
{
	/***** Attention this is a radian *****/
	yrot = otd->psi * 180 / PI;
	xrot = otd->theta * 180 / PI;
	zrot = otd->phi * 180 / PI;
}

// Draw function.
void Aircraft::draw(LPRECT lpRect, BOOL isTerrain/* = TRUE*/, BOOL isInstr/* = FALSE*/)
{
	if (isTerrain) {
		glPushMatrix();
			glPushMatrix();
			glTranslatef(0.0f, 0.0f, -5.0f);
			glTranslatef(-1.0f, -1.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(-xrot, 1.0f, 0.0f, 0.0f);
			glRotatef(-yrot, 0.0f, 1.0f, 0.0f);
			glRotatef(-zrot, 0.0f, 0.0f, 1.0f);
			Scene::drawCoordinateSystem();
			glPopMatrix();

			// Render the terrain.
			glPushMatrix();
			glTranslatef(-512.0f, -20.0f, -512.0f);
			terrain->RenderHeightMap();
			glPopMatrix();

			// Render the skybox
			glPushMatrix();
			glTranslatef(x, y, z);

			glPopMatrix();
			
			glPushMatrix();
			glDisable(GL_BLEND);
			glColor3f(1.0f, 1.0f, 1.0f);
			// -800.0f is an experienced value. 
			//glTranslatef(0.0f, 0.0f, -800.0f);
			glTranslatef(x, y, z);
			// To make the aircraft's head toward left
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(-xrot, 1.0f, 0.0f, 0.0f);
			glRotatef(-yrot, 0.0f, 1.0f, 0.0f);
			glRotatef(-zrot, 0.0f, 0.0f, 1.0f);
			glBegin(GL_TRIANGLES);
				for ( int i = 0; i < (int)meshes.size(); i++ ) {
					for ( int j = 0; j < (int)meshes[i].numFaces; j++ ) {
						glNormal3f(meshes[i].normals[(int) meshes[i].faces[j].x].x, meshes[i].normals[(int) meshes[i].faces[j].x].y, meshes[i].normals[(int) meshes[i].faces[j].x].z);
						glVertex3f(meshes[i].vertices[(int) meshes[i].faces[j].x].x, meshes[i].vertices[(int) meshes[i].faces[j].x].y, meshes[i].vertices[(int) meshes[i].faces[j].x].z);

						glNormal3f(meshes[i].normals[(int) meshes[i].faces[j].y].x, meshes[i].normals[(int) meshes[i].faces[j].y].y, meshes[i].normals[(int) meshes[i].faces[j].y].z);
						glVertex3f(meshes[i].vertices[(int) meshes[i].faces[j].y].x, meshes[i].vertices[(int) meshes[i].faces[j].y].y, meshes[i].vertices[(int) meshes[i].faces[j].y].z);

						glNormal3f(meshes[i].normals[(int) meshes[i].faces[j].z].x, meshes[i].normals[(int) meshes[i].faces[j].z].y, meshes[i].normals[(int) meshes[i].faces[j].z].z);
						glVertex3f(meshes[i].vertices[(int) meshes[i].faces[j].z].x, meshes[i].vertices[(int) meshes[i].faces[j].z].y, meshes[i].vertices[(int) meshes[i].faces[j].z].z);
					}
				}
			glEnd();
			glEnable(GL_BLEND);
			glPopMatrix();
		glPopMatrix();
	} else if (isInstr) {
		// Adjust the aircraft's position
		drawWithInstruments(lpRect);
	} else {
		// No terrain will be drawn
		drawWithAutoSize(lpRect);
	}
}