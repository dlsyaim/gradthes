#include "stdafx.h"
#include <windows.h>
#include <GL/glut.h>
#include <vector>

#include "Layer.h"

Layer::Layer(void):switchLayers(NULL)
{
	tex = new Texture;
	tl = new transformationList();
}

Layer::Layer(int _w, int _h):w(_w), h(_h), switchLayers(NULL)
{
	tex = new Texture;
	tl = new transformationList();
}

Layer::~Layer(void)
{
	if (tex)
		delete tex;
	if (tl)
	{
		std::vector<Transformation*>::iterator iter;
		for (iter = tl->begin(); iter != tl->end(); iter++) {
			delete *iter;
		}
		delete tl;
	}
	if (switchLayers)
	{
		std::vector<Layer*>::iterator iter;
		for (iter = switchLayers->begin(); iter != switchLayers->end(); iter++) {
			delete *iter;
		}
		delete switchLayers;
	}
}
