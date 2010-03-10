#pragma once
#include "Instrument.h"

class DirectionalGyro :
	public Instrument
{
public:
	DirectionalGyro(void);
	~DirectionalGyro(void);

	inline void setHeading(double heading){this->heading = heading;}
	inline double getHeading(void){return heading;}

	void updateHeading(double delta);

private:
	double heading;
};
