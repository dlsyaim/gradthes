#pragma once

class CSteeringGear
{
public:
	CSteeringGear(double _roll = 0.0, double _pitch = 0.0, double _collectivePitch = 0.0, double _direction = 0.0):
	roll(_roll),
	pitch(_pitch),
	collectivePitch(_collectivePitch),
	direction(_direction)
	{}
	~CSteeringGear(void);
	
	inline void setRoll(double roll) {this->roll = roll;}
	inline double getRoll(void) {return roll;}

	inline void setPitch(double pitch) {this->pitch = pitch;}
	inline double getPitch(void) {return pitch;}

	inline void setCollectivePitch(double collectivePitch) {this->collectivePitch = collectivePitch;}
	inline double getCollectivePitch(void){return collectivePitch;}

	inline void setDirection(double direction) {this->direction = direction;}
	inline double getDirection(void) {return direction;}

private:
	double roll, pitch, collectivePitch, direction;
};
