#include "stdafx.h"
#include <stdio.h>	
#include <atlbase.h>
#include <msxml2.h>
#include <iostream>
#include <GL\gl.h>
#include <vector>
#include <string>
#include "Transformation.h"

Transformation::Transformation(void):
offset(0),
minR(1),
maxR(0),
scale(-100)
{
}

Transformation::Transformation(float _w_scale, float _h_scale):
offset(0), 
w_scale(_w_scale), 
h_scale(_h_scale),
minR(1),
maxR(0),
scale(-100)
{
}

Transformation::~Transformation(void)
{
}


void Transformation::doTransform(void)
{
	switch (type) {
		case ROTATION:
			glRotatef((GLfloat)offset, 0.0, 0.0, 1.0);
			break;
		case XSHIFT:
			glTranslatef((GLfloat)offset, 0.0, 0.0);
			break;
		case YSHIFT:
			glTranslatef(0.0, (GLfloat)offset, 0.0);
			break;
		default:
			break;
	}
}