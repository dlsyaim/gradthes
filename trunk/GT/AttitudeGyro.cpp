#include "stdafx.h"
#include <stdio.h>														
#include <olectl.h>														
#include <math.h>													
#include <GL\gl.h>	
#include <string>
#include <vector>
#include <algorithm>
#include "Util.h"
#include "AttitudeGyro.h"

AttitudeGyro::AttitudeGyro(void)
{
}

AttitudeGyro::~AttitudeGyro(void)
{
}

void AttitudeGyro::updatePitch(double pitchAngle)
{
	// We assume the 4th layer is the pitch layer acoording to the configuration file and the sorting order.
	Layer* pitchLayer = (*ll)[3];
	// And we just update the y-shift value, which is the second Transformation.
	transformationList* tl = pitchLayer->getTl();
	Transformation* tf = (*tl)[1];
	/*double offsetPitch = tf->getOffset();
	offsetPitch += (deltaPitch * tf->getScale());
	if (offsetPitch <= tf->getMinR()) {
		offsetPitch = tf->getMinR();
	} else if (offsetPitch >= tf->getMaxR()) {
		offsetPitch = tf->getMaxR();
	}*/

	// Limit the pitchAngle to the range -20 to 20
	pitchAngle = pitchAngle / 90.0 * 20.0;

	tf->setOffset(-pitchAngle);
}

void AttitudeGyro::updateRoll(double rollAngle)
{
	// We also know the 2nd layer is the roll layer acoording to the configuration file.
	Layer* rollLayer = (*ll)[1];
	// And we know there is just ROTATION Transformation.
	transformationList *tl = rollLayer->getTl();
	Transformation *tf = (*tl)[0];
	/*double offsetRoll = tf->getOffset();
	offsetRoll += (deltaRoll * tf->getScale());
	if (offsetRoll <= tf->getMinR()) {
		offsetRoll = tf->getMinR();
	} else if (offsetRoll >= tf->getMaxR()) {
		offsetRoll = tf->getMaxR();
	}*/
	tf->setOffset(rollAngle);

}

void AttitudeGyro::draw(void)
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
		if (i != 1) {
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
	}
	glPushMatrix();
			la = (*ll)[1];
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
	
	glPopMatrix();
	glDisable(GL_BLEND);
}