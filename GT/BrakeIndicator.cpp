#include "stdafx.h"
#include <stdio.h>														
#include <olectl.h>														
#include <math.h>													
#include <GL\gl.h>	
#include <string>
#include <vector>
#include <algorithm>

#include "Util.h"
#include "BrakeIndicator.h"

BrakeIndicator::BrakeIndicator(void)
{
}

BrakeIndicator::~BrakeIndicator(void)
{
}

// Because brake indicator has switch type of Layer
// So need to special draw function.
void BrakeIndicator::draw(void)
{
	Layer* la;
	layerList* switchLayerList;
	Texture* tex;
	transformationList *tl;
	// Sort the layers in descend order
	sort(ll->begin(), ll->end(), descend);
	/*
	 * When choosing GL_SRC_ALPHA and GL_SRC_ALPHA, 
	 * so we got blending effects.
	 */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
	glPushMatrix();
	glTranslatef((GLfloat)x, (GLfloat)y, 0);
	// Render each Layer
	for (int i = 0; i < (int)ll->size(); i++) {
		glPushMatrix();
		la = (*ll)[i];
		// If this Layer has switch layers, then choose one of state
		switchLayerList = la->getSwitchLayers();
		if (switchLayerList != NULL) {
			la = (*switchLayerList)[0];
		}
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
