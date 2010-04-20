#pragma once

#include "define\FlyStructDefine.h "

/*
 * This struct is an aggregated struct, which contains
 * (1)helicopterName,
 * (2)HelicopterPara(parameters about the helicopter itself),
 * (3)ServoActorData(demarcated servo actor data).
 * And changes as time goes by.
 */

typedef struct _HelicopterModel
{
	char helicopterName[256];
	struct HelicopterPara heliPara;
	struct ServoActorData sad;
}HelicopterModel, *PHelicopterModel;

/*
 * Must consider the configuration files
 */

//typedef struct _
//{
//
//};