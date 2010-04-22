#ifndef _HELISYS_FLYINSDEFINE_H_
#define _HELISYS_FLYINSDEFINE_H_


/*****************************************************************************
*ָ��ͷ���
******************************************************************************/
#define INSHEAD				unsigned short
#define InitIns(ins)		(ins=0x0000)
#define GetFirstIns(ins)	(ins&0x0f00)
#define GetSecondIns(ins)	(ins&0x0ff0)
#define GetThirdIns(ins)	(ins&0x0fff)
/*****************************************************************************
*ָ�����
******************************************************************************/
#define FEM_EMERGENCY						0x0100				/*Ӧ��ָ��								*/
#define FIE_INSPARSEERR						0x0200				/*ָ���������ָ��						*/
#define FNT_NETTESTTEXT						0x0300				/*����ͨ�Ŵ��ı�����ָ��				*/
#define FNT_NETTESTTEXTREPLY				0x0400				/*����ͨ�Ŵ��ı����Իظ�ָ��			*/
#define FCT_NETCOMTEST						0x0500				/*����ͨ�Ų���ָ��						*/
#define FCT_NETCOMTESTREPLY					0x0600				/*����ͨ�Ų��Իظ�ָ��					*/
#define FET_EQUIPMENTTEST					0x0700				/*�豸���Զ�����ָ�					*/
#define SAT_SERVOACTOR_TST					0x0710				/*�������ָ��							*/
#define STT_THROTTLE_TST					0x0720				/*���Ų���ָ��							*/
#define STT_TILTDISC_TST					0x0730				/*��б�̲���ָ��						*/
#define SIT_IMU_TST							0x0740				/*IMU����������ָ�					*/
#define TIT_IMUTEST_START					0x0741				/*��ʼIMU����ָ��						*/
#define TIT_IMUTEST_STOP					0x0742				/*����IMU����ָ��						*/
#define TIT_IMUTEST_DATA					0x0743				/*IMU��������ָ��						*/
#define SGT_GPS_TST							0x0750				/*GPS����������ָ�					*/
#define TGT_GPSTEST_START					0x0751				/*��ʼGPS����ָ��						*/
#define TGT_GPSTEST_STOP					0x0752				/*����GPS����ָ��						*/
#define TGT_GPSTEST_DATA					0x0753				/*GPS��������ָ��						*/
#define SOT_OPTTRACE_TST					0x0760				/*��ѧ׷��ϵͳ����������ָ�			*/
#define TOT_OPTTRACETEST_START				0x0761				/*��ʼ��ѧ׷��ϵͳ����ָ��				*/
#define TOT_OPTTRACETEST_STOP				0x0762				/*������ѧ׷��ϵͳ����ָ��				*/
#define TOT_OPTTRACETEST_DATA				0x0763				/*��ѧ׷��ϵͳ��������ָ��				*/
#define SAT_ALTIMETER_TST					0x0770				/*�߶ȼƲ���������ָ�				*/
#define TAT_ALTIMETERTEST_START				0x0771				/*��ʼ�߶ȼƲ���ָ��					*/
#define TAT_ALTIMETERTEST_STOP				0x0772				/*�����߶ȼƲ���ָ��					*/
#define TAT_ALTIMETERTEST_DATA				0x0773				/*�߶ȼƲ�������ָ��					*/
#define FTS_TASK_SET						0x0800              /*�������ö���ָ�					*/
#define SAS_ACTORSET_TASK					0x0810				/*�������������ָ�					*/
#define TAS_ACTORSET						0x0811				/*�������ָ��							*/
#define STS_TILTDISCSET_TASK				0x0820				/*��б������������ָ�				*/
#define TTS_TILTDISCSET						0x0821				/*��б������ָ��						*/
#define SPT_PATH_TASK						0x0830				/*·������������ָ�					*/
#define TPT_LOADPATHPOINT_START				0x0831				/*��ʼ·������ָ��						*/
#define TPT_LOADPATHPOINT_STOP				0x0832				/*����·������ָ��						*/
#define TPT_LOADPATHPOINTS					0x0833				/*����·����ָ��						*/
#define TPT_LOADPATHPOINTS_REPLY			0x0834				/*����·����ظ�ָ��					*/
#define TPT_LOADPATHPOINTS_CHECK			0x0835				/*·�����鷵��ָ��					*/
#define TPT_LOADHELIPARA			        0x0840				/*���طɻ�����ָ��					    */
#define TPT_LOADCONTROLPARA			        0x0850				/*���ؿ��Ʋ���ָ�� 					    */

#define FOC_OPERATIONCOMMAND				0x0a00				/*�������ƶ�����ָ�					*/
#define SFT_FLYING_TASK						0x0a10				/*��������������ָ�					*/
#define TFT_STARTTASK						0x0a11				/*��ʼ��������ָ��						*/
#define TFT_STARTTASKREPLY					0x0a12				/*��ʼ�������񷵻�ָ��					*/
#define TFT_STOPTASK						0x0a13				/*������������ָ��						*/
#define TFT_STARTSTOPREPLY					0x0a14				/*�����������񷵻�ָ��					*/
#define FIT_FLYINGSTATEDATA					0x0b00				/*�������ݷ���ָ��						*/
#define FIT_FLYINGSTATEDATAACT				0x0c00				/*�������ݷ���ȷ��ָ��					*/
///////////////////////////////////////////////////////////////////////

#define INSTRUCTION_LENGTH                  2
#define COM_TEXT_LENGTH 100

#endif

