#ifndef _HELI_SYSDEF_H_
#define _HELI_SYSDEF_H_


/*****************************************************************************
*指令头设计
******************************************************************************/
#define INSHEAD				__int16

#define InitIns(ins)		(ins=0x0000)
#define GetFirstIns(ins)	(ins&0x000f)
#define GetSecondIns(ins)	(ins&0x00ff)
#define GetThirdIns(ins)	(ins&0x0fff)



/*****************************************************************************
*指令设计
******************************************************************************/
#define FEM_EMERGENCY						0x0000				/*应急指令								*/
#define FIE_INSPARSEERR						0x0001				/*指令解析错误指令						*/
#define FNT_NETTESTTEXT						0x0002				/*网络通信带文本测试指令				*/
#define FNT_NETTESTTEXTREPLY				0x0003				/*网络通信带文本测试回复指令			*/
#define FCT_NETCOMTEST						0x0004				/*网络通信测试指令						*/
#define FCT_NETCOMTESTREPLY					0x0005				/*网络通信测试回复指令					*/
#define FET_EQUIPMENTTEST					0x0006				/*设备测试二级子指令集					*/
#define SAT_SERVOACTOR_TST					0x0016				/*舵机测试指令							*/
#define STT_THROTTLE_TST					0x0026				/*油门测试指令							*/
#define STT_TILTDISC_TST					0x0036				/*倾斜盘测试指令						*/
#define SIT_IMU_TST							0x0046				/*IMU测试三级子指令集					*/
#define TIT_IMUTEST_START					0x0146				/*开始IMU测试指令						*/
#define TIT_IMUTEST_STOP					0x0246				/*结束IMU测试指令						*/
#define TIT_IMUTEST_DATA					0x0346				/*IMU测试数据指令						*/
#define SGT_GPS_TST							0x0056				/*GPS测试三级子指令集					*/
#define TGT_GPSTEST_START					0x0156				/*开始GPS测试指令						*/
#define TGT_GPSTEST_STOP					0x0256				/*结束GPS测试指令						*/
#define TGT_GPSTEST_DATA					0x0356				/*GPS测试数据指令						*/
#define SOT_OPTTRACE_TST					0x0066				/*光学追踪系统测试三级子指令集			*/
#define TOT_OPTTRACETEST_START				0x0166				/*开始光学追踪系统测试指令				*/
#define TOT_OPTTRACETEST_STOP				0x0266				/*结束光学追踪系统测试指令				*/
#define TOT_OPTTRACETEST_DATA				0x0366				/*光学追踪系统测试数据指令				*/
#define SAT_ALTIMETER_TST					0x0076				/*高度计测试三级子指令集				*/
#define TAT_ALTIMETERTEST_START				0x0176				/*开始高度计测试指令					*/
#define TAT_ALTIMETERTEST_STOP				0x0276				/*结束高度计测试指令					*/
#define TAT_ALTIMETERTEST_DATA				0x0376				/*高度计测试数据指令					*/
#define FOC_OPERATIONCOMMAND				0x0007				/*操作控制二级子指令集					*/
#define SFT_FLYING_TASK						0x0017				/*飞行任务三级子指令集					*/
#define TFT_STARTTASK						0x0117				/*开始飞行任务指令						*/
#define TFT_STARTTASKREPLY					0x0217				/*开始飞行任务返回指令					*/
#define TFT_STARTSTOP						0x0317				/*结束飞行任务指令						*/
#define TFT_STARTSTOPREPLY					0x0417				/*结束飞行任务返回指令					*/
#define SAS_ACTORSET_TASK					0x0027				/*舵机设置三级子指令集					*/
#define TAS_ACTORSET						0x0127				/*舵机设置指令							*/
#define STS_TILTDISCSET_TASK				0x0037				/*倾斜盘设置三级子指令集				*/
#define TTS_TILTDISCSET						0x0137				/*倾斜盘设置指令						*/
#define SPT_PATH_TASK						0x0047				/*路径任务三级子指令集					*/
#define TPT_LOADPATHPOINT_START				0x0147				/*开始路径加载指令						*/
#define TPT_LOADPATHPOINT_STOP				0x0247				/*结束路径加载指令						*/
#define TPT_LOADPATHPOINTS					0x0347				/*加载路径点指令						*/
#define TPT_LOADPATHPOINTS_REPLY			0x0447				/*加载路径点回复指令					*/
#define TPT_LOADPATHPOINTS_CHECK			0x0547				/*路径点检查返回指令					*/
#define FIT_FLYINGSTATEDATA					0x0008				/*飞行数据返回指令						*/

/*****************************************************************************
*指令数据设计
******************************************************************************/


typedef struct ServoActorTstInsData
{
	__int8	ActorSerial;
	float	SetPWM;
};


typedef struct ThrottleTstInsData
{
	float	SetPWM;
};


typedef struct TiltDiscTstInsData
{
	float	CollectSetAngle;
	float	RollSetAngle;
	float	PitchetAngle;
};


typedef struct IMUTestData
{
	__int8	IMUState;					 
	float	N_Speed;				 
	float	E_Speed;				 
	float	D_Speed;				 
	float	N_Acc;					 
	float	E_Acc;					 
	float	D_Acc;					 
	float	phi;					 
	float	theta;					 
	float	psi;						 
	float	phi_Acc;				 
	float	theta_Acc;				 
	float	psi_Acc;				 
};


typedef struct IGPSestData
{
	__int8	GPSState;					 
	float	N_Pos;				 
	float	E_Pos;				 
	float	D_Pos;
};


typedef struct OPTTRACETestData
{
	__int8	OPTState;					 
	float	N_Pos;				 
	float	E_Pos;				 
	float	D_Pos;					 
	float	N_Speed;				 
	float	E_Speed;				 
	float	D_Speed;				 
	float	N_Acc;					 
	float	E_Acc;					 
	float	D_Acc;					 
	float	phi;					 
	float	theta;					 
	float	psi;						 
	float	phi_Acc;				 
	float	theta_Acc;				 
	float	psi_Acc;				 
};


typedef struct  ServoActorData
{
	float	a1MeansureAng[5];		
	float	a1PWMValue[5];
	float	a2MeansureAng[5];		
	float	a2PWMValue[5];
	float	a3MeansureAng[5];		
	float	a3PWMValue[5];
	float	a4MeansureAng[5];	
	float	a4PWMValue[5];
};


typedef struct TiltDiscData
{
	float	CommandAngs[10][3];
	float   MeansureAngs[10][3];
};


typedef struct  PathPointData
{
	int		serial;							 
	float	Coordinate_X;
	float	Coordinate_Y;
	float	Coordinate_Z;
	float	StayTime;
	float	reserve1;
	float	reserve2;
	float	reserve3;
};


#endif
