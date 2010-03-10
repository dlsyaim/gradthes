#pragma once

#ifndef STEP_SIZE
#define STEP_SIZE 16
#endif

#ifndef MAP_SIZE
#define MAP_SIZE 1024
#endif

class Texture;
class Terrain
{
public:
	Terrain(void);
	~Terrain(void);

	void LoadRawFile(LPSTR strName);
	void RenderHeightMap();
	// Return the height value according to the X and Y
	int Height(int X, int Y);
	void SetTextureCoord(float x, float z);

	// getter
	inline Texture* getTerrainTex(void){return terrainTex;}
private:
	Texture *terrainTex;
	
	// Height map data
	BYTE* pHeightMap;
			
};
