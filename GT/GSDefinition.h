#ifndef _GSDEFINITION_H_
#define _GSDEFINITION_H_
#include "define\FlyStructDefine.h "
typedef struct _HelicopterModel
{
	struct HelicopterPara heliPara;
	char helicopterName[256];
}HelicopterModel, *PHelicopterModel;

#endif