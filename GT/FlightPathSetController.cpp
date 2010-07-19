#include "StdAfx.h"
#include "FlightPathSetController.h"
#include "FileHandler.h"

CFlightPathSetController::CFlightPathSetController(void)
{
}

CFlightPathSetController::~CFlightPathSetController(void)
{
}

void CFlightPathSetController::savePathFile(LPCTSTR baseName, std::vector<pPathPointData> *pPPD)
{
	CFileHandler::savePathFile(baseName, pPPD);
}

bool CFlightPathSetController::openPathFile(LPCTSTR fileName, std::vector<pPathPointData> *pPPD)
{
	return CFileHandler::openPathFile(fileName, pPPD);
}

bool CFlightPathSetController::checkPath(LPCTSTR fileName)
{
	return CFileHandler::checkPath(fileName);
}

void CFlightPathSetController::updatePathFile(std::vector<pPathPointData> *pPPD)
{
	return CFileHandler::updatePathFile(pPPD);
}