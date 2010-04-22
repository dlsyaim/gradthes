#ifndef _HELISYS_FLYINSDEFINE_H_
#define _HELISYS_FLYINSDEFINE_H_


/*****************************************************************************
*指令头设计
******************************************************************************/
#define INSHEAD				unsigned short
#define InitIns(ins)		(ins=0x0000)
#define GetFirstIns(ins)	(ins&0x0f00)
#define GetSecondIns(ins)	(ins&0x0ff0)
#define GetThirdIns(ins)	(ins&0x0fff)
/*****************************************************************************
*指令设计
******************************************************************************/
#define FEM_EMERGENCY						0x0100				/*应急指令								*/
#define FIE_INSPARSEERR						0x0200				/*指令解析错误指令						*/
#define FNT_NETTESTTEXT						0x0300				/*网络通信带文本测试指令				*/
#define FNT_NETTESTTEXTREPLY				0x0400				/*网络通信带文本测试回复指令			*/
#define FCT_NETCOMTEST						0x0500				/*网络通信测试指令						*/
#define FCT_NETCOMTESTREPLY					0x0600				/*网络通信测试回复指令					*/
#define FET_EQUIPMENTTEST					0x0700				/*设备测试二级子指令集					*/
#define SAT_SERVOACTOR_TST					0x0710				/*舵机测试指令							*/
#define STT_THROTTLE_TST					0x0720				/*油门测试指令							*/
#define STT_TILTDISC_TST					0x0730				/*倾斜盘测试指令						*/
#define SIT_IMU_TST							0x0740				/*IMU测试三级子指令集					*/
#define TIT_IMUTEST_START					0x0741				/*开始IMU测试指令						*/
#define TIT_IMUTEST_STOP					0x0742				/*结束IMU测试指令						*/
#define TIT_IMUTEST_DATA					0x0743				/*IMU测试数据指令						*/
#define SGT_GPS_TST							0x0750				/*GPS测试三级子指令集					*/
#define TGT_GPSTEST_START					0x0751				/*开始GPS测试指令						*/
#define TGT_GPSTEST_STOP					0x0752				/*结束GPS测试指令						*/
#define TGT_GPSTEST_DATA					0x0753				/*GPS测试数据指令						*/
#define SOT_OPTTRACE_TST					0x0760				/*光学追踪系统测试三级子指令集			*/
#define TOT_OPTTRACETEST_START				0x0761				/*开始光学追踪系统测试指令				*/
#define TOT_OPTTRACETEST_STOP				0x0762				/*结束光学追踪系统测试指令				*/
#define TOT_OPTTRACETEST_DATA				0x0763				/*光学追踪系统测试数据指令				*/
#define SAT_ALTIMETER_TST					0x0770				/*高度计测试三级子指令集				*/
#define TAT_ALTIMETERTEST_START				0x0771				/*开始高度计测试指令					*/
#define TAT_ALTIMETERTEST_STOP				0x0772				/*结束高度计测试指令					*/
#define TAT_ALTIMETERTEST_DATA				0x0773				/*高度计测试数据指令					*/
#define FTS_TASK_SET						0x0800              /*任务设置二级指令集					*/
#define SAS_ACTORSET_TASK					0x0810				/*舵机设置三级子指令集					*/
#define TAS_ACTORSET						0x0811				/*舵机设置指令							*/
#define STS_TILTDISCSET_TASK				0x0820				/*倾斜盘设置三级子指令集				*/
#define TTS_TILTDISCSET						0x0821				/*倾斜盘设置指令						*/
#define SPT_PATH_TASK						0x0830				/*路径任务三级子指令集					*/
#define TPT_LOADPATHPOINT_START				0x0831				/*开始路径加载指令						*/
#define TPT_LOADPATHPOINT_STOP				0x0832				/*结束路径加载指令						*/
#define TPT_LOADPATHPOINTS					0x0833				/*加载路径点指令						*/
#define TPT_LOADPATHPOINTS_REPLY			0x0834				/*加载路径点回复指令					*/
#define TPT_LOADPATHPOINTS_CHECK			0x0835				/*路径点检查返回指令					*/
#define TPT_LOADHELIPARA			        0x0840				/*加载飞机参数指令					    */
#define TPT_LOADCONTROLPARA			        0x0850				/*加载控制参数指令 					    */

#define FOC_OPERATIONCOMMAND				0x0a00				/*操作控制二级子指令集					*/
#define SFT_FLYING_TASK						0x0a10				/*飞行任务三级子指令集					*/
#define TFT_STARTTASK						0x0a11				/*开始飞行任务指令						*/
#define TFT_STARTTASKREPLY					0x0a12				/*开始飞行任务返回指令					*/
#define TFT_STOPTASK						0x0a13				/*结束飞行任务指令						*/
#define TFT_STARTSTOPREPLY					0x0a14				/*结束飞行任务返回指令					*/
#define FIT_FLYINGSTATEDATA					0x0b00				/*飞行数据返回指令						*/
#define FIT_FLYINGSTATEDATAACT				0x0c00				/*飞行数据返回确认指令					*/
///////////////////////////////////////////////////////////////////////

#define INSTRUCTION_LENGTH                  2
#define COM_TEXT_LENGTH 100

#endif

