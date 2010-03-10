#pragma once
#include "Instrument.h"

class Altimeter :
	public Instrument
{
public:
	Altimeter(void);
	~Altimeter(void);

	// Override the virtual function
	void draw(void);
};
