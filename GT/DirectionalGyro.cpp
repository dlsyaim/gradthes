#include "stdafx.h"											
#include <GL\gl.h>
#include <vector>
#include "util.h"
#include "DirectionalGyro.h"

DirectionalGyro::DirectionalGyro(void)
{
}

DirectionalGyro::~DirectionalGyro(void)
{
}

void DirectionalGyro::updateHeading(double heading)
{
	// After sorting, the compass rose Layer is 2nd Layer.
	Layer *compassRose = (*ll)[1];
	transformationList* tl = compassRose->getTl();
	Transformation *tf = (*tl)[0];
	
	// Because the heading is the absolute angle, not the incremental.
	//double offset = tf->getOffset();
	//offset += (delta * tf->getScale());
	tf->setOffset(heading);

}
