#include "stdafx.h"
#include <windows.h>
#include <GL/glut.h>
#include <vector>

#include "RPM.h"
#include "AttitudeGyro.h"
#include "DirectionalGyro.h"
#include "Texture.h"
#include "Panel.h"

Panel::Panel(void)
{
	inLi = new instrumentList();
}

Panel::~Panel(void)
{
	if (inLi)
		delete inLi;
}

void Panel::updateRPM(double thelta)
{
	// Because the RPM is the first Instrument
	((RPM*)(*inLi)[0])->updateTurnAngle(thelta);
}

// The parameter passed is the absolute angle.
void Panel::updateAttitudeGyro(double angle, BOOL pitchOrRoll)
{
	// We assume that the attitude gyro is the 7th instrument.
	if (pitchOrRoll) {
		((AttitudeGyro*)(*inLi)[6])->updatePitch(angle);
	} else {
		((AttitudeGyro*)(*inLi)[6])->updateRoll(angle);
	}
}

// The parameter passed is the absolute heading angle.
void Panel::updateDirectonalGyro(double heading)
{
	// We assume that the directional gyro is the 9th instrument.
	((DirectionalGyro*)(*inLi)[9])->updateHeading(heading);
}

// Set the background
void Panel::setBg(std::string bg) 
{
	if (bg.empty())
		return;
	this->bg = bg.substr(8, bg.size() - 8 - 3);
	background = new Texture(this->bg);
	if (!background->loadTexture()) {
		delete background;
		background = NULL;
	}
}

// Draw function.
void Panel::draw(void)
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0.0f, 0.0f, -635.0f);	
	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);

	// First render the background
	if (background) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, background->getTexId());
		glBegin(GL_POLYGON);
			glTexCoord2f(background->getX1(), background->getY1()); glVertex3f(-630.0f, -365.0f, 0.0f);
			glTexCoord2f(background->getX2(), background->getY1()); glVertex3f(0.0f, -365.0f, 0.0f);
			glTexCoord2f(background->getX2(), background->getY2()); glVertex3f(0.0f, 40.0f, 0.0f);
			glTexCoord2f(background->getX1(), background->getY2()); glVertex3f(-635.0f, 40.0f, 0.0f);
		glEnd();
	}
	
	// Render each Instrument.
	for (int i = 0; i < (int)inLi->size(); i++) {		
		(*inLi)[i]->draw();
	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

