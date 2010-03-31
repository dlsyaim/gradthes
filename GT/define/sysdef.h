#ifndef _HELI_SYSDEF_H_
#define _HELI_SYSDEF_H_


/*****************************************************************************
*ָ��ͷ���
******************************************************************************/
#define INSHEAD				__int16

#define InitIns(ins)		(ins=0x0000)
#define GetFirstIns(ins)	(ins&0x000f)
#define GetSecondIns(ins)	(ins&0x00ff)
#define GetThirdIns(ins)	(ins&0x0fff)



/*****************************************************************************
*ָ�����
******************************************************************************/
#define FEM_EMERGENCY						0x0000				/*Ӧ��ָ��								*/
#define FIE_INSPARSEERR						0x0001				/*ָ���������ָ��						*/
#define FNT_NETTESTTEXT						0x0002				/*����ͨ�Ŵ��ı�����ָ��				*/
#define FNT_NETTESTTEXTREPLY				0x0003				/*����ͨ�Ŵ��ı����Իظ�ָ��			*/
#define FCT_NETCOMTEST						0x0004				/*����ͨ�Ų���ָ��						*/
#define FCT_NETCOMTESTREPLY					0x0005				/*����ͨ�Ų��Իظ�ָ��					*/
#define FET_EQUIPMENTTEST					0x0006				/*�豸���Զ�����ָ�					*/
#define SAT_SERVOACTOR_TST					0x0016				/*�������ָ��							*/
#define STT_THROTTLE_TST					0x0026				/*���Ų���ָ��							*/
#define STT_TILTDISC_TST					0x0036				/*��б�̲���ָ��						*/
#define SIT_IMU_TST							0x0046				/*IMU����������ָ�					*/
#define TIT_IMUTEST_START					0x0146				/*��ʼIMU����ָ��						*/
#define TIT_IMUTEST_STOP					0x0246				/*����IMU����ָ��						*/
#define TIT_IMUTEST_DATA					0x0346				/*IMU��������ָ��						*/
#define SGT_GPS_TST							0x0056				/*GPS����������ָ�					*/
#define TGT_GPSTEST_START					0x0156				/*��ʼGPS����ָ��						*/
#define TGT_GPSTEST_STOP					0x0256				/*����GPS����ָ��						*/
#define TGT_GPSTEST_DATA					0x0356				/*GPS��������ָ��						*/
#define SOT_OPTTRACE_TST					0x0066				/*��ѧ׷��ϵͳ����������ָ�			*/
#define TOT_OPTTRACETEST_START				0x0166				/*��ʼ��ѧ׷��ϵͳ����ָ��				*/
#define TOT_OPTTRACETEST_STOP				0x0266				/*������ѧ׷��ϵͳ����ָ��				*/
#define TOT_OPTTRACETEST_DATA				0x0366				/*��ѧ׷��ϵͳ��������ָ��				*/
#define SAT_ALTIMETER_TST					0x0076				/*�߶ȼƲ���������ָ�				*/
#define TAT_ALTIMETERTEST_START				0x0176				/*��ʼ�߶ȼƲ���ָ��					*/
#define TAT_ALTIMETERTEST_STOP				0x0276				/*�����߶ȼƲ���ָ��					*/
#define TAT_ALTIMETERTEST_DATA				0x0376				/*�߶ȼƲ�������ָ��					*/
#define FOC_OPERATIONCOMMAND				0x0007				/*�������ƶ�����ָ�					*/
#define SFT_FLYING_TASK						0x0017				/*��������������ָ�					*/
#define TFT_STARTTASK						0x0117				/*��ʼ��������ָ��						*/
#define TFT_STARTTASKREPLY					0x0217				/*��ʼ�������񷵻�ָ��					*/
#define TFT_STARTSTOP						0x0317				/*������������ָ��						*/
#define TFT_STARTSTOPREPLY					0x0417				/*�����������񷵻�ָ��					*/
#define SAS_ACTORSET_TASK					0x0027				/*�������������ָ�					*/
#define TAS_ACTORSET						0x0127				/*�������ָ��							*/
#define STS_TILTDISCSET_TASK				0x0037				/*��б������������ָ�				*/
#define TTS_TILTDISCSET						0x0137				/*��б������ָ��						*/
#define SPT_PATH_TASK						0x0047				/*·������������ָ�					*/
#define TPT_LOADPATHPOINT_START				0x0147				/*��ʼ·������ָ��						*/
#define TPT_LOADPATHPOINT_STOP				0x0247				/*����·������ָ��						*/
#define TPT_LOADPATHPOINTS					0x0347				/*����·����ָ��						*/
#define TPT_LOADPATHPOINTS_REPLY			0x0447				/*����·����ظ�ָ��					*/
#define TPT_LOADPATHPOINTS_CHECK			0x0547				/*·�����鷵��ָ��					*/
#define FIT_FLYINGSTATEDATA					0x0008				/*�������ݷ���ָ��						*/

/*****************************************************************************
*ָ���������
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
