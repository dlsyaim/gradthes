#pragma once
#include "GSDefinition.h"

class CMainFrmController
{
public:
	CMainFrmController(void);
	~CMainFrmController(void);

	BOOL openModelFile(LPCTSTR fileName, PHelicopterModel pHM);

	void saveExperimentConfiguration(void);
	void saveExperimentConfiguration(LPCTSTR filePath);
};
