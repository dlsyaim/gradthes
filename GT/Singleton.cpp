#include "StdAfx.h"
#include <vector>
#include <fstream>
#include "Singleton.h"

CSingleton::CSingleton(void)
{
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
	PHelicopterModel tpHM;
	CString tName;
	int countRead;
	if (isNew) {
		// New a helicopter model
		tpHM =  new HelicopterModel;
		// Initialize 
		memset(tpHM->helicopterName, 0, sizeof(tpHM->helicopterName));
		pHMV.push_back(tpHM);
		return tpHM;
	} else if(helicopterName != "") {
	    // Should check the helicopter model buffer first
		std::vector<PHelicopterModel>::iterator iter;		
		for (iter = pHMV.begin(); iter != pHMV.end(); iter++) {
			tName = (*iter)->helicopterName;
			if (tName == helicopterName) {
				// Means in the buffer
				return *iter;
			} 
		}
		// Means not in the buffer, then should read the file
		std::ifstream ifs("uh.hm", std::ios::binary);
		tpHM = new HelicopterModel;
		// Initialize 
		memset(tpHM->helicopterName, 0, sizeof(tpHM->helicopterName));
		while (TRUE) {			
			ifs.read((char*) tpHM, sizeof(*tpHM));
			countRead = ifs.gcount();
			if (countRead != sizeof(*tpHM))
				break;
			tName = tpHM->helicopterName;
			if (tName == helicopterName) {
				// Means found in the file
				pHMV.push_back(tpHM);
				ifs.close();
				return tpHM;
			}
		}
		ifs.close();
		// Means not found in the file
		delete tpHM;
		return NULL;					
	} else 
		return NULL;
}
