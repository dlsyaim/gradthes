#include "StdAfx.h"
#include "ServoActorLim.h"

CServoActorLim::CServoActorLim(void)
{
	for (int i = 0; i < 20; i++) {
		parameters[i] = 0.0;
	}
}

CServoActorLim::~CServoActorLim(void)
{
	
}
