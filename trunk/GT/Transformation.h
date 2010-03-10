#pragma once

class Transformation
{
public:
	enum TRANSFORMATION_TYPE {
		ROTATION,
		XSHIFT,
		YSHIFT
	};
	Transformation(void);
	Transformation(float _w_scale, float _h_scale);
	~Transformation(void);
	inline void setOffset(double offset){
		//if (type == XSHIFT) {
		//	this->offset = (int)(offset * w_scale);
		//} else if (type == YSHIFT) {
		//	this->offset = (int)(offset * h_scale);
		//}
		this->offset = offset;
	}
	inline double getOffset(void){return offset;}
	inline void setType(TRANSFORMATION_TYPE type) {this->type = type;}
	inline TRANSFORMATION_TYPE getType(void){return type;}

	inline void setType(std::string type) {
		const char* yshift = "y-shift";
		const char* xshift = "x-shift";
		const char* rotation = "rotation";
		if (!strcmp(yshift, type.c_str())) {
			this->type = YSHIFT;
		}

		if (!strcmp(xshift, type.c_str())) {
			this->type = XSHIFT;
		}

		if (!strcmp(rotation, type.c_str())) {
			this->type = ROTATION;
		}
	}

	inline float getW_scale(void) {return w_scale;}
	inline void setW_scale(float w_scale) {this->w_scale = w_scale;}

	inline float getH_scale(void) {return h_scale;}
	inline void setH_scale(float h_scale){this->h_scale = h_scale;}

	inline double getMaxR(void){return maxR;}
	inline void setMaxR(double maxR){this->maxR = maxR;}

	inline double getMinR(void){return minR;}
	inline void setMinR(double minR){this->minR = minR;}

	inline double getScale(void){return scale;}
	inline void setScale(double scale){this->scale = scale;}

	void doTransform(void);
private:
	TRANSFORMATION_TYPE type;
	// Offset.
	double offset;
	// Scale factor.
	float w_scale, h_scale;
	// Min, max, and scale
	double maxR, minR, scale;
};

typedef std::vector<Transformation*> transformationList;
