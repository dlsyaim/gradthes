#pragma once

#include "VRMLLoader.h"

class Terrain;

class Aircraft
{
public:
	Aircraft(void);
	virtual ~Aircraft(void);

	// Load aircraft
	void loadAircraft(const char* filePath);

	// Draw function.
	void draw(const RECT &rect, BOOL isTerrain = TRUE, BOOL isInstr = FALSE);

	// Setters and getters
	inline void setXrot(double xrot) {xrot_ = xrot;}
	inline double getXrot(void) {return xrot_;}
	inline void setYrot(double yrot) {yrot_ = yrot;}
	inline double getYrot(void) {return yrot_;}
	inline void setZrot(double zrot) {zrot_ = zrot;}
	inline double getZrot(void) {return zrot_;}

	inline void setX(float x) {x_ = x;}
	inline float getX(void) {return x_;}
	inline void setY(float y) {y_ = y;}
	inline float getY(void) {return y_;}
	inline void setZ(float z) {z_ = z;}
	inline float getZ(void) {return z_;}
	
	// Update data
	void update(const double *stat);
	void update(const FlyState& fs);
	void update(const IMUTestData& itd);
	void update(const OPTTRACETestData& otd);

private:
// Attributes
	std::vector<Mesh> meshes_;
	double xrot_, yrot_, zrot_;
	// Position
	float x_, y_, z_;
	// Terrain
	Terrain *terrain_;

// Operations	
	// When the client area's size changes, then the aircraft update acoordingly.
	void drawWithAutoSize(const RECT &rect);
	
	// When the instruments are drawn, so the aircraft adjust its position
	void drawWithInstruments(const RECT &rect);

	void drawModel(void);
};
