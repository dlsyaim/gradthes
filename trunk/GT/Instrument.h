#pragma once
#include "Layer.h"

class Instrument
{
public:
	Instrument(void);
	Instrument(int _x, int _y, int _width, int _height):x(_x), y(_y), width(_width), height(_height){}
	virtual ~Instrument(void);
	// Getters and setters
	inline void setX(int x){this->x = x;}
	inline int getX(void){return x;}
	inline void setY(int y){this->y = y;}
	inline int getY(void){return y;}
	inline void setWidth(int width){this->width = width;}
	inline int getWidth(void){return width;}
	inline void setHeight(int height){this->height = height;}
	inline int getHeight(void){return height;}
	inline void setW_base(int w_base){
		this->w_base = w_base;
		if (width == 0) {
			width = w_base;
		}
		w_scale = (float) width / w_base;
	}
	inline int getW_base(void){return w_base;}
	inline void setH_base(int h_base){
		this->h_base = h_base;
		if (height == 0) {
			height = h_base;
		}
		h_scale = (float) height / h_base;
	}
	inline int getH_base(void){return h_base;}
	inline void setName(std::string name) {this->name = name;}
	inline std::string getName(void){return name;}
	inline void setFullName(std::string fullName){this->fullName = fullName;}
	inline std::string getFullName(void){return fullName;}
	inline void setInPath(std::string inPath) {this->inPath = inPath.substr(3);}
	inline std::string getInPath(void) {return inPath;}
	inline void setLl(layerList* ll) {this->ll = ll;}
	inline layerList* getLl(void){return ll;}

	inline float getW_scale(void) {return w_scale;}
	inline float getH_scale(void) {return h_scale;}

	virtual void draw(void);
	
protected:
	// Position
	int x, y;
	// Size
	int width, height;
	// Name
	std::string name, fullName;
	// Include path
	std::string inPath;
	// Layer list
	layerList* ll;
	// factor
	float w_scale, h_scale;
	// base
	int w_base, h_base;
};

typedef std::vector<Instrument*> instrumentList;
