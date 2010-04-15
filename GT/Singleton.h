#pragma once
#include "GSDefinition.h"

class CSingleton
{
private:
	CSingleton(void);
public:
	static CSingleton* getInstance();
	~CSingleton(void);
	PHelicopterModel getHelicopterModel(BOOL isNew = TRUE, CString helicopterName = "");
private:
	static CSingleton* instance;
	HelicopterModel hm;

	/// Helicopter model buffer
	std::vector<PHelicopterModel> pHMV;
};
