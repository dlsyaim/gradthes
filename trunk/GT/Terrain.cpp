#include "StdAfx.h"
#include <windows.h>
#include <gl/glut.h>
#include <vector>
#include "Terrain.h"
#include "Texture.h"

Terrain::Terrain(void)
{
	terrainTex = new Texture();
	pHeightMap = new BYTE[MAP_SIZE * MAP_SIZE];
}

Terrain::~Terrain(void)
{
	if (terrainTex)
		delete terrainTex;
	if (pHeightMap)
		delete[] pHeightMap;
}


void Terrain::LoadRawFile(LPSTR strName)
{
	FILE *pFile = NULL;

	pFile = fopen(strName, "rb");									// Open the file in binary mode.

	if (pFile == NULL)												    // Check if the file is existing and opened.
	{
		MessageBox(NULL, "Failed to open the height map file!\nCan't open the height map.", "Error", MB_OK);
		return;														
	}

	fread( pHeightMap, 1, MAP_SIZE * MAP_SIZE, pFile );						// Load .raw file into pHeightMap array

	
	if (ferror(pFile))
	{	
		MessageBox(NULL, "Error reading terrain data!\nCan't get terrain data.", "Error", MB_OK);
	}

	fclose(pFile);													
}

void Terrain::RenderHeightMap(void)
{
	int X = 0, Y = 0;												    // The 2-D coordinates of points
	int x, y, z;													        // The 3-D coordinates of points
	BOOL bSwitchSides = FALSE;

	if (!pHeightMap)												// Check the pHeightMap
	{
		return;
	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, terrainTex->getTexId());						

	glBegin(GL_TRIANGLE_STRIP);										

	for (X = 0; X <= MAP_SIZE; X += STEP_SIZE)						
	{
		if (bSwitchSides)											   // Check whether read the height map from the opposite direction or not
		{	
			// Because we need to make the triangle to be ____,  we must specify the (X, y, Y) first.
			// Render the terrain in the current X coordinate
			for (Y = MAP_SIZE; Y >= 0; Y -= STEP_SIZE)				
			{
				// Get the lower-left point's (X, Y, Z)
				x = X;
				y = Height(X, Y);
				z = Y;

				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);

				// Get the lower-right point's (X, Y, Z)
				x = X + STEP_SIZE;
				y = Height(X + STEP_SIZE, Y);
				z = Y;

				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);
			}
		} else {
			for (Y = 0; Y <= MAP_SIZE; Y += STEP_SIZE)				
			{
				// Because we need to make the triangle to be ____,  we must specify the (X + STEP_SIZE, y, Y) first.
				// Get the upper-right point's (X, Y, Z)
				x = X + STEP_SIZE;
				y = Height(X + STEP_SIZE, Y);
				z = Y;

				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);

				// Get the upper-left point's (X, Y, Z)
				x = X;
				y = Height(X, Y);
				z = Y;

				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);
			}
		}
		bSwitchSides = !bSwitchSides;								// Change the direction of rendering
	}
	glEnd();					
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

int Terrain::Height(int X, int Y)
{
	int x = X % MAP_SIZE;
	int y = Y % MAP_SIZE;

	if (!pHeightMap) 
		return 0;

	return pHeightMap[x + y * MAP_SIZE];
}

void Terrain::SetTextureCoord(float x, float z)
{
	glTexCoord2f((float) x / (float) MAP_SIZE, - (float) z / (float) MAP_SIZE);
}