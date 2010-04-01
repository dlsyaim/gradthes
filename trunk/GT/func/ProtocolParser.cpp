#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "..\GT.h"
#include "..\MainFrm.h"
#include "ProtocolParser.h"
#include "..\MsgType.h"
#include "..\CommunicationTestDialog.h"


CProtocolParser::CProtocolParser()
{
	
}

CProtocolParser::~CProtocolParser()
{
	
}

bool CProtocolParser::OnInsData(void * Target,__int32 Len)
{
	if(Target==NULL)
	{
		return false;
	}
	INSHEAD * inshead = (INSHEAD *)Target;
	INSHEAD V = * inshead;
	INSHEAD F = GetFirstIns(V);
	INSHEAD S = GetSecondIns(V);
	INSHEAD T = GetThirdIns(V);

	switch(F)
	{
	case FEM_EMERGENCY:			/*应急*/
		this->OnEmergency(Target,Len);
		break;
	case FCT_NETCOMTEST:		/*网络通信测试*/	
		this->OnComTest(Target,Len);
		break;
	case FCT_NETCOMTESTREPLY:	/*网络通信测试应答*/
		this->OnComTestReply(Target,Len);
		break;
	case FOC_OPERATIONCOMMAND:	/*操作命令*/
		switch(S)
		{
		case SFT_FLYING_TASK:					/*飞行任务*/
			switch(T)
			{
			case TFT_STARTTASK:										/*开始飞行任务*/
				this->OnStartTask(Target,Len);
				break;
			case TFT_STARTTASKREPLY:								/*开始飞行任务回复*/
				this->OnStartTaskReply(Target,Len);
				break;
			case TFT_STARTSTOP:										/*结束飞行任务*/
				this->OnStopTask(Target,Len);
				break;	
			case TFT_STARTSTOPREPLY:								/*结束飞行任务回复*/
				this->OnStopTaskReply(Target,Len);
				break;
			default:
				ParseError(V);
				break;
			}
			break;
		case SAS_ACTORSET_TASK:					/*舵机设置*/
			switch (T)
			{
			case TAS_ACTORSET:										/*舵机设置*/
				this->OnServoActorSet(Target,Len);
				break;
			default:
				ParseError(V);
				break;
			}
			break;
		case STS_TILTDISCSET_TASK:				/*倾斜盘设置*/
			switch (T)
			{
			case TTS_TILTDISCSET:									/*倾斜盘设置*/
				this->OnTileDiscSet(Target,Len);
				break;
			default:
				ParseError(V);
				break;
			}
			break;
		case SPT_PATH_TASK:						/*路径设置*/
			switch (T)
			{
			case TPT_LOADPATHPOINT_START:							/*开始路径设置*/
				this->OnLoadPathPointStart(Target,Len);
				break;
			case TPT_LOADPATHPOINT_STOP:							/*结束路径设置*/
				this->OnLoadPathPointStop(Target,Len);
				break;
			case TPT_LOADPATHPOINTS:								/*路径点设置数据*/
				this->OnLoadPathPoint(Target,Len);
				break;
			case TPT_LOADPATHPOINTS_REPLY:							/*路径点设置回复*/
				this->OnLoadPathPointSerial(Target,Len);
				break;
			case TPT_LOADPATHPOINTS_CHECK:							/*开始路径设置检测*/
				this->OnPathPointState(Target,Len);
				break;
			default:
				ParseError(V);
				break;
			}
			break;
		default:
			ParseError(V);
			break;
		}
		break;
	case FIT_FLYINGSTATEDATA:	/*飞行数据*/
		this->OnFlyingState(Target,Len);
		break;
	case FIE_INSPARSEERR:		/*指令解析错误*/
		this->OnErrorInsHead(Target,Len);
		break;
	case FET_EQUIPMENTTEST:		/*设备测试*/
		switch(S)
		{
		case SAT_SERVOACTOR_TST:				/*舵机测试*/
			this->OnServoActorTest(Target,Len);
			break;
		case STT_THROTTLE_TST:					/*油门测试*/
			this->OnThrottleTest(Target,Len);
			break;
		case STT_TILTDISC_TST:					/*倾斜盘测试*/
			this->OnTiltDiscTest(Target,Len);
			break;
		case SIT_IMU_TST:						/*IMU测试*/
			switch(T)
			{
			case TIT_IMUTEST_START:									/*开始IMU测试*/
				this->OnIMUTestStart(Target,Len);
				break;
			case TIT_IMUTEST_STOP:									/*结束IMU测试*/
				this->OnIMUTestStop(Target,Len);
				break;
			case TIT_IMUTEST_DATA:									/*IMU测试数据*/
				this->OnIMUTestData(Target,Len);
				break;
			default:
				ParseError(V);
				break;
			}
			break;
		case SGT_GPS_TST:						/*GPS测试*/
			switch(T)
			{
			case TGT_GPSTEST_START:									/*开始GPS测试*/
				this->OnGPSTestStart(Target,Len);
				break;
			case TGT_GPSTEST_STOP:									/*结束GPS测试*/
				this->OnGPSTestStop(Target,Len);
				break;
			case TGT_GPSTEST_DATA:									/*GPS测试数据*/
				this->OnGPSTestData(Target,Len);
				break;
			default:
				ParseError(V);
				break;
			}
			break;
		case SOT_OPTTRACE_TST:					/*光学追踪系统测试*/
			switch(T)
			{
			case TOT_OPTTRACETEST_START:							/*开始光学追踪系统测试*/
				this->OnOPTTTestStart(Target,Len);
				break;
			case TOT_OPTTRACETEST_STOP:								/*结束光学追踪系统测试*/
				this->OnOPTTTestStop(Target,Len);
				break;
			case TOT_OPTTRACETEST_DATA:								/*光学追踪系统测试数据*/
				this->OnOPTTTestData(Target,Len);
				break;
			default:
				ParseError(V);
				break;
			}
			break;
		case SAT_ALTIMETER_TST:					/*高度计测试*/
			switch(T)
			{
			case TAT_ALTIMETERTEST_START:							/*开始高度计测试*/
				this->OnAltiTestStart(Target,Len);
				break;
			case TAT_ALTIMETERTEST_STOP:							/*结束高度计测试*/
				this->OnAltiTestStop(Target,Len);
				break;
			case TAT_ALTIMETERTEST_DATA:							/*光学高度计测试数据*/
				this->OnAltiTestData(Target,Len);
				break;
			default:
				ParseError(V);
				break;
			}
			break;
		default:
			ParseError(V);
			break;
		}
		break;
	case FNT_NETTESTTEXT:		/*网络通信测试带文本*/
		this->OnComTestT(Target,Len);
		break;
	case FNT_NETTESTTEXTREPLY:	/*网络通信测试带文本回复*/
		this->OnComTestTReply(Target,Len);
		break;
	default :					/*无定义*/
		ParseError(V);
	}
	return true;
}

void CProtocolParser::ParseError(INSHEAD V)
{
	printf("%x\n",V);
}

void CProtocolParser::OnEmergency(void * Target, __int32 Len)
{
	if(Len != 4)
	{
		printf("error ins para OnEmergency\n");
		return;
	}
	char * tmp = (char *)Target;
	__int16 Errorcode = *(tmp+2);
	printf("OnEmergency Errorcode %x \n",Errorcode);
}

void CProtocolParser::OnErrorInsHead(void * Target, __int32 Len)
{
	if(Len != 4)
	{
		printf("error ins para OnErrorInsHead\n");
		return;
	}
	char * tmp = (char *)Target;
	__int16 ErrorInsHead = *(tmp+2);
	printf("OnErrorInsHead %x \n",ErrorInsHead);
}

void CProtocolParser::OnComTestT(void * Target, __int32 Len)
{
	if(Len != 102)
	{
		printf("error ins para OnComTestT\n");
		return;
	}
	char * tmp = (char *)Target;
	char * text = (tmp+2);
	printf("OnComTestT  text %s\n",text);
}

void CProtocolParser::OnComTestTReply(void * Target, __int32 Len)
{
	if(Len != 102)
	{
		printf("error ins para OnComTestTReply\n");
		return;
	}
	char * tmp = (char *)Target;
	char * text = (tmp+2);

	printf("OnComTestTReply  text %s\n",text);
	/***** Here the communication test dialog must be informed *****/
	CGTApp* m_mainApp = (CGTApp*)AfxGetApp();
	if (m_mainApp == NULL) {
		AfxMessageBox("Failed to get the application", MB_OK | MB_ICONSTOP);
	} else if (!m_mainApp->getCtd()->PostMessage(COMMUNICATION_TEST_REPLY_MSG, 0, 0)) {
		AfxMessageBox("Failed to post messages", MB_OK | MB_ICONSTOP);
	}

	//PostMessage(GetDlgItem(IDD_COMMUNICATIONTEST_DIALOG), COMMUNICATION_TEST_REPLY_MSG, 0, 0);
}

void CProtocolParser::OnComTest(void * Target, __int32 Len)
{
	if(Len != 2)
	{
		printf("error ins para OnComTest\n");
		return;
	}
	printf("OnComTest no data\n");
}

void CProtocolParser::OnComTestReply(void * Target, __int32 Len)
{
	if(Len != 2)
	{
		printf("error ins para OnComTestReply\n");
		return;
	}
	printf("OnComTestReply no data\n");
}

void CProtocolParser::OnServoActorTest(void * Target, __int32 Len)
{
	if(Len != 10)
	{
		printf("error ins para OnServoActorTest\n");
		return;
	}
	char * tmp = (char *)Target;
	struct ServoActorTstInsData * satid = (struct ServoActorTstInsData *)(tmp+2);
	printf("OnServoActorTest  serial %d   value %f\n",satid->ActorSerial,satid->SetPWM);
}

void CProtocolParser::OnThrottleTest(void * Target, __int32 Len)
{
	if(Len != 6)
	{
		printf("error ins para OnThrottleTest\n");
		return;
	}
	char * tmpc = (char *)Target;
	struct ThrottleTstInsData * tmp = (struct ThrottleTstInsData *)(tmpc+2);
	printf("OnThrottleTest value %f\n",tmp->SetPWM);
}

void CProtocolParser::OnTiltDiscTest(void * Target, __int32 Len)
{
	if(Len != 14)
	{
		printf("error ins para OnTiltDiscTest\n");
		return;
	}
	char * tmpc = (char *)Target;
	struct TiltDiscTstInsData * tmp = (struct TiltDiscTstInsData *)(tmpc+2);
	printf("OnTiltDiscTest a1 %f a2 %f a3 %f \n",tmp->CollectSetAngle,tmp->RollSetAngle,tmp->PitchetAngle);
}

void CProtocolParser::OnIMUTestStart(void * Target, __int32 Len)
{
	if(Len != 2)
	{
		printf("error ins para OnIMUTestStart\n");
		return;
	}
	printf("OnIMUTestStart  no data\n");
}

void CProtocolParser::OnIMUTestStop(void * Target, __int32 Len)
{
	if(Len != 2)
	{
		printf("error ins para OnIMUTestStop\n");
		return;
	}
	printf("OnIMUTestStop no data\n");
}

void CProtocolParser::OnIMUTestData(void * Target, __int32 Len)
{
	if(Len != 54)
	{
		printf("error ins para OnIMUTestData\n");
		return;
	}
	char * tmpc = (char *)Target;
	struct IMUTestData * tmp = (struct IMUTestData *)(tmpc+2);
	printf("OnIMUTestData %d %f %f %f %f %f %f %f %f %f %f %f %f\n",tmp->IMUState,
		tmp->N_Speed,tmp->E_Speed,tmp->D_Speed,
		tmp->N_Acc,tmp->E_Acc,tmp->D_Acc,
		tmp->phi,tmp->theta,tmp->psi,
		tmp->phi_Acc,tmp->theta_Acc,tmp->psi_Acc);
}

void CProtocolParser::OnGPSTestStart(void * Target, __int32 Len)
{
	if(Len != 2)
	{
		printf("error ins para OnGPSTestStart\n");
		return;
	}
	printf("OnGPSTestStart no data\n");
}

void CProtocolParser::OnGPSTestStop(void * Target, __int32 Len)
{
	if(Len != 2)
	{
		printf("error ins para OnGPSTestStop\n");
		return;
	}
	printf("OnGPSTestStop no data\n");
}

void CProtocolParser::OnGPSTestData(void * Target, __int32 Len)
{
	printf("OnGPSTestData  data no define correctly\n");
}

void CProtocolParser::OnOPTTTestStart(void * Target, __int32 Len)
{
	if(Len != 2)
	{
		printf("error ins para OnOPTTTestStart\n");
		return;
	}
	printf("OnOPTTTestStart  no data\n");
}

void CProtocolParser::OnOPTTTestStop(void * Target, __int32 Len)
{
	if(Len != 2)
	{
		printf("error ins para OnOPTTTestStop\n");
		return;
	}
	printf("OnOPTTTestStop no data\n");
}

void CProtocolParser::OnOPTTTestData(void * Target, __int32 Len)
{
	if(Len != 66)
	{
		printf("error ins para OnOPTTTestData\n");
		return;
	}
	char * tmpc = (char *)Target;
	struct OPTTRACETestData * tmp = (struct OPTTRACETestData *)(tmpc+2);
	printf("OnOPTTTestData %d \n%f %f %f %f %f %f %f %f %f\n %f %f %f %f %f %f\n",tmp->OPTState,
		tmp->N_Pos,tmp->E_Pos,tmp->D_Pos,
		tmp->N_Speed,tmp->E_Speed,tmp->D_Speed,
		tmp->N_Acc,tmp->E_Acc,tmp->D_Acc,
		tmp->phi,tmp->theta,tmp->psi,
		tmp->phi_Acc,tmp->theta_Acc,tmp->psi_Acc);
	printf("OnOPTTTestData\n");
}

void CProtocolParser::OnAltiTestStart(void * Target, __int32 Len)
{
	if(Len != 2)
	{
		printf("error ins para OnAltiTestStart\n");
		return;
	}
	printf("OnAltiTestStart no data\n");
}

void CProtocolParser::OnAltiTestStop(void * Target, __int32 Len)
{
	if(Len != 2)
	{
		printf("error ins para OnAltiTestStop\n");
		return;
	}
	printf("OnAltiTestStop no data\n");
}

void CProtocolParser::OnAltiTestData(void * Target, __int32 Len)
{
	printf("OnAltiTestData no defined correctly\n");
}

void CProtocolParser::OnStartTask(void * Target, __int32 Len)
{
	if(Len != 2)
	{
		printf("error ins para OnStartTask\n");
		return;
	}
	printf("OnStartTask no data\n");
}

void CProtocolParser::OnStartTaskReply(void * Target, __int32 Len)
{
	if(Len != 6)
	{
		printf("error ins para OnStartTaskReply\n");
		return;
	}
	char * tmpc = (char *)Target;
	__int32 * tmp = (__int32 *)(tmpc+2);
	printf("OnStartTaskReply %x\n",*tmp);
}

void CProtocolParser::OnStopTask(void * Target, __int32 Len)
{
	if(Len != 2)
	{
		printf("error ins para OnStopTask\n");
		return;
	}
	printf("OnStopTask no data\n");
}

void CProtocolParser::OnStopTaskReply(void * Target, __int32 Len)
{
	if(Len != 6)
	{
		printf("error ins para OnStopTaskReply\n");
		return;
	}
	char * tmpc = (char *)Target;
	__int32 * tmp = (__int32 *)(tmpc+2);
	printf("OnStopTaskReply %x\n",*tmp);
}

void CProtocolParser::OnServoActorSet(void * Target, __int32 Len)
{
	if(Len != 162)
	{
		printf("error ins para OnServoActorSet\n");
		return;
	}
	char * tmpc = (char *)Target;
	ServoActorData * tmp = (ServoActorData *)(tmpc+2);
	printf("OnServoActorSet with data and no show here\n");
}

void CProtocolParser::OnTileDiscSet(void * Target, __int32 Len)
{
	if(Len != 242)
	{
		printf("error ins para OnTileDiscSet\n");
		return;
	}
	char * tmpc = (char *)Target;
	TiltDiscData * tmp = (TiltDiscData *)(tmpc+2);
	printf("OnTileDiscSet with data and no show here\n");
}

void CProtocolParser::OnLoadPathPointStart(void * Target, __int32 Len)
{
	if(Len != 2)
	{
		printf("error ins para OnLoadPathPointStart\n");
		return;
	}
	printf("OnLoadPathPointStart no data\n");
}

void CProtocolParser::OnLoadPathPointStop(void * Target, __int32 Len)
{
	if(Len != 2)
	{
		printf("error ins para OnLoadPathPointStop\n");
		return;
	}
	printf("OnLoadPathPointStop no data\n");
}

void CProtocolParser::OnLoadPathPoint(void * Target, __int32 Len)
{
	if(Len != 34)
	{
		printf("error ins para OnLoadPathPoint\n");
		return;
	}
	char * tmpc = (char *)Target;
	PathPointData * tmp = (PathPointData *)(tmpc+2);
	printf("OnLoadPathPoint %d %f %f %f %f\n",tmp->serial,tmp->StayTime,tmp->Coordinate_X,tmp->Coordinate_Y,tmp->Coordinate_Z);
}

void CProtocolParser::OnLoadPathPointSerial(void * Target, __int32 Len)
{
	if(Len != 6)
	{
		printf("error ins para OnLoadPathPointSerial\n");
		return;
	}
	char * tmpc = (char *)Target;
	__int32 * tmp = (__int32 *)(tmpc+2);
	printf("OnLoadPathPointSerial  %d \n",*tmp);
}

void CProtocolParser::OnPathPointState(void * Target, __int32 Len)
{
	if(Len != 6)
	{
		printf("error ins para OnLoadPathPointSerial\n");
		return;
	}
	char * tmpc = (char *)Target;
	__int32 * tmp = (__int32 *)(tmpc+2);
	printf("OnPathPointState *d\n",*tmp);
}

void CProtocolParser::OnFlyingState(void * Target, __int32 Len)
{
	printf("OnFlyingState no defined correctly\n");
}
