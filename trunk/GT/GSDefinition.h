#pragma once

#include "define\FlyStructDefine.h "


/*
 * This struct is an aggregated struct, a record type, which contains
 * (1)helicopterName,
 * (2)HelicopterPara(parameters about the helicopter itself),
 * (3)Flag variable indicates if the servo actor is demarcated or not,
 * (4)ServoActorData(demarcated servo actor data),
 * (5)Flag variable indicates if the tilt disc is demarcated or not,
 * (6)TiltDiscData(demarcated tilt disc data).
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
 * The experiment configuration
 * (1)The file name of the helicopter model
 * (2)The file name of control parameters
 * (3)The file name of the flight path
 * (4)The file name of the fly data
 */

typedef struct _ConfigStruct
{
	char helicopterModelFileName[101];
	char controlParameterFileName[101];
	char flightPathFileName[101];
	char flyDataFileName[101];
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
}ExperimentData, *PExperimentData;


/*
 * The control parameters' files:
 * version
 * ControlPara struct
 */
typedef struct _ControlParameter
{
	int version;
	ControlPara cp;
} ControlParameter, PControlParameter;