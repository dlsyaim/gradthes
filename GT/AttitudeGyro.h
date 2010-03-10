#pragma once
#include "Instrument.h"

// Instrument indicates the pitch and roll of the helicopter.
class AttitudeGyro :
	public Instrument
{
public:
	AttitudeGyro(void);
	~AttitudeGyro(void);
	inline void setHeading(double heading){this->heading = heading;}
	inline double getHeading(void){return heading;}
	inline void setPitch(double pitch){this->pitch = pitch;}
	inline double getPitch(void){return pitch;}
	inline void setRoll(double roll) {this->roll = roll;}
	inline double getRoll(void){return roll;}

	// Update pitch
	void updatePitch(double pitchAngle);
	// Update roll 
	void updateRoll(double rollAngle);
private:
	double heading;
	double pitch;
	double roll;
};
