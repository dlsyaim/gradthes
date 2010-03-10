#pragma once
#include "Instrument.h"

class BrakeIndicator :
	public Instrument
{
public:
	BrakeIndicator(void);
	~BrakeIndicator(void);
	void draw(void);
};
