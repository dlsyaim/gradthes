#pragma once

class GlobalExperimentData
{
public:
	GlobalExperimentData(void);
	~GlobalExperimentData(void);
public:
	static BOOL isCommunicationTestPass;
	static BOOL isServoActorDemarcated;
	static BOOL isIMUTestPass;
	static BOOL isGPSTestPass;
	static BOOL isFlightPathSet;
	static BOOL isControlParameterSet;
};
