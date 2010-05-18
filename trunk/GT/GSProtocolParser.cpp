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
	curPos = 0;

	isError = FALSE;
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
	} else if (!m_mainApp->getCtd()) {
		AfxMessageBox("No communication test");
	} else {
		m_mainApp->getCtd()->SendMessage(COMMUNICATION_TEST_REPLY_MSG, 0, 0);
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
	curPos = 0;
	
	/* If not casting, then Target can't be added */
	char *buf = (char *)tmpTarget;
	char *Target = new char[Len];
	memcpy(Target, buf, Len);

	isError = FALSE;
	while (curPos < (Len - 1) && !isError) {
		// Parse the instruction header
		INSHEAD *inshead = (INSHEAD *)(Target + curPos);
		INSHEAD V = *inshead;
		INSHEAD F = GetFirstIns(V);
		INSHEAD S = GetSecondIns(V);
		INSHEAD T = GetThirdIns(V);

		switch(F)
		{

		case FEM_EMERGENCY:
			this->OnEmergency(Target + curPos, 4);
			curPos += 4;
			break;
	//////////////////////////////////////////////////////////////////////
		case FCT_NETCOMTEST:
			this->OnComTest(Target + curPos, INSTRUCTION_LENGTH);
			curPos += INSTRUCTION_LENGTH;
			break;
	/////////////////////////////////////////////////////////////////////
		case FCT_NETCOMTESTREPLY:
			this->OnComTestReply(Target + curPos, INSTRUCTION_LENGTH);
			curPos += INSTRUCTION_LENGTH;
			break;
	/////////////////////////////////////////////////////////////////////
		case FOC_OPERATIONCOMMAND:
			switch(S)
			{
			case SFT_FLYING_TASK:
				switch(T)
				{
				case TFT_STARTTASK:
					this->OnStartTask(Target + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TFT_STARTTASKREPLY:
					this->OnStartTaskReply(Target + curPos, 6);
					curPos += 6;
					break;
				case TFT_STOPTASK:
					this->OnStopTask(Target + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TFT_STOPTASKREPLY:
					this->OnStopTaskReply(Target + curPos, 6);
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
	/////////////////////////////////////////////////////////////////////
		case FTS_TASK_SET:
			switch(S)
			{
			case TPT_LOADHELIPARA:
			{
				this->OnLoadHeliPara(Target + curPos, sizeof(HelicopterPara) + INSTRUCTION_LENGTH);
				curPos += sizeof(HelicopterPara) + INSTRUCTION_LENGTH;
				break;
			}
			case TPT_LOADCONTROLPARA:
			{
				this->OnLoadCtlPara(Target + curPos, sizeof(ControlPara) + INSTRUCTION_LENGTH);
				curPos += sizeof(ControlPara) + INSTRUCTION_LENGTH;
				break;
			}
			case SAS_ACTORSET_TASK:
				switch (T)
				{
				case TAS_ACTORSET:
					this->OnServoActorSet(Target + curPos, sizeof(ServoActorData) + INSTRUCTION_LENGTH);
					curPos += sizeof(ServoActorData) + INSTRUCTION_LENGTH;
					break;
				default:
					ParseError(V);
					break;
				}
				break;
			case STS_TILTDISCSET_TASK:
				switch (T)
				{
				case TTS_TILTDISCSET:
					this->OnTileDiscSet(Target + curPos, sizeof(TiltDiscData) + INSTRUCTION_LENGTH);
					curPos += sizeof(TiltDiscData) + INSTRUCTION_LENGTH;
					break;
				default:
					ParseError(V);
					break;
				}
				break;
			case SPT_PATH_TASK:
				switch (T)
				{
				case TPT_LOADPATHPOINT_START:
					this->OnLoadPathPointStart(Target + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TPT_LOADPATHPOINT_STOP:
					this->OnLoadPathPointStop(Target + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TPT_LOADPATHPOINTS:
					this->OnLoadPathPoint(Target + curPos, sizeof(PathPointData) + INSTRUCTION_LENGTH);
					curPos += sizeof(PathPointData) + INSTRUCTION_LENGTH;
					break;
				case TPT_LOADPATHPOINTS_REPLY:
					this->OnLoadPathPointSerial(Target + curPos, 6);
					curPos += 6;
					break;
				case TPT_LOADPATHPOINTS_CHECK:
					this->OnPathPointState(Target + curPos, 6);
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
	/////////////////////////////////////////////////////////////////////
		case FIT_FLYINGSTATEDATA:
			this->OnFlyingState(Target + curPos, sizeof(FlyStateGroup) + INSTRUCTION_LENGTH);
			curPos += sizeof(FlyStateGroup) + INSTRUCTION_LENGTH;
			break;
	/////////////////////////////////////////////////////////////////////
		case FIT_FLYINGSTATEDATAACT:
			this->OnFlyingStateAct(Target + curPos, 6);
			curPos += 6;
			break;
	/////////////////////////////////////////////////////////////////////
		case FIE_INSPARSEERR:
			this->OnErrorInsHead(Target + curPos, 4);
			curPos += 4;
			break;
	/////////////////////////////////////////////////////////////////////
		case FET_EQUIPMENTTEST:
			switch(S)
			{
			case SAT_SERVOACTOR_TST:
				this->OnServoActorTest(Target + curPos, sizeof(ServoActorTstInsData) + INSTRUCTION_LENGTH);
				curPos += sizeof(ServoActorTstInsData) + INSTRUCTION_LENGTH;
				break;
			case STT_THROTTLE_TST:
				this->OnThrottleTest(Target + curPos, sizeof(ThrottleTstInsData) + INSTRUCTION_LENGTH);
				curPos += sizeof(ThrottleTstInsData) + INSTRUCTION_LENGTH;
				break;
			case STT_TILTDISC_TST:
				this->OnTiltDiscTest(Target + curPos, sizeof(TiltDiscTstInsData) + INSTRUCTION_LENGTH);
				curPos += sizeof(TiltDiscTstInsData) + INSTRUCTION_LENGTH;
				break;
			case SIT_IMU_TST:
				switch(T)
				{
				case TIT_IMUTEST_START:
					this->OnIMUTestStart(Target + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TIT_IMUTEST_STOP:
					this->OnIMUTestStop(Target + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TIT_IMUTEST_DATA:
					this->OnIMUTestData(Target + curPos, INSTRUCTION_LENGTH + sizeof(IMUTestData));
					curPos += INSTRUCTION_LENGTH + sizeof(IMUTestData);
					break;
				default:
					ParseError(V);
					break;
				}
				break;
			case SGT_GPS_TST:
				switch(T)
				{
				case TGT_GPSTEST_START:
					this->OnGPSTestStart(Target + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TGT_GPSTEST_STOP:
					this->OnGPSTestStop(Target + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TGT_GPSTEST_DATA:
					this->OnGPSTestData(Target + curPos, INSTRUCTION_LENGTH + sizeof(GPSTestData));
					curPos += INSTRUCTION_LENGTH + sizeof(GPSTestData);
					break;
				default:
					ParseError(V);
					break;
				}
				break;
			case SOT_OPTTRACE_TST:
				switch(T)
				{
				case TOT_OPTTRACETEST_START:
					this->OnOPTTTestStart(Target + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TOT_OPTTRACETEST_STOP:
					this->OnOPTTTestStop(Target + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TOT_OPTTRACETEST_DATA:
					this->OnOPTTTestData(Target + curPos, INSTRUCTION_LENGTH + sizeof(OPTTRACETestData));
					curPos += INSTRUCTION_LENGTH + sizeof(OPTTRACETestData);
					break;
				default:
					ParseError(V);
					break;
				}
				break;
			case SAT_ALTIMETER_TST:
				switch(T)
				{
				case TAT_ALTIMETERTEST_START:
					this->OnAltiTestStart(Target + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TAT_ALTIMETERTEST_STOP:
					this->OnAltiTestStop(Target + curPos, INSTRUCTION_LENGTH);
					curPos += INSTRUCTION_LENGTH;
					break;
				case TAT_ALTIMETERTEST_DATA:
					this->OnAltiTestData(Target + curPos, INSTRUCTION_LENGTH);
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
	/////////////////////////////////////////////////////////////////////
		case FNT_NETTESTTEXT:
			this->OnComTestT(Target + curPos, COM_TEXT_LENGTH + INSTRUCTION_LENGTH);
			curPos += COM_TEXT_LENGTH + INSTRUCTION_LENGTH;
			break;
	/////////////////////////////////////////////////////////////////////
		case FNT_NETTESTTEXTREPLY:
			this->OnComTestTReply(Target + curPos, COM_TEXT_LENGTH + INSTRUCTION_LENGTH);
			curPos += COM_TEXT_LENGTH + INSTRUCTION_LENGTH;
			break;
	/////////////////////////////////////////////////////////////////////
		default :
			ParseError(V);
		}
	} // end while loop

	// Release memory
	delete[] Target;
	return TRUE;
}

void CGSProtocolParser::ParseError(INSHEAD V)
{
	isError = TRUE;
	::SendMessage(((CGTApp*)AfxGetApp())->GetMainWnd()->m_hWnd, ERROR_INSTRUCTION, 0, 0);
}