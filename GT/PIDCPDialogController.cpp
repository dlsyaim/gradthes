#include "StdAfx.h"
#include "PIDCPDialogController.h"
#include "FileHandler.h"

CPIDCPDialogController::CPIDCPDialogController(void)
{
}

CPIDCPDialogController::~CPIDCPDialogController(void)
{
}

void CPIDCPDialogController::saveControlParaFile(LPCTSTR baseName, std::vector<ControlPara> *PCPV)
{
	CFileHandler::saveControlParaFile(baseName, PCPV);
}


BOOL CPIDCPDialogController::openControlParaFile(LPCTSTR fileName, std::vector<ControlPara> *PCPV)
{
	return CFileHandler::openControlParaFile(fileName, PCPV);
}

bool CPIDCPDialogController::checkControlParameter(LPCTSTR fileName)
{
	return CFileHandler::checkControlParameter(fileName);
}

void CPIDCPDialogController::updateControlParaFile(std::vector<ControlPara> *PCPV)
{
	return CFileHandler::updateControlParaFile(PCPV);
}
