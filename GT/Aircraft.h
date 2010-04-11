#pragma once
#include "VRMLLoader.h"
#include "Tools.h"
class Terrain;
class Aircraft
{
public:
	Aircraft(void);
	~Aircraft(void);

	// 
	inline void setMeshes(std::vector<Mesh> meshes) {this->meshes = meshes;}
	inline std::vector<Mesh> getMeshes(void) {return meshes;}

	// 
	void loadAircraft(void);

	// 
	void loadAircraft(char* filePath);

	// Draw funtion.
	void draw(void);

	// Draw function.
	void draw(LPRECT lpRect);

	// Setters and getters
	inline void setXrot(double xrot) {this->xrot = xrot;}
	inline double getXrot(void) {return xrot;}
	inline void setYrot(double yrot) {this->yrot = yrot;}
	inline double getYrot(void) {return yrot;}
	inline void setZrot(double zrot) {this->zrot = zrot;}
	inline double getZrot(void) {return zrot;}

	inline void setX(double x) {this->x = x;}
	inline double getX(void) {return x;}

	inline void setY(double y) {this->y = y;}
	inline double getY(void) {return y;}

	inline void setZ(double z) {this->z = z;}
	inline double getZ(void) {return z;}
	// 
	void update(double *stat);
	void update(FlyState* fs);

private:
	std::vector<Mesh> meshes;

	double xrot, yrot, zrot;
	// Terrain
	Terrain *terrain;

	// Position
	double x, y, z;


};