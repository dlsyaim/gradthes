#include "StdAfx.h"
#include "SteeringGearLim.h"

CSteeringGearLim::CSteeringGearLim(void)
{
	for (int i = 0; i < 20; i++) {
		parameters[i] = 0.0;
	}
}

CSteeringGearLim::~CSteeringGearLim(void)
{
	
}
