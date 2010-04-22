#include "StdAfx.h"
#include <gl/glut.h>
#include <vector>
#include "GSProtocolParser.h"
#include "GT.h"
#include "GTView.h"
#include "IMUTestFormView.h"
#include "OPTFormView.h"
#include "GridView.h"
#include "LeftView.h"
#include "GTDoc.h"
#include "MsgType.h"
#include "CommunicationTestDialog.h"



CGSProtocolParser::CGSProtocolParser(void)
{
}

CGSProtocolParser::~CGSProtocolParser(void)
{
}


void CGSProtocolParser::OnComTestTReply(void * Target, __int32 Len)
{
	if(Len != (COM_TEXT_LENGTH + INSTRUCTION_LENGTH) )
	{
		AfxMessageBox(_T("Error ins para OnComTestTReply"), MB_OK | MB_ICONSTOP);
		return;
	}
	char * tmp = (char *)Target;
	char * text = (tmp + INSTRUCTION_LENGTH);

	/***** Here the communication test dialog must be informed *****/
	CGTApp* m_mainApp = (CGTApp*)AfxGetApp();
	if (m_mainApp == NULL) {
		AfxMessageBox("Failed to get the application pointer", MB_OK | MB_ICONSTOP);
	} else if (!m_mainApp->getCtd()->SendMessage(COMMUNICATION_TEST_REPLY_MSG, 0, 0)) {
		AfxMessageBox("Failed to inform the communication test dialog", MB_OK | MB_ICONSTOP);
	}
}

void CGSProtocolParser::OnIMUTestData(void * Target, __int32 Len) 
{
	if(Len != (sizeof(IMUTestData) + INSTRUCTION_LENGTH))
	{
		AfxMessageBox("No IMU test data back", MB_OK | MB_ICONSTOP);
		return;
	}

	/***** The IMUTestFormView and CGTView must be informed *****/

	char * tmpc = (char *)Target;
	struct IMUTestData * tmp = (struct IMUTestData *)(tmpc + INSTRUCTION_LENGTH);
	CGTApp* m_mainApp = (CGTApp*)AfxGetApp();
	CGTDoc* m_pDoc = m_mainApp->getDoc();
	if (m_pDoc) {
		m_pDoc->IMUView->updateData(tmp);
		::SendMessage(m_pDoc->IMUView->m_hWnd, IMU_TEST_REPLY_MSG, 0, 0);
		m_pDoc->lowerRightView->updateIMUData(tmp);
	}
}

void CGSProtocolParser::OnOPTTTestData(void * Target, __int32 Len)
{
	if(Len != (sizeof(OPTTRACETestData) + INSTRUCTION_LENGTH))
	{
		printf("error ins para OnOPTTTestData\n");
		return;
	}
	char * tmpc = (char *)Target;
	struct OPTTRACETestData * tmp = (struct OPTTRACETestData *)(&(tmpc[INSTRUCTION_LENGTH]));
	CGTApp* m_mainApp = (CGTApp*)AfxGetApp();
	CGTDoc* m_pDoc = m_mainApp->getDoc();
	if (m_pDoc) {
		m_pDoc->optView->updateData(tmp);
		::SendMessage(m_pDoc->optView->m_hWnd, OPT_TEST_REPLY_MSG, 0, 0);
		m_pDoc->lowerRightView->updateOPTData(tmp);
	}
}

void CGSProtocolParser::OnLoadPathPointSerial(void *Target, int Len)
{
	if(Len != (INSTRUCTION_LENGTH + sizeof(int)))
	{
		AfxMessageBox("error ins para OnLoadPathPointSerial\n", MB_OK | MB_ICONSTOP);
		return;
	}
	char * tmpc = (char *)Target;
	__int32 * tmp = (__int32 *)(tmpc + INSTRUCTION_LENGTH);
	CGTApp* m_mainApp = (CGTApp*)AfxGetApp();
	CGTDoc* m_pDoc = m_mainApp->getDoc();
	if (m_pDoc) {
		m_pDoc->gridView->setReceived(tmp);
		::SendMessage(m_pDoc->gridView->m_hWnd, LOAD_POINT_REPLY_MSG, 0, 0);
	}
}

void CGSProtocolParser::OnPathPointState(void *Target, int Len)
{
	if(Len != (INSTRUCTION_LENGTH + sizeof(int)))
	{
		AfxMessageBox("error ins para OnLoadPathPointSerial\n", MB_OK | MB_ICONSTOP);
		return;
	}

	char * tmpc = (char *)Target;
	__int32 * tmp = (__int32 *)(tmpc + INSTRUCTION_LENGTH);

	CGTApp* m_mainApp = (CGTApp*)AfxGetApp();
	CGTDoc* m_pDoc = m_mainApp->getDoc();
	if (m_pDoc) {
		m_pDoc->gridView->setState(tmp);
		::SendMessage(m_pDoc->gridView->m_hWnd, PATH_CHECK_REPLY_MSG, 0, 0);
	}
}

void CGSProtocolParser::OnComTest(void * Target, __int32 Len)
{
	if(Len != INSTRUCTION_LENGTH)
	{
		AfxMessageBox("error ins para OnComTest\n", MB_OK | MB_ICONSTOP);
		return;
	}
	CGTApp* m_mainApp = (CGTApp*)AfxGetApp();
	char command[2];
	__int16* c = (__int16*)command;
	c[0] = FCT_NETCOMTESTREPLY;
	m_mainApp->getCln()->SendSvr(command, sizeof(command));
}

void CGSProtocolParser::OnStartTaskReply(void *Target, __int32 Len)
{
	
	if (Len != (INSTRUCTION_LENGTH + sizeof(int))) {
		AfxMessageBox("error ins para OnStartTaskReply\n");
		return;
	}

	char * tmpc = (char *)Target;
	__int32 * tmp = (__int32 *)(tmpc + INSTRUCTION_LENGTH);

	CGTApp* m_mainApp = (CGTApp*)AfxGetApp();
	CGTDoc* m_pDoc = m_mainApp->getDoc();
	if (m_pDoc) {
		m_pDoc->leftView->setIsStart(tmp);
		::SendMessage(m_pDoc->leftView->m_hWnd, START_TASK_REPLY_MSG, 0, 0);
	}

}

void CGSProtocolParser::OnStopTaskReply(void *Target, __int32 Len)
{
	if (Len != (INSTRUCTION_LENGTH + sizeof(int))) {
		AfxMessageBox("error ins para OnStartTaskReply\n");
		return;
	}

	char * tmpc = (char *)Target;
	__int32 * tmp = (__int32 *)(tmpc + INSTRUCTION_LENGTH);

	CGTApp* m_mainApp = (CGTApp*)AfxGetApp();
	CGTDoc* m_pDoc = m_mainApp->getDoc();
	if (m_pDoc) {
		m_pDoc->leftView->setIsStop(tmp);
		::SendMessage(m_pDoc->leftView->m_hWnd, STOP_TASK_REPLY_MSG, 0, 0);
	}

}


void CGSProtocolParser::OnFlyingState(void *Target, __int32 Len)
{
	if (Len != (sizeof(FlyStateGroup) + INSTRUCTION_LENGTH))
	{
		AfxMessageBox("Error in the fly state group's length", MB_OK | MB_ICONSTOP);
		return;
	}
	char *tempC = (char*)Target;
	pFlyStateGroup tempFSG = (pFlyStateGroup)(&tempC[INSTRUCTION_LENGTH]);

	CGTApp* m_mainApp = (CGTApp*)AfxGetApp();
	CGTDoc* m_pDoc = m_mainApp->getDoc();
	if (m_pDoc) {
		m_pDoc->leftView->setNewestFSG(tempFSG);
		::SendMessage(m_pDoc->leftView->m_hWnd, FLYING_STATE_DATA_MSG, 0, 0);
	}
}

bool CGSProtocolParser::OnInsData(void *tmpTarget, __int32 Len)
{		
	/*
	 * Because the recvbuf isn't pure any more, so we must split it according to the command header
	 */
	if(tmpTarget == NULL)
	{
		return false ;
	}
	// The index of the buffer - Target
	int curPos = 0;
	/* If not casting, then Target can't be added */
	char *buf = (char *)tmpTarget;
	char *Target = new char[Len];
	memcpy(Target, buf, Len);

	while (curPos < (Len - 1)) {
		// Parse the instruction header
		INSHEAD *inshead = (INSHEAD *)(buf + curPos);
		INSHEAD V = *inshead;
		INSHEAD F = GetFirstIns(V);
		INSHEAD S = GetSecondIns(V);
		INSHEAD T = GetThirdIns(V);

		switch(F)
		{
		case FEM_EMERGENCY:			/* Ӧ�� */
			this->OnEmergency(buf + curPos, 4);
			curPos += 4;
			break;
		case FCT_NETCOMTEST:		/* ����ͨ�Ų��� */	
			this->OnComTest(buf + curPos, INSTRUCTION_LENGTH);
			curPos += INSTRUCTION_LENGTH;
			break;
		case FCT_NETCOMTESTREPLY:	/* ����ͨ�Ų���Ӧ�� */
			this->OnComTestReply(buf + curPos, INSTRUCTION_LENGTH);
			curPos += INSTRUCTION_LENGTH;
			break;
		case FOC_OPERATIONCOMMAND:	/* �������� */
			switch(S)
			{
			case SFT_FLYING_TASK:					/*��������*/
				switch(T)
				{
				case TFT_STARTTASK:										/*��ʼ��������*/
					this->OnStartTask(buf + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TFT_STARTTASKREPLY:								/*��ʼ��������ظ�*/
					this->OnStartTaskReply(buf + curPos, 6);
					curPos += 6;
					break;
				case TFT_STOPTASK:										/*������������*/
					this->OnStopTask(buf + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;	
				case TFT_STARTSTOPREPLY:								/*������������ظ�*/
					this->OnStopTaskReply(buf + curPos, 6);
					curPos += 6;
					break;
				default:
					ParseError(V);
					break;
				}
				break;
			case SAS_ACTORSET_TASK:					/*�������*/
				switch (T)
				{
				case TAS_ACTORSET:										/*�������*/
					this->OnServoActorSet(buf + curPos, sizeof(ServoActorData) + INSTRUCTION_LENGTH);
					curPos += (sizeof(ServoActorData) + INSTRUCTION_LENGTH);
					break;
				default:
					ParseError(V);
					break;
				}
				break;
			case STS_TILTDISCSET_TASK:				/*��б������*/
				switch (T)
				{
				case TTS_TILTDISCSET:									/*��б������*/
					this->OnTileDiscSet(buf + curPos, sizeof(TiltDiscData) + INSTRUCTION_LENGTH);
					curPos += (sizeof(TiltDiscData) + INSTRUCTION_LENGTH);
					break;
				default:
					ParseError(V);
					break;
				}
				break;
			case SPT_PATH_TASK:						/*·������*/
				switch (T)
				{
				case TPT_LOADPATHPOINT_START:							/*��ʼ·������*/
					this->OnLoadPathPointStart(buf + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TPT_LOADPATHPOINT_STOP:							/*����·������*/
					this->OnLoadPathPointStop(buf + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TPT_LOADPATHPOINTS:								/*·������������*/
					this->OnLoadPathPoint(buf + curPos, sizeof(PathPointData) + INSTRUCTION_LENGTH);
					curPos += (sizeof(PathPointData) + INSTRUCTION_LENGTH);
					break;
				case TPT_LOADPATHPOINTS_REPLY:							/*·�������ûظ�*/
					this->OnLoadPathPointSerial(buf + curPos, 6);
					curPos += 6;
					break;
				case TPT_LOADPATHPOINTS_CHECK:							/*��ʼ·�����ü��*/
					this->OnPathPointState(buf + curPos, 6);
					curPos += 6;
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
		case FIT_FLYINGSTATEDATA:	/*��������*/
			this->OnFlyingState(buf + curPos, sizeof(FlyStateGroup) + INSTRUCTION_LENGTH);
			curPos += (sizeof(FlyStateGroup) + INSTRUCTION_LENGTH);
			break;
		case FIE_INSPARSEERR:		/*ָ���������*/
			this->OnErrorInsHead(buf + curPos, 4);
			curPos += 4;
			break;
		case FET_EQUIPMENTTEST:		/*�豸����*/
			switch(S)
			{
			case SAT_SERVOACTOR_TST:				/*�������*/
				this->OnServoActorTest(buf + curPos, sizeof(ServoActorTstInsData) + INSTRUCTION_LENGTH);
				curPos += (sizeof(ServoActorTstInsData) + INSTRUCTION_LENGTH);
				break;
			case STT_THROTTLE_TST:					/*���Ų���*/
				this->OnThrottleTest(buf + curPos, sizeof(ThrottleTstInsData) + INSTRUCTION_LENGTH);
				curPos += (sizeof(ThrottleTstInsData) + INSTRUCTION_LENGTH);
				break;
			case STT_TILTDISC_TST:					/*��б�̲���*/
				this->OnTiltDiscTest(buf + curPos, sizeof(TiltDiscTstInsData) + INSTRUCTION_LENGTH);
				curPos += (sizeof(TiltDiscTstInsData) + INSTRUCTION_LENGTH);
				break;
			case SIT_IMU_TST:						/*IMU����*/
				switch(T)
				{
				case TIT_IMUTEST_START:									/*��ʼIMU����*/
					this->OnIMUTestStart(buf + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TIT_IMUTEST_STOP:									/*����IMU����*/
					this->OnIMUTestStop(buf + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TIT_IMUTEST_DATA:									/*IMU��������*/
					this->OnIMUTestData(buf + curPos, sizeof(IMUTestData) + INSTRUCTION_LENGTH);
					curPos += (sizeof(IMUTestData) + INSTRUCTION_LENGTH);
					break;
				default:
					ParseError(V);
					break;
				}
				break;
			case SGT_GPS_TST:						/*GPS����*/
				switch(T)
				{
				case TGT_GPSTEST_START:									/*��ʼGPS����*/
					this->OnGPSTestStart(buf + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TGT_GPSTEST_STOP:									/*����GPS����*/
					this->OnGPSTestStop(buf + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TGT_GPSTEST_DATA:									/*GPS��������*/
					this->OnGPSTestData(buf + curPos, sizeof(GPSTestData) + INSTRUCTION_LENGTH);
					curPos += (sizeof(GPSTestData) + INSTRUCTION_LENGTH);
					break;
				default:
					ParseError(V);
					break;
				}
				break;
			case SOT_OPTTRACE_TST:					/*��ѧ׷��ϵͳ����*/
				switch(T)
				{
				case TOT_OPTTRACETEST_START:							/*��ʼ��ѧ׷��ϵͳ����*/
					this->OnOPTTTestStart(buf + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TOT_OPTTRACETEST_STOP:								/*������ѧ׷��ϵͳ����*/
					this->OnOPTTTestStop(buf + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TOT_OPTTRACETEST_DATA:								/*��ѧ׷��ϵͳ��������*/
					this->OnOPTTTestData(buf + curPos, sizeof(OPTTRACETestData) + INSTRUCTION_LENGTH);
					curPos += (sizeof(OPTTRACETestData) + INSTRUCTION_LENGTH);
					break; 
				default:
					ParseError(V);
					break;
				}
				break;
			case SAT_ALTIMETER_TST:					/*�߶ȼƲ���*/
				switch(T)
				{
				case TAT_ALTIMETERTEST_START:							/*��ʼ�߶ȼƲ���*/
					this->OnAltiTestStart(buf + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TAT_ALTIMETERTEST_STOP:							/*�����߶ȼƲ���*/
					this->OnAltiTestStop(buf + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TAT_ALTIMETERTEST_DATA:							/*��ѧ�߶ȼƲ�������*/
					this->OnAltiTestData(buf + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
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
		case FNT_NETTESTTEXT:		/*����ͨ�Ų��Դ��ı�*/
			this->OnComTestT(buf + curPos, COM_TEXT_LENGTH + INSTRUCTION_LENGTH);
			curPos += (COM_TEXT_LENGTH + INSTRUCTION_LENGTH);
			break;
		case FNT_NETTESTTEXTREPLY:	/*����ͨ�Ų��Դ��ı��ظ�*/
			this->OnComTestTReply(buf + curPos, COM_TEXT_LENGTH + INSTRUCTION_LENGTH);
			curPos += (COM_TEXT_LENGTH + INSTRUCTION_LENGTH);
			break;
		default :					/*�޶���*/
			ParseError(V);
		}
	} // end while loop

	// Release memory
	delete[] Target;
	return TRUE;
}