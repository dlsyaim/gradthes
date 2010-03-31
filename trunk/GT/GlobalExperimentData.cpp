#include "StdAfx.h"
#include "GlobalExperimentData.h"

GlobalExperimentData::GlobalExperimentData(void)
{
}

GlobalExperimentData::~GlobalExperimentData(void)
{
}


BOOL GlobalExperimentData::isCommunicationTestPass = FALSE;
BOOL GlobalExperimentData::isControlParameterSet = FALSE;
BOOL GlobalExperimentData::isFlightPathSet = FALSE;
BOOL GlobalExperimentData::isServoActorDemarcated = FALSE;
BOOL GlobalExperimentData::isIMUTestPass = FALSE;
BOOL GlobalExperimentData::isGPSTestPass  = FALSE;