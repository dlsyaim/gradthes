#pragma once

#include <vector>
#include <fstream>
#include "GSDefinition.h"

class CSingleton
{
// Operations
private:
	CSingleton(void);
public:
	static CSingleton* getInstance();
	~CSingleton(void);
	PHelicopterModel getHelicopterModel(BOOL isNew = TRUE, CString helicopterName = "");
	
	inline void setIsCommunicationTestPass(BOOL isCommunicationTestPass){this->isCommunicationTestPass = isCommunicationTestPass;}
	inline BOOL getIsCommunicationTestPass(void) {return this->isCommunicationTestPass;}

	inline void setIsServoActorDemarcated(BOOL isServoActorDemarcated){this->isServoActorDemarcated = isServoActorDemarcated;}
	inline BOOL getIsServoActorDemarcated(void) {return this->isServoActorDemarcated;}
	
	inline void setIsIMUTestPass(BOOL isIMUTestPass){this->isIMUTestPass = isIMUTestPass;}
	inline BOOL getIsIMUTestPass(void) {return this->isIMUTestPass;}

	inline void setIsOPTTestPass(BOOL isOPTTestPass){this->isOPTTestPass = isOPTTestPass;}
	inline BOOL getIsOPTTestPass(void) {return this->isOPTTestPass;}

	inline void setIsPathSet(BOOL isPathSet){this->isPathSet = isPathSet;}
	inline BOOL getIsPathSet(void) {return this->isPathSet;}

	inline void setRecentFPName(CString recentFPName) {this->recentFPName = recentFPName;}
	inline CString getRecnetFPName(void) {return recentFPName;}

	inline void setRecentCPName(CString recentCPName) {this->recentCPName = recentCPName;}
	inline CString getRecnetCPName(void) {return recentCPName;}

	inline void setIsControlParameterSet(BOOL isControlParameterSet) {this->isControlParameterSet = isControlParameterSet;}
	inline BOOL getIsControlParameterSet(void) {return isControlParameterSet;}

	inline PHelicopterModel getCurPHM(void) {return curPHM;}
	inline void setCurPHM(PHelicopterModel curPHM) {this->curPHM = curPHM;}
	void delCurPHM(void);
	void rollBackCurPHM(BOOL isNew);

	void updatePrePHM(void);

	void updateBuffer(BOOL isNew, PHelicopterModel phm);

	BOOL isReady(void);
// Attributes
private:
	static CSingleton* instance;
	// The helicopter model used in this experiment
	PHelicopterModel curPHM;
	// The previous helicopter model 
	PHelicopterModel prePHM;

	// Helicopter model buffer
	std::vector<PHelicopterModel> pHMV;
	// Flag variables 
	BOOL isCommunicationTestPass;
	BOOL isServoActorDemarcated;
	BOOL isIMUTestPass;
	BOOL isOPTTestPass;
	BOOL isPathSet;
	BOOL isControlParameterSet;
	// The name of the recent flight path file
	CString recentFPName;
	// The name of the recent control parameter file
	CString recentCPName;
// Operations
private:
	void setCurPHM(BOOL isNew, CString helicopterName);
};
