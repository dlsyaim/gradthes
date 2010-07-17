#include "StdAfx.h"
#include <windows.h>
#include <GL/glut.h>
#include "Aircraft.h"
#include "Scene.h"
#include "Terrain.h"
#include "Texture.h"
#include "Utility.h"


Aircraft::Aircraft(void):
	xrot_(0.0),
	yrot_(0.0),
	zrot_(0.0),
	x_(0.0f),
	y_(0.0f),
	z_(-600.0f)
{
	terrain_ = new Terrain();
}

Aircraft::~Aircraft(void)
{
	if (terrain_)
		delete terrain_;
}

void Aircraft::loadAircraft(const char *filePath)
{
	meshes_ = loadVRML((char *)filePath);

	terrain_->LoadRawFile("..\\terrains\\terrain.raw");
	std::string texPath = "..\\Instruments\\Textures\\Terrain.tga";
	terrain_->getTerrainTex()->loadTexture(texPath);
}

// Attention: This function needs to be consummated
void Aircraft::drawWithAutoSize(const RECT &rect)
{
	// When the client area minimized, just return.
	if (rect.right == 0 || rect.bottom == 0)
		return;
	
	// Calculate the differences
	float diff = calculateDifferences(rect);
	z_ = z_ + diff;	
	y_ = -150.0f;
	x_ = 0.0f;

	drawModel();
	
}

// Attention: This function needs to be consummated
void Aircraft::drawWithInstruments(const RECT &rect)
{
	// When the client area minimized, just return.
	if (rect.right == 0 || rect.bottom == 0)
		return;

	// Calculate the differences
	float diff = calculateDifferences(rect);
	z_ = z_ + diff;
	y_ = -50.0f;
	x_ = 300.0f;

	drawModel();
}

void Aircraft::update(const double *stat) {
	ASSERT(stat != NULL);

	yrot_ = stat[0];
	xrot_ = stat[1];
	zrot_ = stat[2];
}

void Aircraft::update(const FlyState &fs)
{
	/***** Attention this is a radian *****/
	yrot_ = fs.psi * 180 / PI;
	xrot_ = fs.theta * 180 / PI;
	zrot_ = fs.phi * 180 / PI;
}

void Aircraft::update(const IMUTestData &itd)
{
	/***** Attention this is a radian *****/
	yrot_ = itd.psi * 180 / PI;
	xrot_ = itd.theta * 180 / PI;
	zrot_ = itd.phi * 180 / PI;
}

void Aircraft::update(const OPTTRACETestData &otd)
{
	/***** Attention this is a radian *****/
	yrot_ = otd.psi * 180 / PI;
	xrot_ = otd.theta * 180 / PI;
	zrot_ = otd.phi * 180 / PI;
}

/*
 * The draw function's entry
 */
void Aircraft::draw(const RECT &rect, BOOL isTerrain/* = TRUE*/, BOOL isInstr/* = FALSE*/)
{
	if (isTerrain) {
		glPushMatrix();
			glPushMatrix();
			glTranslatef(0.0f, 0.0f, -5.0f);
			glTranslatef(-1.0f, -1.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			glRotatef(-xrot_, 1.0f, 0.0f, 0.0f);
			glRotatef(-yrot_, 0.0f, 1.0f, 0.0f);
			glRotatef(-zrot_, 0.0f, 0.0f, 1.0f);
			Scene::drawCoordinateSystem();
			glPopMatrix();

			// Render the terrain.
			glPushMatrix();
			glTranslatef(-512.0f, -20.0f, -512.0f);
			terrain_->RenderHeightMap();
			glPopMatrix();

			// Render the skybox
			glPushMatrix();
			glTranslatef(x_, y_, z_);

			glPopMatrix();
			
			glPushMatrix();
			glDisable(GL_BLEND);
			glColor3f(1.0f, 1.0f, 1.0f);
			// -800.0f is an experienced value. 
			//glTranslatef(0.0f, 0.0f, -800.0f);
			glTranslatef(x_, y_, z_);
			// To make the aircraft's coordinate system same as the test environment's coordinate system.
			// First rotate around the y-axis, means heading
			glRotatef(yrot_, 0.0f, 1.0f, 0.0f);
			// Second rotate around the x-axis, means pitch
			glRotatef(-xrot_, 1.0f, 0.0f, 0.0f);
			// Third rotate around the z-axis, means roll
			glRotatef(zrot_, 0.0f, 0.0f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glBegin(GL_TRIANGLES);
				for ( int i = 0; i < (int)meshes_.size(); i++ ) {
					for ( int j = 0; j < (int)meshes_[i].numFaces; j++ ) {
						glNormal3f(meshes_[i].normals[(int) meshes_[i].faces[j].x].x, meshes_[i].normals[(int) meshes_[i].faces[j].x].y, meshes_[i].normals[(int) meshes_[i].faces[j].x].z);
						glVertex3f(meshes_[i].vertices[(int) meshes_[i].faces[j].x].x, meshes_[i].vertices[(int) meshes_[i].faces[j].x].y, meshes_[i].vertices[(int) meshes_[i].faces[j].x].z);

						glNormal3f(meshes_[i].normals[(int) meshes_[i].faces[j].y].x, meshes_[i].normals[(int) meshes_[i].faces[j].y].y, meshes_[i].normals[(int) meshes_[i].faces[j].y].z);
						glVertex3f(meshes_[i].vertices[(int) meshes_[i].faces[j].y].x, meshes_[i].vertices[(int) meshes_[i].faces[j].y].y, meshes_[i].vertices[(int) meshes_[i].faces[j].y].z);

						glNormal3f(meshes_[i].normals[(int) meshes_[i].faces[j].z].x, meshes_[i].normals[(int) meshes_[i].faces[j].z].y, meshes_[i].normals[(int) meshes_[i].faces[j].z].z);
						glVertex3f(meshes_[i].vertices[(int) meshes_[i].faces[j].z].x, meshes_[i].vertices[(int) meshes_[i].faces[j].z].y, meshes_[i].vertices[(int) meshes_[i].faces[j].z].z);
					}
				}
			glEnd();
			glEnable(GL_BLEND);
			glPopMatrix();
		glPopMatrix();
	} else if (isInstr) {
		// Adjust the aircraft's position
		drawWithInstruments(rect);
	} else {
		// No terrain will be drawn
		drawWithAutoSize(rect);
	}
}

void Aircraft::drawModel(void)
{
	glPushMatrix();
	glDisable(GL_BLEND);
	glColor3f(1.0f, 1.0f, 1.0f);
	/*
	 * Whe the client area's size changes, then the aircraft update acoordingly.
	 * And to accommplish this target, we just traslate deeper towards Z-axis negative direction to make
	 * the aircaft smaller
	 */
	glTranslatef(x_, y_, z_);

	// To make the aircraft's coordinate system same as the test environment's coordinate system
	// First rotate around the y-axis, means heading
	glRotatef(yrot_, 0.0f, 1.0f, 0.0f);
	// Second rotate around the x-axis, means pitch
	glRotatef(-xrot_, 1.0f, 0.0f, 0.0f);
	// Third rotate around the z-axis, means roll
	glRotatef(zrot_, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_TRIANGLES);
		for ( int i = 0; i < (int)meshes_.size(); i++ ) {
			for ( int j = 0; j < (int)meshes_[i].numFaces; j++ ) {
				glNormal3f(meshes_[i].normals[(int) meshes_[i].faces[j].x].x, 
					meshes_[i].normals[(int) meshes_[i].faces[j].x].y, 
					meshes_[i].normals[(int) meshes_[i].faces[j].x].z);
				glVertex3f(meshes_[i].vertices[(int) meshes_[i].faces[j].x].x, 
					meshes_[i].vertices[(int) meshes_[i].faces[j].x].y, 
					meshes_[i].vertices[(int) meshes_[i].faces[j].x].z);

				glNormal3f(meshes_[i].normals[(int) meshes_[i].faces[j].y].x, 
					meshes_[i].normals[(int) meshes_[i].faces[j].y].y, 
					meshes_[i].normals[(int) meshes_[i].faces[j].y].z);
				glVertex3f(meshes_[i].vertices[(int) meshes_[i].faces[j].y].x, 
					meshes_[i].vertices[(int) meshes_[i].faces[j].y].y, 
					meshes_[i].vertices[(int) meshes_[i].faces[j].y].z);

				glNormal3f(meshes_[i].normals[(int) meshes_[i].faces[j].z].x, 
					meshes_[i].normals[(int) meshes_[i].faces[j].z].y, 
					meshes_[i].normals[(int) meshes_[i].faces[j].z].z);
				glVertex3f(meshes_[i].vertices[(int) meshes_[i].faces[j].z].x, 
					meshes_[i].vertices[(int) meshes_[i].faces[j].z].y, 
					meshes_[i].vertices[(int) meshes_[i].faces[j].z].z);
			}
		}
	glEnd();
	glEnable(GL_BLEND);
	glPopMatrix();
}