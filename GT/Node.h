#pragma once

class CNode
{
public:
	CNode( int _id = -1, double _x = 0.0, double _y = 0.0, double _z = 0.0, long _hoveringInterval = 0): id(_id), x(_x), y(_y), z(_z), hoveringInterval(_hoveringInterval){}
	~CNode(void);

	inline void setX(double x) {this->x = x;}
	inline double getX(void) {return x;}
	inline void setY(double y) {this->y = y;}
	inline double getY(void) {return y;}
	inline void setZ(double z) {this->z = z;}
	inline double getZ(void) {return z;}
	inline void setHoveringInterval(long hoveringInterval) {this->hoveringInterval = hoveringInterval;}
	inline long getHoveringInterval(void) {return hoveringInterval;}
	inline void setId(int id) {this->id = id;}
	inline int getId(void) {return id;}


private:
	int id;
	double x, y, z;
	long hoveringInterval;
};
