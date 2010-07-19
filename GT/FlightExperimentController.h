#pragma once
#include <vector>
#include "GSDefinition.h"


class CFlightExperimentController
{
public:
	CFlightExperimentController(void);
	~CFlightExperimentController(void);

	void saveFlyDataFile(LPCTSTR fileName, std::vector<FlyStateGroup> *pFSG);
	void appendFlyDataFile(LPCTSTR fileName, std::vector<FlyStateGroup> *pFSG);
	void addFlyDataFileHeader(LPCTSTR fileName, PExperimentData pED);
};
