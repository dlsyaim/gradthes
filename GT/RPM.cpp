#include "stdafx.h"
#include <stdio.h>														
#include <olectl.h>														
#include <math.h>													
#include <GL\glut.h>	
#include <string>
#include <vector>
#include <algorithm>
#include "RPM.h"
#include "Util.h"

RPM::RPM(void):Instrument(), turnAngle(-150.0)
{
}

RPM::~RPM(void)
{
}

// Virtual render function
void RPM::draw(void)
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
	glTranslatef(x, y, 0.0f);
	// Render each Layer include needles
	for (int i = 0; i < (int)ll->size(); i++) {
		glPushMatrix();
		la = (*ll)[i];
		tex = la->getTex();
		tl = la->getTl();
		if (tex) {
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glBindTexture(GL_TEXTURE_2D, tex->getTexId());		
			glEnable(GL_TEXTURE_2D);
			// First move to the proper position and turn to the proper orientation.
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

void RPM::updateTurnAngle(double deltaAngle)
{
	// The last Layer is the needle
	Layer* needle = (*ll)[ll->size() - 1];
	transformationList *tl = needle->getTl();
	// Just update the paramters of the function glRotatef
	for (int i = 0; i < (int)tl->size(); i++) {
		if ((*tl)[i]->getType() == Transformation::ROTATION) {
			turnAngle += deltaAngle;
			if (turnAngle <= -150) {
				turnAngle = -150;
			} else if (turnAngle >= 150) {
				turnAngle = 150;
			}
			(*tl)[i]->setOffset(turnAngle);
		}
	}
}
