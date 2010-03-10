#pragma once
#include "Panel.h"
#include "Camera.h"
#include "Aircraft.h"
#include "Tools.h"

class Renderer
{
public:
	// Construction / deconstruction
	Renderer(void);
	Renderer(int _length);
	~Renderer(void);

	// Load configuration
	BOOL loadConfiguration();

	// Draw function
	void draw(LPRECT lpRect);
	// Draw fonts
	void drawFonts(void);	
	
	// Update the instruments' data.
	void updateInstrumentsData();
	void updateInstrumentsData(FlyState *fs);
	BOOL updateInstrumentsData(CString aLine);
	
	// Update camera
	void updateCamera(void);
	// Update camera
	void updateCamera(int virtualKey);	
	void updateCamera(LPPOINT lpPoint);

	// Setter and getter
	inline void setBase(GLuint base) {this->base = base;}
	inline GLuint getBase(void){return base;}
	// Setter and getter
	inline void setStat(double *stat) {this->stat = stat;}
	inline double* getStat(void) {return stat;}
	// Setter and getter
	inline void setIsMultiport(BOOL isMultiport) {this->isMultiport = isMultiport;}
	inline BOOL getIsMultiport(void) {return isMultiport;}

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

// Operations
private:
	// Draw function
	void draw(void);
	// Initialize the illumination and material
	void initializeIlluminationAndMaterial(void);
	// Update stat array
	void updateStat(FlyState* fs);

};
