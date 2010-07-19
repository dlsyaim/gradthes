#include "StdAfx.h"
#include "FileHandler.h"
#include "Singleton.h"

CFileHandler::CFileHandler(void)
{
}

CFileHandler::~CFileHandler(void)
{
}

BOOL CFileHandler::openModelFile(LPCTSTR fileName, PHelicopterModel pHM)
{
	const int LEN = 256;
	char filePath[LEN];
	memset(filePath, 0, LEN);

	const char *prefix = "modelfiles/";
	strcat_s(filePath, LEN, prefix);
	strcat_s(filePath, LEN, fileName);

	std::ifstream ifs(filePath, std::ios::in);
	if (ifs.fail()) {
		return FALSE;
	}

	int version;
	ifs>>version;
	ifs.seekg(1, std::ios::cur);
	ifs.read((char *)pHM, sizeof(HelicopterModel));
	ifs.close();	

	CSingleton *instance = CSingleton::getInstance();
	instance->setCurHelicopterModelFileName(fileName);

	return TRUE;
}

void CFileHandler::saveModelFile(PHelicopterModel pHM)
{
	if (!pHM)
		return;

	const int LEN = 256;
	char filePath[LEN];
	memset(filePath, 0, LEN);
	const char* prefix = "modelfiles/";
    strcat_s(filePath, LEN, prefix);
	strcat_s(filePath, LEN, pHM->helicopterName);

	// First read the index file of the models
	int serialNumber = getModelSerialNumber(pHM->helicopterName);
	CTime t = CTime::GetCurrentTime();  
	CString timeString = t.Format("_%Y-%m-%d_");
	strcat_s(filePath, LEN, timeString);
	timeString.Empty();
	timeString.Format("%d", serialNumber);
	strcat_s(filePath, LEN, timeString);

	const int version = 0;
	std::ofstream ofs(filePath, std::ios::out | std::ios::binary);
	ofs<<version<<" ";
	ofs.write((char *)pHM, sizeof(HelicopterModel));
	ofs.close();

	// Add an item into the index file
	addModelIndexFile(filePath);

	CSingleton *instance = CSingleton::getInstance();
	instance->setCurHelicopterModelFileName(filePath + 11);
	
}

void CFileHandler::updateModelFile(PHelicopterModel pHM)
{
	if (!pHM)
		return;

	const int LEN = 256;
	char filePath[LEN];
	memset(filePath, 0, LEN);
	const char* prefix = "modelfiles/";
    strcat_s(filePath, LEN, prefix);

	CSingleton *instance = CSingleton::getInstance();
	strcat_s(filePath, instance->getCurHelicopterModelFileName());

	const int version = 0;

	std::ofstream ofs(filePath, std::ios::out | std::ios::trunc);
	ofs<<version<<" ";
	ofs.write((char *)pHM, sizeof(HelicopterModel));
	ofs.close();	
}

void CFileHandler::addModelIndexFile(LPCTSTR filePath)
{
	const int LEN = 100;
	std::ofstream ofs("flyconfig/model_index", std::ios::out | std::ios::app | std::ios::binary);
	ofs.write(filePath + 11, LEN);
	ofs.close();

	//CSingleton *instance = CSingleton::getInstance();
	//instance->setCurFileName(filePath + 11);
}

BOOL CFileHandler::openControlParaFile(LPCTSTR fileName, std::vector<ControlPara> *pVCP)
{
	const int LEN = 256;
	char filePath[LEN];
	memset(filePath, 0, LEN);

	const char *prefix = "controlparafiles/";
	strcat_s(filePath, LEN, prefix);
	strcat_s(filePath, LEN, fileName);

	std::ifstream ifs(filePath, std::ios::in | std::ios::binary);
	if (ifs.fail()) {
		return FALSE;
	}

	int fileVersion;
	ifs>>fileVersion;

	ifs.seekg(1, std::ios::cur);
	ControlPara cp;
	while (true) {
		ifs.read((char *)&cp, sizeof(ControlPara));
		if (ifs.gcount() != sizeof(ControlPara))
			break;
		pVCP->push_back(cp);
	}

	ifs.close();

	CSingleton *instance = CSingleton::getInstance();
	instance->setCurControlParameterFileName(fileName);
	return TRUE;

}

void CFileHandler::updateControlParaFile(std::vector<ControlPara> *PCPV)
{
	const int LEN = 256;
	char filePath[LEN];
	memset(filePath, 0, LEN);
	const char* prefix = "controlparafiles/";
    strcat_s(filePath, LEN, prefix);

	CSingleton *instance = CSingleton::getInstance();
	strcat_s(filePath, instance->getCurControlParameterFileName());

	const int version = 0;

	std::ofstream ofs(filePath, std::ios::out | std::ios::trunc);
	ofs<<version<<" ";
	std::vector<ControlPara>::iterator iter;
	for (iter = PCPV->begin(); iter != PCPV->end(); iter++) {
		ofs.write((char *)&(*iter), sizeof(ControlPara));
	}
	ofs.close();	
}

int CFileHandler::getModelSerialNumber(LPCTSTR modelName)
{
	const int LEN = 101;
	char modelStr[LEN];
	char cmodelStr[LEN];

	memset(modelStr, 0, LEN);
	memset(cmodelStr, 0, LEN);

	CTime t = CTime::GetCurrentTime();  
	CString timeString = t.Format("_%Y-%m-%d_");

	int serial = 1;
	CString serialStr;
	std::ifstream ifs("flyconfig/model_index", std::ios::in | std::ios::binary);
	while (true) {
		ifs.read(modelStr, LEN - 1);
		if (ifs.gcount() != (LEN - 1))
			break;

		memset(cmodelStr, 0, LEN);
		strcat_s(cmodelStr, LEN, modelName);
		strcat_s(cmodelStr, LEN, timeString);
		serialStr.Empty();
		serialStr.Format("%d", serial);
		strcat_s(cmodelStr, LEN, serialStr);
		if (!strcmp(modelStr, cmodelStr)) {
			++serial;
		}
	}
	ifs.close();
	return serial;

}


bool CFileHandler::checkModel(LPCTSTR fileName) 
{
	std::ifstream ifs("flyconfig/experimentconfig_index", std::ios::in);
	ConfigStruct cs;
	bool isConfig = false;
	while (true) {
		ifs.read((char *)&cs, sizeof(ConfigStruct));
		if (ifs.gcount() != sizeof(ConfigStruct)) 
			break;
		if (!strcmp(fileName, cs.helicopterModelFileName)) {
			isConfig = true;
			break;
		}
	}
	return isConfig;
}

bool CFileHandler::checkControlParameter(LPCTSTR fileName) 
{
	std::ifstream ifs("flyconfig/experimentconfig_index", std::ios::in);
	ConfigStruct cs;
	bool isConfig = false;
	while (true) {
		ifs.read((char *)&cs, sizeof(ConfigStruct));
		if (ifs.gcount() != sizeof(ConfigStruct)) 
			break;
		if (!strcmp(fileName, cs.controlParameterFileName)) {
			isConfig = true;
			break;
		}
	}
	return isConfig;
}

bool CFileHandler::checkPath(LPCTSTR fileName) 
{
	std::ifstream ifs("flyconfig/experimentconfig_index", std::ios::in);
	ConfigStruct cs;
	bool isConfig = false;
	while (true) {
		ifs.read((char *)&cs, sizeof(ConfigStruct));
		if (ifs.gcount() != sizeof(ConfigStruct)) 
			break;
		if (!strcmp(fileName, cs.flightPathFileName)) {
			isConfig = true;
			break;
		}
	}
	return isConfig;
}

void CFileHandler::saveControlParaFile(LPCTSTR baseName, std::vector<ControlPara> *PCPV)
{
	const int LEN = 256;
	char fileName[LEN];
	memset(fileName, 0, LEN);

	const char *prefix = "controlparafiles/";
	strcat_s(fileName, LEN, prefix);
	strcat_s(fileName, LEN, baseName);

	CTime t = CTime::GetCurrentTime();  
	CString timeString = t.Format("_%Y-%m-%d_");

	strcat_s(fileName, timeString);

	int serial = getControlParaSerialNumber(baseName);

	timeString.Empty();
	timeString.Format("%d", serial);
	strcat_s(fileName, LEN, timeString);

	std::ofstream ofs(fileName, std::ios::out | std::ios::binary);
	int version = 0;
	ofs<<version<<" ";
	std::vector<ControlPara>::iterator iter;
	for (iter = PCPV->begin(); iter != PCPV->end(); iter++) {
		ofs.write((char *) &(*iter), sizeof(ControlPara));
	}
	ofs.close();	

	addControlParaIndexFile(fileName);

	CSingleton *instance = CSingleton::getInstance();
	instance->setCurControlParameterFileName(fileName + 17);
}

int CFileHandler::getControlParaSerialNumber(LPCTSTR baseName)
{
	const int LEN = 101;
	char ctrStr[LEN];
	char cctrStr[LEN];

	memset(ctrStr, 0, LEN);
	memset(cctrStr, 0, LEN);

	CTime t = CTime::GetCurrentTime();  
	CString timeString = t.Format("_%Y-%m-%d_");

	int serial = 1;
	CString serialStr;
	std::ifstream ifs("flyconfig/controlpara_index", std::ios::in | std::ios::binary);

	while (true) {
		ifs.read(ctrStr, LEN - 1);
		if (ifs.gcount() != (LEN - 1))
			break;

		memset(cctrStr, 0, LEN);
		strcat_s(cctrStr, LEN, baseName);
		strcat_s(cctrStr, LEN, timeString);
		serialStr.Empty();
		serialStr.Format("%d", serial);
		strcat_s(cctrStr, LEN, serialStr);

		if (!strcmp(cctrStr, ctrStr)) {
			++serial;
		}

	}
	ifs.close();
	return serial;
}

void CFileHandler::addControlParaIndexFile(LPCTSTR fileName)
{
	const int LEN = 100;
	std::ofstream ofs("flyconfig/controlpara_index", std::ios::out | std::ios::binary | std::ios::app);
	ofs.write(fileName + 17 , LEN);
	ofs.close();
}


bool CFileHandler::openPathFile(LPCTSTR fileName, std::vector<pPathPointData> *pPPD) 
{
	const int LEN = 256;
	char filePath[LEN];
	memset(filePath, 0, LEN);
	const char* prefix = "pathfiles/";
    strcat_s(filePath, LEN, prefix);
	CSingleton *instance = CSingleton::getInstance();
	strcat_s(filePath, LEN, fileName);

	std::ifstream ifs(filePath, std::ios::binary | std::ios::in);
	if (ifs.fail())
		return false;

	int fileVersion;
	ifs>>fileVersion;

	ifs.seekg(1, std::ios::cur);

	while (true) {
		pPathPointData tempP = new PathPointData();
		ifs.read((char *)tempP, sizeof(PathPointData));
		if (ifs.gcount() != sizeof(PathPointData)) {
			delete tempP;
			break;
		}

		pPPD->push_back(tempP);
	}
	ifs.close();

	instance->setCurFlightPathFileName(fileName);
	return true;
}

void CFileHandler::savePathFile(LPCTSTR baseName, std::vector<pPathPointData> *pPPD)
{
	const int LEN = 256;
	char filePath[LEN];
	memset(filePath, 0, LEN);

	const char *prefix = "pathfiles/";
	strcat_s(filePath, LEN, prefix);
	strcat_s(filePath, LEN, baseName);

	CTime t = CTime::GetCurrentTime();  
	CString timeString = t.Format("_%Y-%m-%d_");

	strcat_s(filePath, timeString);

	int serial = getPathSerialNumber(baseName);

	timeString.Empty();
	timeString.Format("%d", serial);
	strcat_s(filePath, LEN, timeString);

	std::ofstream ofs(filePath, std::ios::out | std::ios::binary);
	int version = 0;
	ofs<<version<<" ";
	std::vector<pPathPointData>::iterator iter;
	for (iter = pPPD->begin(); iter != pPPD->end(); iter++) {
		ofs.write((char *) (*iter), sizeof(PathPointData));
	}
	ofs.close();	

	addPathIndexFile(filePath);

	CSingleton *instance = CSingleton::getInstance();
	instance->setCurFlightPathFileName(filePath + 11);
}

void CFileHandler::addPathIndexFile(LPCTSTR fileName)
{
	const int LEN = 100;
	std::ofstream ofs("flyconfig/path_index", std::ios::out | std::ios::binary | std::ios::app);
	ofs.write(fileName + 10, LEN);
	ofs.close();
}

int CFileHandler::getPathSerialNumber(LPCTSTR baseName)
{
	const int LEN = 101;
	char pathStr[LEN];
	char cpathStr[LEN];

	memset(pathStr, 0, LEN);
	memset(cpathStr, 0, LEN);

	CTime t = CTime::GetCurrentTime();  
	CString timeString = t.Format("_%Y-%m-%d_");

	int serial = 1;
	CString serialStr;
	std::ifstream ifs("flyconfig/path_index", std::ios::in | std::ios::binary);

	while (true) {
		ifs.read(pathStr, LEN - 1);
		if (ifs.gcount() != (LEN - 1))
			break;

		memset(cpathStr, 0, LEN);
		strcat_s(cpathStr, LEN, baseName);
		strcat_s(cpathStr, LEN, timeString);
		serialStr.Empty();
		serialStr.Format("%d", serial);
		strcat_s(cpathStr, LEN, serialStr);

		if (!strcmp(cpathStr, pathStr)) {
			++serial;
		}

	}
	ifs.close();
	return serial;
}

void CFileHandler::saveFlyDataFile(LPCTSTR fileName, std::vector<FlyStateGroup> *pFSG)
{
	//int serial = getFlyDataSerialNumber(fileName);
	static int count = 1;
	const int LEN = 256;
	char filePath[LEN];

	memset(filePath, 0, LEN);
	const char* prefix = "flydatafiles/";
	strcat_s(filePath, LEN, prefix);
	strcat_s(filePath, LEN, fileName);

	//CString str;
	//str.Format("%d", serial);
	//strcat_s(filePath, LEN, str);

	std::ofstream ofs(filePath, std::ios::binary | std::ios::out);
	std::vector<FlyStateGroup>::iterator iter;
	for (iter = pFSG->begin(); iter != pFSG->end(); iter++) {
		ofs.write((char *) & (*iter), sizeof(FlyStateGroup));
	}
	ofs.close();
	
	if (count == 1) {
		addFlyDataIndexFile(filePath);
		++count;
	}

}

void CFileHandler::appendFlyDataFile(LPCTSTR fileName, std::vector<FlyStateGroup> *pFSG)
{
	int serial = getFlyDataSerialNumber(fileName);

	const int LEN = 256;
	char filePath[LEN];

	memset(filePath, 0, LEN);
	const char* prefix = "flydatafiles/";
	strcat_s(filePath, LEN, prefix);
	strcat_s(filePath, LEN, fileName);

	CString str;
	str.Format("%d", serial);
	strcat_s(filePath, LEN, str);

	std::ofstream ofs(filePath, std::ios::binary | std::ios::out);
	std::vector<FlyStateGroup>::iterator iter;
	for (iter = pFSG->begin(); iter != pFSG->end(); iter++) {
		ofs.write((char *) & (*iter), sizeof(FlyStateGroup));
	}
	ofs.close();
	
	addFlyDataIndexFile(filePath);

}

void CFileHandler::addFlyDataFileHeader(LPCTSTR fileName, PExperimentData pED)
{
	const int LEN = 256;
	char filePath[LEN];

	memset(filePath, 0, LEN);
	const char* prefix = "flydatafiles/";
	strcat_s(filePath, LEN, prefix);
	strcat_s(filePath, LEN, fileName);

	std::ofstream ofs(filePath, std::ios::binary | std::ios::out);
	ofs.seekp(0, std::ios::beg);
	int fileVersion = 0;
	ofs<<fileVersion;

	
	CSingleton *instance = CSingleton::getInstance();
	int size = 0;
	size = sizeof(HelicopterModel);
	ofs<<size;
	ofs.write((char *)instance->getCurPHM(), size);

	std::vector<ControlPara> *pCPV = instance->getCPV();
	size = pCPV->size() * sizeof(ControlPara);

	ofs<<size;
	std::vector<ControlPara>::iterator iter1;
	for (iter1 = pCPV->begin(); iter1 != pCPV->end(); iter1++) {
		ofs.write((char *)&(*iter1), sizeof(ControlPara));
	}

	std::vector<pPathPointData> *pPath = instance->getPath();
	size = pPath->size() * sizeof(PathPointData);
	ofs<<size;
	std::vector<pPathPointData>::iterator iter2;
	for (iter2 = pPath->begin(); iter2 != pPath->end(); iter2++) {
		ofs.write((char *)*iter2, sizeof(PathPointData));
	}

	ofs.write((char *)pED, sizeof(ExperimentData));
	ofs.close();

}

int CFileHandler::getFlyDataSerialNumber(LPCTSTR baseName)
{
	const int LEN = 101;
	char flyDataStr[LEN];
	char cflyDataStr[LEN];

	memset(flyDataStr, 0, LEN);
	memset(cflyDataStr, 0, LEN);

	int serial = 0;
	CString serialStr;
	std::ifstream ifs("flyconfig/flydata_index", std::ios::in | std::ios::binary);

	while (true) {
		ifs.read(flyDataStr, LEN - 1);
		if (ifs.gcount() != (LEN - 1))
			break;

		memset(cflyDataStr, 0, LEN);
		strcat_s(cflyDataStr, LEN, baseName);
		serialStr.Empty();
		serialStr.Format("%d", serial);
		if (serial == 0) {
			serialStr.Empty();
		}
		strcat_s(cflyDataStr, LEN, serialStr);

		if (!strcmp(cflyDataStr, flyDataStr)) {
			++serial;
		}

	}
	ifs.close();
	return serial;
}

void CFileHandler::addFlyDataIndexFile(LPCTSTR fileName)
{
	const int LEN = 100;
	std::ofstream ofs("flyconfig/flydata_index", std::ios::out | std::ios::binary);
	ofs.write(fileName + 13, LEN);
	ofs.close();
}

void CFileHandler::saveExperimentConfiguration(void)
{
	CSingleton *instance = CSingleton::getInstance();
	PConfigStruct curCS = instance->getCS();
	std::ofstream ofs("flyconfig/experimentconfig_index", std::ios::binary | std::ios::app);
	ofs.write((char *)curCS, sizeof(ConfigStruct));
	ofs.close();
}

void CFileHandler::saveExperimentConfiguration(LPCTSTR filePath)
{
	CSingleton *instance = CSingleton::getInstance();
	PConfigStruct curCS = instance->getCS();
	std::ofstream ofs(filePath, std::ios::binary | std::ios::app);
	ofs.write((char *)curCS, sizeof(ConfigStruct));
	ofs.close();
}

void CFileHandler::updatePathFile(std::vector<pPathPointData> *pPPD)
{
	const int LEN = 256;
	char filePath[LEN];
	memset(filePath, 0, LEN);
	const char* prefix = "pathfiles/";
    strcat_s(filePath, LEN, prefix);

	CSingleton *instance = CSingleton::getInstance();
	strcat_s(filePath, instance->getCurFlightPathFileName());

	const int version = 0;

	std::ofstream ofs(filePath, std::ios::binary | std::ios::trunc);
	ofs<<version<<" ";
	std::vector<pPathPointData>::iterator iter;
	for (iter = pPPD->begin(); iter != pPPD->end(); iter++) {
		ofs.write((char *)*iter, sizeof(PathPointData));
	}
	ofs.close();	
}