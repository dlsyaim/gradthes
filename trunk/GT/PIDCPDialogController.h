#pragma once
#include <vector>
#include "GSDefinition.h"

class CPIDCPDialogController
{
public:
	CPIDCPDialogController(void);
	~CPIDCPDialogController(void);

	void saveControlParaFile(LPCTSTR baseName, std::vector<ControlPara>*PCPV);

	BOOL openControlParaFile(LPCTSTR fileName, std::vector<ControlPara> *PCPV);

	void updateControlParaFile(std::vector<ControlPara> *PCPV);

	bool checkControlParameter(LPCTSTR fileName);
};
