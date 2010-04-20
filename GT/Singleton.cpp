#include "StdAfx.h"
#include "Singleton.h"

CSingleton::CSingleton(void)
{
	isCommunicationTestPass = FALSE;
	isServoActorDemarcated = FALSE;
	isIMUTestPass = FALSE;
	isOPTTestPass = FALSE;
	isPathSet = FALSE;
	isControlParameterSet = FALSE;
	curPHM = prePHM = NULL;
}

CSingleton::~CSingleton(void)
{
	std::vector<PHelicopterModel>::iterator iter;
	for (iter = pHMV.begin(); iter != pHMV.end(); iter++)
		delete *iter;
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

	return curPHM;
}

void CSingleton::setCurPHM(BOOL isNew, CString helicopterName)
{
	CString tName;
	int countRead;
	if (isNew) {
		// New a helicopter model
		curPHM =  new HelicopterModel;
		// Initialize 
		memset(curPHM->helicopterName, 0, sizeof(curPHM->helicopterName));
	} else if(helicopterName != "") {
	    // Should check the helicopter model buffer first
		std::vector<PHelicopterModel>::iterator iter;		
		for (iter = pHMV.begin(); iter != pHMV.end(); iter++) {
			tName = (*iter)->helicopterName;
			if (tName == helicopterName) {
				// Means in the buffer, and first store the current helicopter model in the prePHM
				prePHM = curPHM;
				curPHM = *iter;
				return;
			} 
		}
		// Means not in the buffer, then should read the file
		std::ifstream ifs("uh.hm", std::ios::binary);
		prePHM = curPHM;
		curPHM = new HelicopterModel;
		// Initialize 
		memset(curPHM->helicopterName, 0, sizeof(curPHM->helicopterName));
		while (TRUE) {			
			ifs.read((char*) curPHM, sizeof(*curPHM));
			countRead = ifs.gcount();
			if (countRead != sizeof(*curPHM))
				break;
			tName = curPHM->helicopterName;
			if (tName == helicopterName) {
				// Means found in the file
				pHMV.push_back(curPHM);
				ifs.close();
				return;
			}
		}
		ifs.close();
		// Means not found in the file and not found in the buffer
		delete curPHM;
		curPHM = prePHM;
	} else {
		curPHM = NULL;
	}
}


void CSingleton::updateBuffer(BOOL isNew, PHelicopterModel phm)
{
	if (isNew) {
		pHMV.push_back(phm);
	}
}

void CSingleton::delCurPHM(void)
{
	if (curPHM) {
		delete curPHM;
		curPHM = NULL;
	}
}

void CSingleton::rollBackCurPHM(BOOL isNew)
{
	if (isNew) {
		delete curPHM;
		curPHM = prePHM;
	} else {
		curPHM = prePHM;
	}

	if (curPHM)
		TRACE(curPHM->helicopterName);
}

void CSingleton::updatePrePHM(void)
{
	prePHM = curPHM;
}


BOOL CSingleton::isReady(void)
{
		return isCommunicationTestPass && 
			isServoActorDemarcated && 
			isIMUTestPass && 
			isOPTTestPass && 
			isPathSet && 
			isControlParameterSet &&
			curPHM != NULL;
}