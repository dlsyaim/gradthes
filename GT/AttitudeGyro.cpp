#include "stdafx.h"
#include <stdio.h>														
#include <olectl.h>														
#include <math.h>													
#include <GL\gl.h>	
#include <string>
#include <vector>
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