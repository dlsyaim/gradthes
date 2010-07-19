#pragma once
#include <vector>
#include "GSDefinition.h"

class CFlightPathSetController
{
public:
	CFlightPathSetController(void);
	~CFlightPathSetController(void);

	void savePathFile(LPCTSTR baseName, std::vector<pPathPointData> *pPPD);
	bool openPathFile(LPCTSTR filePath, std::vector<pPathPointData> *pPPD);

	bool checkPath(LPCTSTR fileName);

	void updatePathFile(std::vector<pPathPointData> *pPPD);
};
