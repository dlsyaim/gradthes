#include "StdAfx.h"
#include "Singleton.h"
#include "FileHandler.h"

CSingleton::CSingleton(void)
{
	isCommunicationTestPass = FALSE;
	isServoActorDemarcated = FALSE;
	isIMUTestPass = FALSE;
	isOPTTestPass = FALSE;
	isPathSet = FALSE;
	isControlParameterSet = FALSE;
	isRotorDemarcated = FALSE;
	
	memset(&cs, 0, sizeof(ConfigStruct));
	memset(&tempCS, 0, sizeof(ConfigStruct));

	memset(&curHM, 0, sizeof(HelicopterModel));
}

CSingleton::~CSingleton(void)
{
	/*std::vector<PHelicopterModel>::iterator iter;
	for (iter = pHMV.begin(); iter != pHMV.end(); iter++)
		delete *iter;*/

	std::vector<PathPointData*>::iterator pathIter;
	for (pathIter = path.begin(); pathIter != path.end(); pathIter++) {
		delete *pathIter;
	}

	for (pathIter = scheduledPath.begin(); pathIter != scheduledPath.end(); pathIter++) {
		delete *pathIter;
	}
}

CSingleton* CSingleton::instance = 0;

CSingleton* CSingleton::getInstance(void)
{
	if (instance == 0) {
		instance = new CSingleton();
	}

	return instance;
}

PHelicopterModel CSingleton::getHelicopterModel(BOOL isNew/* = 1*/, CString helicopterName/* = ""*/)
{
	setCurPHM(isNew, helicopterName);

	return &curHM;
}

void CSingleton::setCurPHM(BOOL isNew, CString helicopterName)
{
	//CString tName;
	//if (isNew) {
	//	// New a helicopter model
	//	curPHM =  new HelicopterModel;
	//	// Initialize the helicopter name
	//	memset(curPHM->helicopterName, 0, sizeof(curPHM->helicopterName));
	//	// Initialize the state of demarcated:0 indicates no demarcated 1 indicates demarcated
	//	curPHM->isDemarcated = 0;
	//	// Initialize the state of rotor demarcated: 0 indicates no demarcated and 1 indicates demarcated
	//	curPHM->isRotorDemarcated = 0;
	//} else if(helicopterName != "") {
	//    //// Should check the helicopter model buffer first
	//	//std::vector<PHelicopterModel>::iterator iter;		
	//	//for (iter = pHMV.begin(); iter != pHMV.end(); iter++) {
	//	//	tName = (*iter)->helicopterName;
	//	//	if (tName == helicopterName) {
	//	//		// Means in the buffer, and first store the current helicopter model in the prePHM
	//	//		prePHM = curPHM;
	//	//		curPHM = *iter;
	//	//		return;
	//	//	} 
	//	//}
	//	//// Means not in the buffer, then should read the file
	//	//std::ifstream ifs("uh.hm", std::ios::binary);
	//	//prePHM = curPHM;
	//	//curPHM = new HelicopterModel;
	//	//// Initialize the helicopter name
	//	//memset(curPHM->helicopterName, 0, sizeof(curPHM->helicopterName));
	//	//// Initialize the state variable
	//	//curPHM->isDemarcated = 0;
	//	//curPHM->isRotorDemarcated = 0;
	//	//while (TRUE) {			
	//	//	ifs.read((char*) curPHM, sizeof(*curPHM));
	//	//	countRead = ifs.gcount();
	//	//	if (countRead != sizeof(*curPHM))
	//	//		break;
	//	//	tName = curPHM->helicopterName;
	//	//	if (tName == helicopterName) {
	//	//		// Found in the file
	//	//		pHMV.push_back(curPHM);
	//	//		ifs.close();
	//	//		return;
	//	//	}
	//	//}
	//	//ifs.close();
	//	curPHM = new HelicopterModel();
	//	// Initialize the helicopter name
	//	memset(curPHM->helicopterName, 0, sizeof(curPHM->helicopterName));
	//	// Initialize the state variable
	//	curPHM->isDemarcated = 0;
	//	curPHM->isRotorDemarcated = 0;
	//	if (!CFileHandler::openModelFile(helicopterName, curPHM)) {
	//		// Not found in the file and not found in the buffer
	//		delete curPHM;
	//		//curPHM = prePHM;
	//	}		
	//} else {
	//	// Should not run to here
	//	curPHM = NULL;
	//}
}


void CSingleton::updateBuffer(BOOL isNew, PHelicopterModel phm)
{
	if (isNew) {
		//pHMV.push_back(phm);
	}
}

void CSingleton::delCurPHM(void)
{
	/*if (curPHM) {
		delete curPHM;
		curPHM = NULL;
	}*/
}

void CSingleton::rollBackCurPHM(BOOL isNew)
{
	/*if (isNew) {
		delete curPHM;
		curPHM = prePHM;
	} else {
		curPHM = prePHM;
	}*/
	//delete curPHM;
	//curPHM = prePHM;
	//if (curPHM)
	//	TRACE(curPHM->helicopterName);
}

void CSingleton::updateCurPHM(void)
{
	//if (curPHM) {
	//	delete curPHM;
	//}
	//curPHM = tempPHM;
	//tempPHM = NULL;
	//memcpy(&curHM, &tempHM, sizeof(HelicopterModel));
	//memset(&tempHM, 0, sizeof(HelicopterModel));
}

void CSingleton::updateCurCP(void)
{
	CPV.clear();
	std::vector<ControlPara>::iterator iter;
	for (iter = tempCPV.begin(); iter != tempCPV.end(); iter++) {
		CPV.push_back(*iter);
	}
	tempCPV.clear();
}

void CSingleton::updateCurFP(void)
{
	path.clear();
	std::vector<pPathPointData>::iterator iter;
	for (iter = tempPath.begin(); iter != tempPath.end(); iter++) {
		path.push_back(*iter);
	}
	tempPath.clear();
}


BOOL CSingleton::isReady(void)
{
	//if (curPHM == NULL)
	//	return FALSE;
	if (curHM.isDemarcated == 1)
		isServoActorDemarcated = TRUE;
	else
		isServoActorDemarcated = FALSE;

	if (curHM.isRotorDemarcated == 1)
		isRotorDemarcated = TRUE;
	else
		isRotorDemarcated = FALSE;
	
	//if (cs.isControlSet == 1)
	//	isControlParameterSet = TRUE;
	//else
	//	isControlParameterSet = FALSE;

	//if (cs.isPathSet == 1)
	//	isPathSet = TRUE;
	//else
	//	isPathSet = FALSE;
	
	return	isCommunicationTestPass && 
			isIMUTestPass && 
			isOPTTestPass && 
			isServoActorDemarcated &&
			isRotorDemarcated &&
			isControlParameterSet &&
			isPathSet;
}

void CSingleton::updateHelicopterModelFile(void)
{
	// Open the uh.hm file and update it	
	//std::ifstream ifs("uh.hm", std::ios::binary | std::ios::in | std::ios::out);
	//if (ifs.fail()) {
	//	AfxMessageBox(_T("Can't find file uh.hm"), MB_OK | MB_ICONSTOP);
	//	return;
	//}
	//int numberOfHM;
	//ifs.seekg(0, std::ios::end);
	//numberOfHM = ifs.tellg() / sizeof(HelicopterModel);
	//ifs.seekg(0, std::ios::beg);
	//// New a temporary helicopter model array
	//PHelicopterModel tmpArray = new HelicopterModel[numberOfHM + 1];
	//// The index of the above array
	//int bytesRead, idx = 0;
	//BOOL isFound = FALSE;
	//// Start to read the file
	//while (TRUE) {
	//	ifs.read((char *)(tmpArray + idx), sizeof(tmpArray[idx]));
	//	bytesRead = ifs.gcount();
	//	if (bytesRead != sizeof(tmpArray[idx])) { 
	//		break;
	//	}
	//	if (!strcmp(tmpArray[idx].helicopterName, curHM.helicopterName)) {
	//		// The current helicopter model is found in the file
	//		isFound = TRUE;		
	//		tmpArray[idx] = *curPHM;
	//	}
	//	idx ++;
	//}
	//ifs.close();
	//if (!isFound) {
	//	TRACE(_T("Theoretically this line of code couldn't be reached\n"));
	//	tmpArray[idx++] = *curPHM;
	//}

	//// Start to update to the file
	//std::ofstream ofs("uh.hm", std::ios::binary | std::ios::trunc);
	//for (int i = 0; i < idx; i++) {
	//	ofs.write((char *)(tmpArray + i), sizeof(tmpArray[i]));
	//}
	//ofs.close();

	//delete[] tmpArray;
}

bool CSingleton::getTempPHM(LPCTSTR fileName, PHelicopterModel tempPHM)
{
	const int LEN = 256;
	char filePath[LEN];
	memset(filePath, 0, LEN);

	const char* prefix = "modelfiles/";
	strcat_s(filePath, LEN, prefix);
	strcat_s(filePath, LEN, fileName);

	int fileVersion;
	std::ifstream ifs(filePath, std::ios::binary);
	if (ifs.fail()) {
		return false;
	}
	ifs>>fileVersion;
	ifs.seekg(1, std::ios::cur);
	ifs.read((char *)tempPHM, sizeof(HelicopterModel));
	ifs.close();

	setCurHelicopterModelFileName(fileName);
	return true;
}

//PHelicopterModel CSingleton::getTempPHM(void)
//{
//	memset(tempHM.helicopterName, 0, sizeof(tempHM.helicopterName));
//	// Initialize the state of demarcated:0 indicates no demarcated 1 indicates demarcated
//	tempHM.isDemarcated = 0;
//	// Initialize the state of rotor demarcated: 0 indicates no demarcated and 1 indicates demarcated
//	tempHM.isRotorDemarcated = 0;
//
//	return &tempHM;
//}

void CSingleton::setCurHelicopterModelFileName(LPCTSTR fileName)
{
	strcpy_s(tempCS.helicopterModelFileName, 100, fileName);
}

void CSingleton::setCurControlParameterFileName(LPCTSTR fileName)
{
	strcpy_s(tempCS.controlParameterFileName, 100, fileName);
}

void CSingleton::setCurFlightPathFileName(LPCTSTR fileName)
{
	strcpy_s(tempCS.flightPathFileName, 100, fileName);
}

void CSingleton::setCurFlyDataFileName(LPCTSTR fileName)
{
	strcpy_s(tempCS.flyDataFileName, 100, fileName);
}

void CSingleton::updateCurConfiguration(void)
{
	memcpy(&cs, &tempCS, sizeof(ConfigStruct));
}
