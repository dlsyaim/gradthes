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

void Aircraft::draw(void)
{
	glPushMatrix();
	glDisable(GL_BLEND);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(0.0f, 0.0f, -600.0f);

	glTranslatef(250.0f, -20.0f, 0.0f);

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
	//yrot = fs->BODY_ANG_PSI;
	//xrot = fs->BODY_ANG_THETA;
	//zrot = fs->BODY_ANG_PHI;
}

void Aircraft::update(IMUTestData *itd)
{
	yrot = itd->psi;
	xrot = itd->theta;
	zrot = itd->phi;
}

// Draw function.
void Aircraft::draw(LPRECT lpRect)
{
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
}