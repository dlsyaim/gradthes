#include "StdAfx.h"
#include <windows.h>
#include <gl/glut.h>
#include "Scene.h"


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
