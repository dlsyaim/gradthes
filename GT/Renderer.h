#pragma once
#include "Panel.h"
#include "Camera.h"
#include "Aircraft.h"
#include "Tools.h"

#define NAVIGATOR_LENGTH 5

class Renderer
{
public:
	// Construction / deconstruction
	Renderer(void);
	Renderer(int _length);
	~Renderer(void);

	// Load configuration
	BOOL loadConfiguration();

	/*
	 * Draw functions
	 */
	void draw(LPRECT lpRect, int renderMode);
	// Draw fonts
	void drawFonts(void);	
	
	// Update camera
	void updateCamera(void);
	void updateCamera(int virtualKey);	
	void updateCamera(LPPOINT lpPoint);
	// Reset camera
	void resetCamera(int m);

	// Setters and getters
	inline void setBase(GLuint base) {this->base = base;}
	inline GLuint getBase(void){return base;}
	inline void setStat(double *stat) {this->stat = stat;}
	inline double* getStat(void) {return stat;}
	inline void setIsMultiport(BOOL isMultiport) {this->isMultiport = isMultiport;}
	inline BOOL getIsMultiport(void) {return isMultiport;}

	void updateData(void);
	void updateData(CString aLine);
	void updateData(pIMUTestData itd);
	void updateData(pOPTTRACETestData otd);
	void updateData(pFlyState fs);

	// Update the flight path data
	inline void setPPath(std::vector<PathPointData*> *pPath) {this->pPath = pPath;}

	inline void setSelect(pPathPointData slc){selectedPoint = slc;}
	inline void setSelectedNavi(int navi) {this->navi = navi;}
	inline void setMapTex(Texture* mapTex) {this->mapTex = mapTex;}

// Attributes
private:
	// Panel
	Panel *panel;
	// Camera
	CCamera* camera;
	// First display list name
	GLuint base;
	// Flight statistics
	double *stat;
	// Length
	int length;
	// Is multiport
	BOOL isMultiport;
	// Aircraft model.
	Aircraft* aircraft;
	// Path data
	std::vector<PathPointData*> *pPath;
	// The size of the current view
	LPRECT lpRect;
	// Quadric object
	GLUquadricObj* qobj;
	// Draw navigator or not
	pPathPointData selectedPoint;
	// Selected navigator
	int navi;
	// Map texture
	Texture* mapTex;

// Operations
	// Draw function with drawing instruments
	void draw(void);
	// Draw flight path
	void drawPath(void);
	// Draw function without drawing instruments
	void drawWithoutInstruments(void);
	// Initialize the illumination and material
	void initializeIlluminationAndMaterial(void);
	
	// Update stat array by FlyState, IMUTestData and OPTTRACETestData
	void updateStat(pFlyState fs);
	void updateStat(pIMUTestData itd);
	void updateStat(pOPTTRACETestData otd);

	// Update the instruments' data by FlyState, One-line-of-file
	void updateInstrumentsData(void);

	// Draw a navigator
	void drawNavigator(void);
};
