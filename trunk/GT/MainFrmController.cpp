#include "StdAfx.h"
#include "MainFrmController.h"
#include "FileHandler.h"

CMainFrmController::CMainFrmController(void)
{
}

CMainFrmController::~CMainFrmController(void)
{
}


BOOL CMainFrmController::openModelFile(LPCTSTR fileName, PHelicopterModel pHM)
{
	return CFileHandler::openModelFile(fileName, pHM);
}

void CMainFrmController::saveExperimentConfiguration(void)
{
	return CFileHandler::saveExperimentConfiguration();
}

void CMainFrmController::saveExperimentConfiguration(LPCTSTR filePath)
{
	return CFileHandler::saveExperimentConfiguration(filePath);
}