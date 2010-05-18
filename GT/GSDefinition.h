#pragma once

#include "define\FlyStructDefine.h "


/*
 * This struct is an aggregated struct, which contains
 * (1)helicopterName,
 * (2)HelicopterPara(parameters about the helicopter itself),
 * (3)ServoActorData(demarcated servo actor data).
 * (4)TiltDiscData(demarcated tilt disc data).
 * And changes as time goes by.
 */

typedef struct _HelicopterModel
{
	char helicopterName[256];
	struct HelicopterPara heliPara;
	char isDemarcated;
	struct ServoActorData sad;
	char isRotorDemarcated;
	struct TiltDiscData tdd;
}HelicopterModel, *PHelicopterModel;

/*
 * The configuration file's structure
 * (1)Version
 * (2)The file name of the flight path
 * (3)The file name of control parameter
 */

typedef struct _ConfigStruct
{
	int version;
	char isPathSet;
	char flightPathFileName[100];
	char isControlSet;
	char controlParameterFileName[100];
}ConfigStruct, *PConfigStruct;

/*
 * The experiments' data files:
 *     Start time: %Y-%m-%d %H:%M:%S)
 *     tof: time of flight  
 *     subExperimentData: store the file name of the fly state which exceeds a required size
 */

typedef struct _ExperimentData
{
	char startTime[100];
	long tof;
	char subExperimentData[100];
}ExperimentData, PExperimentData;