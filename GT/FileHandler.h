#pragma once
#include <vector>
#include <fstream>
#include "GSDefinition.h"

class CFileHandler
{
public:
	CFileHandler(void);
	~CFileHandler(void);

	static BOOL openModelFile(LPCTSTR filePath, PHelicopterModel pHM);
	static void saveModelFile(PHelicopterModel pHM);
	static void updateModelFile(PHelicopterModel pHM);

	static BOOL openControlParaFile(LPCTSTR fileName, std::vector<ControlPara>* PCPV);
	static void saveControlParaFile(LPCTSTR baseName, std::vector<ControlPara>* PCPV);
	static void updateControlParaFile(std::vector<ControlPara>* PCPV);

	static bool openPathFile(LPCTSTR filePath, std::vector<pPathPointData>* pPPD);
	static void savePathFile(LPCTSTR baseName, std::vector<pPathPointData>* pPPD);
	static void updatePathFile(std::vector<pPathPointData>* pPPD);
  
	static void saveFlyDataFile(LPCTSTR fileName, std::vector<FlyStateGroup>* pFSG);
	static void appendFlyDataFile(LPCTSTR fileName, std::vector<FlyStateGroup>* pFSG);
	static void addFlyDataFileHeader(LPCTSTR fileName, PExperimentData pED);
	
	static bool checkModel(LPCTSTR fileName);
	static bool checkControlParameter(LPCTSTR fileName);
	static bool checkPath(LPCTSTR fileName);

	static void saveExperimentConfiguration(void);
	static void saveExperimentConfiguration(LPCTSTR filePath);

private:
	static int getModelSerialNumber(LPCTSTR modelName);
	static int getControlParaSerialNumber(LPCTSTR baseName);
	static int getPathSerialNumber(LPCTSTR baseName);
	static int getFlyDataSerialNumber(LPCTSTR baseName);
	static void addModelIndexFile(LPCTSTR modelName);
	static void addControlParaIndexFile(LPCTSTR fileName);
	static void addPathIndexFile(LPCTSTR fileName);
	static void addFlyDataIndexFile(LPCTSTR fileName);
};
