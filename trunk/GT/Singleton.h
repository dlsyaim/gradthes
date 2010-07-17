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

	//inline void setRecentFPName(CString recentFPName) {this->recentFPName = recentFPName;}
	//inline CString getRecnetFPName(void) {return recentFPName;}

	//inline void setRecentCPName(CString recentCPName) {this->recentCPName = recentCPName;}
	//inline CString getRecnetCPName(void) {return recentCPName;}

	//inline void setCurFileName(CString curFileName) {this->curFileName = curFileName;}
	//inline CString getCurFileName(void) {return curFileName;}
	inline LPCTSTR getCurHelicopterModelFileName(void) {return tempCS.helicopterModelFileName;}
	void setCurHelicopterModelFileName(LPCTSTR fileName);
	void setCurControlParameterFileName(LPCTSTR fileName);
	void setCurFlightPathFileName(LPCTSTR fileName);
	void setCurFlyDataFileName(LPCTSTR fileName);

	void updateCurConfiguration(void);

	inline void setIsControlParameterSet(BOOL isControlParameterSet) {this->isControlParameterSet = isControlParameterSet;}
	inline BOOL getIsControlParameterSet(void) {return isControlParameterSet;}

	inline void setIsRotorDemarcated(BOOL isRotorDemarcated) {this->isRotorDemarcated = isRotorDemarcated;}
	inline BOOL getIsRotorDemarcated(void) {return isRotorDemarcated;}

	inline PHelicopterModel getCurPHM(void) {return &curHM;}
	//inline void setCurPHM(PHelicopterModel curPHM) {this->curPHM = curPHM;}

	inline std::vector<ControlPara>* getTempCPV(void) {return &tempCPV;}
	inline std::vector<ControlPara>* getCPV(void) {return &CPV;}
	
	inline PConfigStruct getCS(void) {return &cs;}

	inline std::vector<pPathPointData> * getPath(void){return &path;}
	//inline std::vector<pPathPointData> * getTempPath(void) {return &tempPath;}
	inline std::vector<pPathPointData> * getScheduledPath(void){return &scheduledPath;}

	//PHelicopterModel getTempPHM(void);
	bool getTempPHM(LPCTSTR name, PHelicopterModel tempPHM);

	void delCurPHM(void);
	void rollBackCurPHM(BOOL isNew);

	void updateCurPHM(void);
	void updateCurCP(void);
	void updateCurFP(void);

	void updateBuffer(BOOL isNew, PHelicopterModel phm);

	void updateHelicopterModelFile(void);

	BOOL isReady(void);
// Attributes
private:
	static CSingleton* instance;
	// The helicopter model used in the flight experiment
	HelicopterModel curHM;
	//// The previous helicopter model 
	//PHelicopterModel prePHM;
	// Helicopter model buffer
	//std::vector<PHelicopterModel> pHMV;
	// Flag variables 
	BOOL isCommunicationTestPass;
	BOOL isServoActorDemarcated;
	BOOL isIMUTestPass;
	BOOL isOPTTestPass;
	BOOL isPathSet;
	BOOL isControlParameterSet;
	BOOL isRotorDemarcated;
	// The name of the recent flight path file
	//CString recentFPName;
	// The name of the recent control parameter file
	//CString recentCPName;
	// Control paramters
	std::vector<ControlPara> CPV, tempCPV;
	// Path points
	std::vector<pPathPointData> path, tempPath;
	// Scheduled path points
	std::vector<pPathPointData> scheduledPath;
	// Experiment configuration
	ConfigStruct cs, tempCS;
	// Current model file name
	//CString curFileName;
// Operations
private:
	void setCurPHM(BOOL isNew, CString helicopterName);
};
