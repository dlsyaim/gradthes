#include "stdafx.h"
#include <windows.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include "Util.h"
#include "Altimeter.h"

Altimeter::Altimeter(void)
{
}

Altimeter::~Altimeter(void)
{
}

void Altimeter::draw(void)
{
	Layer* la;
	Texture* tex;
	transformationList *tl;
	// Sort the layers in descend order
	sort(ll->begin(), ll->end(), descend);
	/*
	 * When choosing GL_SRC_ALPHA and GL_ONE_MINUS_SRC_ALPHA, 
	 * then we should render the bigger part of the Instrument, which is glare shield. 
	 */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glTranslatef((GLfloat)x, (GLfloat)y, 0);
	// Render each Layer
	for (int i = 0; i < (int)ll->size(); i++) {
		if (i == 3) {
			glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA);
		} else {
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		glPushMatrix();
		la = (*ll)[i];
		tex = la->getTex();
		tl = la->getTl();
		if (tex) {
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, tex->getTexId());		
			// First move to the proper position and the proper orientation.
			for (int j = 0; j < (int)tl->size(); j++) {
				(*tl)[j]->doTransform();
			}
			glBegin(GL_POLYGON);
			glTexCoord2f(tex->getX1(), tex->getY1()); glVertex3f(0 - la->getW() / 2.0f, 0 - la->getH() / 2.0f, 0.0f);
			glTexCoord2f(tex->getX2(), tex->getY1()); glVertex3f(0 + la->getW() / 2.0f, 0 - la->getH() / 2.0f, 0.0f);
			glTexCoord2f(tex->getX2(), tex->getY2()); glVertex3f(0 + la->getW() / 2.0f, 0 + la->getH() / 2.0f, 0.0f);
			glTexCoord2f(tex->getX1(), tex->getY2()); glVertex3f(0 - la->getW() / 2.0f, 0 + la->getH() / 2.0f, 0.0f);
			glEnd();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glDisable(GL_BLEND);
}
