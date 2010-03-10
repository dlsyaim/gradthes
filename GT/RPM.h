#pragma once
#include "Instrument.h"

// Instrument indicates revolutions per minutes(RPM).
class RPM :
	public Instrument
{
public:
	RPM(void);
	~RPM(void);
	void draw(void);
	inline void setTurnAngle(double turnAngle){this->turnAngle = turnAngle;}
	inline double getTurnAngle(void){return turnAngle;}
	// Update the revolutions per minutes
	void updateTurnAngle(double deltaAngle);
private:
	double turnAngle;
};
