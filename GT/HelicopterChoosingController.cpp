#include "StdAfx.h"
#include "HelicopterChoosingController.h"
#include "FileHandler.h"

CHelicopterChoosingController::CHelicopterChoosingController(void)
{
}

CHelicopterChoosingController::~CHelicopterChoosingController(void)
{
}


void CHelicopterChoosingController::saveModelFile(PHelicopterModel pHM)
{
	CFileHandler::saveModelFile(pHM);
}

void CHelicopterChoosingController::updateModelFile(PHelicopterModel pHM)
{
	CFileHandler::updateModelFile(pHM);
}

bool CHelicopterChoosingController::checkModel(LPCTSTR fileName)
{
	return CFileHandler::checkModel(fileName);
}