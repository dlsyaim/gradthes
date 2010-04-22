#include "stdafx.h"
#include <stdio.h>														
#include <olectl.h>														
#include <math.h>													
#include <GL\gl.h>	
#include <string>
#include <vector>
#include <algorithm>

#include "Util.h"
#include "Instrument.h"

Instrument::Instrument(void):x(0), y(0), width(0), height(0)
{
	ll = new layerList();
}

Instrument::~Instrument(void)
{
	if (ll)
	{
		std::vector<Layer*>::iterator iter;
		for (iter = ll->begin(); iter != ll->end(); iter++) {
			delete *iter;
		}
		delete ll;
	}
}

void Instrument::draw(void)
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