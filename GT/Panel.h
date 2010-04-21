#pragma once
#include "Instrument.h"

class Texture;
/*
 * Panel is a container which holds all kinds of instruments.
 */
class Panel
{
public:
	Panel(void);
	~Panel(void);

	// Setters and getters.
	inline void setInLi(instrumentList* inLi) {this->inLi = inLi;}
	inline instrumentList* getInLi(void) {return inLi;}
	inline void setH(int h) {this->h = h;}
	inline int getH(void){return h;}
	inline void setW(int w) {this->w = w;}
	inline int getW(void){return w;}
	inline void setYoffset(int yoffset) {this->yoffset = yoffset;}
	inline int getYoffset(void) {return yoffset;}
	inline void setViewHeight(int viewHeight){this->viewHeight = viewHeight;}
	inline int getViewHeight(void){return viewHeight;}
	inline void setName(std::string name){this->name = name;}
	inline std::string getName(void){return name;}
	void setBg(std::string bg);
	inline std::string getBg(void){return bg;}
	
	void updateRPM(double theta);
	void updateAttitudeGyro(double angle, BOOL pitchOrRoll);
	void updateDirectonalGyro(double heading);

	// Draw function.
	void draw(LPRECT lpRect);
private:
	instrumentList* inLi;
	// Position
	int w, h;
	// Y-offset
	int yoffset;
	// View height
	int viewHeight;
	// Name
	std::string name;
	// Background
	std::string bg;
	// Background texture
	Texture *background;

};
