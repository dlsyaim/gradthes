#include "StdAfx.h"
#include <windows.h>
#include <gl/glut.h>
#include <vector>
#include "Scene.h"
#include "Texture.h"

const int gridLines = 15;


Scene::Scene(void)
{
}

Scene::~Scene(void)
{
}

void Scene::drawCoordinateSystem(void)
{
	glDisable(GL_LIGHTING);
	glPushAttrib(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();
	glPopAttrib();
	glEnable(GL_LIGHTING);
}

void Scene::drawCoordinateSystem(LPRECT lpRect)
{
	float length = lpRect->right >= lpRect->bottom ? lpRect->right : lpRect->bottom;
	glDisable(GL_LIGHTING);
	glPushAttrib(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(length, 0.0f, 0.0f);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, length, 0.0f);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, length);
	glEnd();
	glPopAttrib();
	glEnable(GL_LIGHTING);
}


void Scene::drawGrid(LPRECT lpRect)
{
	float length = lpRect->right <= lpRect->bottom ? lpRect->right : lpRect->bottom;
	length /= 120.0f;

	glDisable(GL_LIGHTING);
	glPushAttrib(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINES);
	int i;
	for (i = -gridLines / 2; i <= gridLines / 2; i++) {
		glVertex3f(i * length, 0.0f, gridLines / 2 * length);
		glVertex3f(i * length, 0.0f, -gridLines / 2 * length);

		glVertex3f(-gridLines / 2 * length, 0.0f, i * length);
		glVertex3f(gridLines / 2 * length, 0.0f, i * length);
	}
	glEnd();
	glPopAttrib();
}

void Scene::drawNavigator(void)
{
	glDisable(GL_LIGHTING);
	glPushAttrib(GL_COLOR_BUFFER_BIT);
	

	glPopAttrib();
}

void Scene::drawMapTex(Texture *mapTex, LPRECT lpRect)
{
	if (!mapTex)
		return;
	float length = lpRect->right <= lpRect->bottom ? lpRect->right : lpRect->bottom;
	length = length / 8.0f;


	glPushMatrix();		
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, mapTex->getTexId());		
	glBegin(GL_POLYGON);
	glTexCoord2f(mapTex->getX1(), mapTex->getY1()); glVertex3f(0 + length / 2.0f, 0.0f, 0 + length / 2.0f);
	glTexCoord2f(mapTex->getX2(), mapTex->getY1()); glVertex3f(0 + length / 2.0f, 0.0f, 0 - length / 2.0f);
	glTexCoord2f(mapTex->getX2(), mapTex->getY2()); glVertex3f(0 - length / 2.0f, 0.0f, 0 - length / 2.0f);
	glTexCoord2f(mapTex->getX1(), mapTex->getY2()); glVertex3f(0 - length / 2.0f, 0.0f, 0 + length / 2.0f);
	glEnd();	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}