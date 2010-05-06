#pragma once

class Texture;

class Scene
{
public:
	Scene(void);
	~Scene(void);

	// In the lower-left corner, draw a little 3-d coordinate system.
	static void drawCoordinateSystem(void);
	static void drawCoordinateSystem(LPRECT lpRect);

	// In the X-Z plane, draw a grid
	static void drawGrid(LPRECT lpRect);

	// Draw a navigator
	static void drawNavigator(void);

	// Draw a map texture
	static void drawMapTex(Texture* mapTex, LPRECT lpRect);

};
