#pragma once
#include <fstream>
#include "GSDefinition.h"

class CHelicopterChoosingController
{
public:
	CHelicopterChoosingController(void);
	~CHelicopterChoosingController(void);

	void saveModelFile(PHelicopterModel pHM);
	void updateModelFile(PHelicopterModel pHM);

	bool checkModel(LPCTSTR fileName);
};
