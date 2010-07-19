#include "StdAfx.h"
#include "FlightExperimentController.h"
#include "FileHandler.h"

CFlightExperimentController::CFlightExperimentController(void)
{
}

CFlightExperimentController::~CFlightExperimentController(void)
{
}

void CFlightExperimentController::saveFlyDataFile(LPCTSTR fileName, std::vector<FlyStateGroup> *pFSG)
{
	CFileHandler::saveFlyDataFile(fileName, pFSG);
}

void CFlightExperimentController::appendFlyDataFile(LPCTSTR fileName, std::vector<FlyStateGroup> *pFSG)
{
	CFileHandler::appendFlyDataFile(fileName, pFSG);
}

void CFlightExperimentController::addFlyDataFileHeader(LPCTSTR fileName, PExperimentData pED)
{
	CFileHandler::addFlyDataFileHeader(fileName, pED);
}
