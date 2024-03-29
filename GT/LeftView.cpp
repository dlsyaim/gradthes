// LeftView.cpp : 实现文件
//

#include "stdafx.h"
#include <fstream>
#include <math.h>
#include <vector>
#include <GL/glut.h>
#include "CurveCtrl.h"
#include "GT.h"
#include "MainFrm.h"
#include "LeftView.h"
#include "GTView.h"
#include "GTDoc.h"
#include "Singleton.h"
#include "MsgType.h"
#include "UpperRightView.h"
#include "FlightExperimentController.h"

#define CURVE_WIDTH 280
#define CURVE_HEIGHT 110

#define FIRST_LEFT 9
#define FIRST_UPPER 85

#define LABEL_HEIGHT 40

#define MAX_NUMBER_POINTS 20 

#define PITCH_CURVE_NAME "pitch"
#define ROLL_CURVE_NAME "roll"
#define HEAD_CURVE_NAME "head"

#define MAX_BUFFER_NUM 1000

// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CFormView)

CLeftView::CLeftView()
	: CFormView(CLeftView::IDD)
	, feHour(0)
	, feMinute(0)
	, feSecond(0)
	, feRoll(0)
	, feRollUpper(10)
	, feRollLower(-10)
	, fePitch(0)
	, fePitchUpper(10)
	, fePitchLower(-10)
	, feHead(0)
	, feHeadUpper(180)
	, feHeadLower(-180)
	, feFileName(_T(""))
{
	m_pRollCurveCtrl = m_pPitchCurveCtrl = m_pHeadCurveCtrl = NULL;

	newestFSG = NULL;

	// Because the server says it starts from 1
	expect = 1;

	// The experiment data
	memset(&ed, 0, sizeof(ed));

	controller = new CFlightExperimentController();
}

CLeftView::~CLeftView()
{
	if (m_pRollCurveCtrl)
		delete m_pRollCurveCtrl;
	if (m_pPitchCurveCtrl)
		delete m_pPitchCurveCtrl;
	if (m_pHeadCurveCtrl)
		delete m_pHeadCurveCtrl;

	if (controller)
		delete controller;
}

void CLeftView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FE_HOUR_EDIT, feHour);
	DDX_Text(pDX, IDC_FE_MINUTE_EDIT, feMinute);
	DDX_Text(pDX, IDC_FE_SECOND_EDIT, feSecond);
	DDX_Text(pDX, IDC_FE_ROLL_EDIT, feRoll);
	DDX_Text(pDX, IDC_FE_ROLL_UPPER_EDIT, feRollUpper);
	DDX_Text(pDX, IDC_FE_ROLL_LOWER_EDIT, feRollLower);
	DDX_Text(pDX, IDC_FE_PITCH_EDIT, fePitch);
	DDX_Text(pDX, IDC_FE_PITCH_UPPER_EDIT, fePitchUpper);
	DDX_Text(pDX, IDC_FE_PITCH_LOWER_EDIT, fePitchLower);
	DDX_Text(pDX, IDC_FE_HEAD_EDIT, feHead);
	DDX_Text(pDX, IDC_FE_HEAD_UPPER_EDIT, feHeadUpper);
	DDX_Text(pDX, IDC_FE_HEAD_LOWER_EDIT, feHeadLower);
	DDX_Text(pDX, IDC_FILENAME_EDIT, feFileName);
}

BEGIN_MESSAGE_MAP(CLeftView, CFormView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_FE_START, &CLeftView::OnBnClickedFEStart)
	ON_BN_CLICKED(IDC_FE_STOP, &CLeftView::OnBnClickedFEStop)
	ON_MESSAGE(START_TASK_REPLY_MSG, &CLeftView::OnStartTaskReply)
	ON_MESSAGE(STOP_TASK_REPLY_MSG, &CLeftView::OnStopTaskReply)
	ON_MESSAGE(FLYING_STATE_DATA_MSG, &CLeftView::OnFlyingStateData)
END_MESSAGE_MAP()


// CLeftView 诊断

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CFormView::AssertValid();
}

CGTDoc* CLeftView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGTDoc)));
	return (CGTDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CLeftView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CLeftView 消息处理程序

int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	GetDocument()->leftView = this;
	
	m_pRollCurveCtrl = new CCurveCtrl;
	m_pRollCurveCtrl->Create(CRect(FIRST_LEFT, FIRST_UPPER, FIRST_LEFT + CURVE_WIDTH, FIRST_UPPER + CURVE_HEIGHT), this, 
		IDC_ROLL_CURVE_CONTROL);
	/*
	 * In method SetMargin, the CRect object's four coodinates don't have the actual meaning, they
	 * just represent the margin in LEFT/TOP/RIGHT/BOTTOM direction respectively
	 */
	m_pRollCurveCtrl->SetMargin(CRect(1, 1, 1, 1));
	// Add the curve
	int idx = m_pRollCurveCtrl->AddCurve(ROLL_CURVE_NAME, RGB(0, 0, 0));
	m_pRollCurveCtrl->GetCurve(idx)->ShowCurve();

	int anotherUpper = FIRST_UPPER + CURVE_HEIGHT + LABEL_HEIGHT;
	m_pPitchCurveCtrl = new CCurveCtrl;
	m_pPitchCurveCtrl->Create(CRect(FIRST_LEFT, anotherUpper, FIRST_LEFT + CURVE_WIDTH, anotherUpper + CURVE_HEIGHT), this, 
		IDC_PITCH_CURVE_CONTROL);
	/*
	 * In method SetMargin, the CRect object's four coodinates don't have the actual meaning, they
	 * just represent the margin in LEFT/TOP/RIGHT/BOTTOM direction respectively
	 */
	m_pPitchCurveCtrl->SetMargin(CRect(1, 1, 1, 1));
	idx = m_pPitchCurveCtrl->AddCurve(PITCH_CURVE_NAME, RGB(0, 0, 0));
	m_pPitchCurveCtrl->GetCurve(idx)->ShowCurve();

	anotherUpper = anotherUpper + CURVE_HEIGHT + LABEL_HEIGHT;
	m_pHeadCurveCtrl = new CCurveCtrl;
	m_pHeadCurveCtrl->Create(CRect(FIRST_LEFT, anotherUpper, FIRST_LEFT + CURVE_WIDTH, anotherUpper + CURVE_HEIGHT), this, 
		IDC_HEAD_CURVE_CONTROL);
	/*
	 * In method SetMargin, the CRect object's four coodinates don't have the actual meaning, they
	 * just represent the margin in LEFT/TOP/RIGHT/BOTTOM direction respectively
	 */
	m_pHeadCurveCtrl->SetMargin(CRect(1, 1, 1, 1));
	idx = m_pHeadCurveCtrl->AddCurve(HEAD_CURVE_NAME, RGB(0, 0, 0));
	m_pHeadCurveCtrl->GetCurve(idx)->ShowCurve();

	return 0;
}

BOOL CLeftView::OnEraseBkgnd(CDC* pDC)
{
	return CFormView::OnEraseBkgnd(pDC);
}

void CLeftView::OnBnClickedFEStart()
{
	startFlightExperiment();
}

void CLeftView::OnBnClickedFEStop()
{
	stopFlightExperiment();
}


LRESULT CLeftView::OnStartTaskReply(WPARAM w, LPARAM l)
{
	if(*isStart) {
		TRACE(_T("Start task successfully"));
	
		CSingleton* instance = CSingleton::getInstance();
		// Base file name
		static CString baseFileName = feFileName;
		static int version = -1;
		version++;
		CString verStr;
		if (version != 0) {
			verStr.Format("%d", version);		
			feFileName = baseFileName + verStr;
			UpdateData(FALSE);
		}

		// Get the start time
		startTime = CTime::GetCurrentTime();
		memcpy(ed.startTime, startTime.Format("%Y-%m-%d %H:%M:%S").GetBuffer(0), startTime.Format("%Y-%m-%d %H:%M:%S").GetLength());

	} else {
		AfxMessageBox(_T("Failed to start task"), MB_OK | MB_ICONSTOP);
	}
	return TRUE;
}

LRESULT CLeftView::OnStopTaskReply(WPARAM w, LPARAM l)
{
	if(*isStop) {
		CButton* startBtn = (CButton*)GetDlgItem(IDC_FE_START);
		startBtn->EnableWindow(FALSE);
	} else {
		AfxMessageBox(_T("Failed to stop task"), MB_OK | MB_ICONSTOP);
	}
	return TRUE;
}


LRESULT CLeftView::OnFlyingStateData(WPARAM w, LPARAM l)
{
	/*
	 * First check the newest fly state group
	 */
	if (!newestFSG)	{
		AfxMessageBox("No fly state group coming", MB_OK | MB_ICONSTOP);
		return TRUE;
	}

	// Get the client
	CNetCln *cln = ((CGTApp*)AfxGetApp())->getCln();

	/* 
	 * Check the serial number of the newest fly state group
	 */
	char com[6];
	__int16 *inst = (__int16 *)com;
	inst[0] = FIT_FLYINGSTATEDATAACT;

	__int32 *rpy = (__int32 *)(com + 2);
	if (newestFSG->serial == expect) {    // Make it
		rpy[0] = newestFSG->serial;

		cln->SendSvr(com, sizeof(com));

		expect++;
	} else {
		rpy[0] = expect - 1;
		cln->SendSvr(com, sizeof(com));
		return TRUE;
	}

	/*
	 * Update the edit control
	 */
	updateEditControl();
	
	// Then update the curve
	updateCurve();

	/*
	 * Update the instruments and the 3-d helicopter model
	 */
	GetDocument()->lowerRightView->updateFS(&(newestFSG->states[FLYSTATEGROUPNUMBER - 1]));

	/*
	 * Update the GPS
	 */
	GetDocument()->upperRightView->updateFS(&(newestFSG->states[FLYSTATEGROUPNUMBER - 1]));

	/*
	 * Finally we should store the fly state into files when the buffer is full
	 */
	serialize();
	return TRUE;
}

void CLeftView::updateEditControl(void)
{
	fePitch = newestFSG->states[FLYSTATEGROUPNUMBER - 1].theta / PI * 180.0f;
	feHead = newestFSG->states[FLYSTATEGROUPNUMBER - 1].psi / PI * 180.0f;
	feRoll = newestFSG->states[FLYSTATEGROUPNUMBER - 1].phi / PI * 180.0f;

	CEdit* m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_FE_PITCH_EDIT));
	CString buffer;
	buffer.Format("%.4g", fePitch);
	m_pEdit->SetWindowText(buffer);

	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_FE_ROLL_EDIT));
	buffer.Format("%.4g", feRoll);
	m_pEdit->SetWindowText(buffer);

	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_FE_HEAD_EDIT));
	buffer.Format("%.4g", feHead);
	m_pEdit->SetWindowText(buffer);
}

void CLeftView::updateCurve(void)
{
	// Get the upper and the lower 
	UpdateData(TRUE);
    
	/*
	 * Update the curve
	 */
	float fX, fY;

	if (fePitch <= fePitchLower)
		fY = (float)fePitchLower;
	else if (fePitch >= fePitchUpper)
		fY = (float)fePitchUpper;
	else 
		fY = (float)fePitch;

	if (pitchCurveData.size() == MAX_NUMBER_POINTS) {
		/*
		 * So update the internal vector
		 */
		pitchCurveData.erase(pitchCurveData.begin());
		pitchCurveData.push_back(fY);
	} else {
		pitchCurveData.push_back(fY);
	}

	if (feRoll <= feRollLower)
		fY = (float)feRollLower;
	else if (feRoll >= feRollUpper)
		fY = (float)feRollUpper;
	else 
		fY = (float)feRoll;

	if (rollCurveData.size() == MAX_NUMBER_POINTS) {
		/*
		 * So update the internal vector
		 */
		rollCurveData.erase(rollCurveData.begin());
		rollCurveData.push_back(fY);
	} else {
		rollCurveData.push_back(fY);
	}

	if (feHead <= feHeadLower)
		fY = (float)feHeadLower;
	else if (feHead >= feHeadUpper)
		fY = (float)feHeadUpper;
	else 
		fY = (float)feHead;

	if (headCurveData.size() == MAX_NUMBER_POINTS) {
		/*
		 * So update the internal vector
		 */
		headCurveData.erase(headCurveData.begin());
		headCurveData.push_back(fY);
	} else {
		headCurveData.push_back(fY);
	}
	
	/*
	 * After update the data, then should update the curve
	 */
	
	std::vector<float>::iterator iter;
	fX = 0.1f;
	// First clear the curve
	m_pPitchCurveCtrl->GetCurve(PITCH_CURVE_NAME)->Clear();
	for (iter = pitchCurveData.begin(); iter != pitchCurveData.end(); iter++) {		
		fY = *iter;
		m_pPitchCurveCtrl->AddData(PITCH_CURVE_NAME, fX, fY);
		fX += 0.1f;
	}
	if (pitchCurveData.size() < MAX_NUMBER_POINTS) {
		for (int i = pitchCurveData.size(); i < MAX_NUMBER_POINTS; i++) {
			fY = 0.0f;
			m_pPitchCurveCtrl->AddData(PITCH_CURVE_NAME, fX, fY);
			fX += 0.1f;
		}
	}

	
	fX = 0.1f;
	m_pRollCurveCtrl->GetCurve(ROLL_CURVE_NAME)->Clear();
	for (iter = rollCurveData.begin(); iter != rollCurveData.end(); iter++) {
		fY = *iter;
		m_pRollCurveCtrl->AddData(ROLL_CURVE_NAME, fX, fY);
		fX += 0.1f;
	}
	if (rollCurveData.size() < MAX_NUMBER_POINTS) {
		for (int i = rollCurveData.size(); i < MAX_NUMBER_POINTS; i++) {
			fY = 0.0f;
			m_pRollCurveCtrl->AddData(ROLL_CURVE_NAME, fX, fY);
			fX += 0.1f;
		}
	}

	fX = 0.1f;
	m_pHeadCurveCtrl->GetCurve(HEAD_CURVE_NAME)->Clear();
	for (iter = headCurveData.begin(); iter != headCurveData.end(); iter++) {
		fY = *iter;
		m_pHeadCurveCtrl->AddData(HEAD_CURVE_NAME, fX, fY);
		fX += 0.1f;
	}

	if (headCurveData.size() < MAX_NUMBER_POINTS) {
		for (int i = headCurveData.size(); i < MAX_NUMBER_POINTS; i++) {
			fY = 0.0f;
			m_pHeadCurveCtrl->AddData(HEAD_CURVE_NAME, fX, fY);
			fX += 0.1f;
		}
	}
	
	m_pPitchCurveCtrl->Invalidate();
	m_pRollCurveCtrl->Invalidate();
	m_pHeadCurveCtrl->Invalidate();
}

void CLeftView::serialize(BOOL isForce/* = FALSE*/)
{
	//static int count = 1;
	if (!isForce) {
		bufFSG.push_back(*newestFSG);

		CString fullFileName;
		fullFileName = feFileName + _T(".fs");

		if (bufFSG.size() == MAX_BUFFER_NUM) {
			//std::ofstream ofs(fullFileName, std::ios::binary || std::ios::app);
			//// Calculate the file size 
			//ofs.seekp(0, std::ios::end);
			//int endSize = ofs.tellp();
			//
			//std::vector<FlyStateGroup>::iterator iter;
			//for (iter = bufFSG.begin(); iter != bufFSG.end(); iter++) {
			//	ofs.write((char*) &(*iter), sizeof(*iter));
			//}
			//ofs.close();
			//if (count == 1) {
			controller->saveFlyDataFile(fullFileName, &bufFSG);
			/*	++count;
			} else {

			}*/
			bufFSG.clear();
		}	
	} else {
		CString fullFileName;
		fullFileName = feFileName + _T(".fs");

		//std::ofstream ofs(fullFileName, std::ios::binary || std::ios::app);
		//// Calculate the file size
		//ofs.seekp(0, std::ios::end);
		//int endSize = ofs.tellp();

		//std::vector<FlyStateGroup>::iterator iter;
		//for (iter = bufFSG.begin(); iter != bufFSG.end(); iter++) {
		//	ofs.write((char*) &(*iter), sizeof(*iter));
		//}
		controller->saveFlyDataFile(fullFileName, &bufFSG);

		/*
		 * And we must serialize ed into the file's header
		 */
		/*ofs.seekp(0, std::ios::beg);
		ofs.write((char *)&ed, sizeof(ed));
		ofs.close();*/
		controller->addFlyDataFileHeader(fullFileName, &ed);
		bufFSG.clear();
	}
}

void CLeftView::startFlightExperiment(void)
{
	((CMainFrame*)AfxGetMainWnd())->enableMenuItems(FALSE);
	/***** Here we start flight experiment *****/
	
	/***** First check all the configuration *****/
	CSingleton* instance = CSingleton::getInstance();
	if (!instance->isReady()) {
		AfxMessageBox(_T("Some requirement not satisfied\n"), MB_OK | MB_ICONSTOP);
		return;
	}
	
	UpdateData(TRUE);
	if (feFileName.GetLength() == 0) {
		AfxMessageBox(_T("Experiment file name required"), MB_OK | MB_ICONSTOP);
		return;
	}

	/***** Get the socket client *****/
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	
	__int16* c;	
	PHelicopterModel curPHM = instance->getCurPHM();
	if (curPHM) {
		/***** Firstly send the helicopter parameters to the server *****/
		char heliPara[sizeof(HelicopterPara) + 2];
		c = (__int16 *)heliPara;
		c[0] = TPT_LOADHELIPARA;
		memcpy(heliPara + 2, (char*)(&curPHM->heliPara), sizeof(curPHM->heliPara));
		cln->SendSvr(heliPara, sizeof(heliPara));

		/***** Secondly send the servo actor demarcated data to the server *****/
		char servoData[sizeof(ServoActorData) + 2];
		c = (__int16 *)servoData;
		c[0] = TAS_ACTORSET;
		memcpy(servoData + 2, (char *)(&curPHM->sad), sizeof(curPHM->sad));
		cln->SendSvr(servoData, sizeof(servoData));

		/***** Thirdly send the rotor actor demarcated data to the server *****/
		char rotorData[sizeof(TiltDiscData) + 2];
		c = (__int16 *)rotorData;
		c[0] = TTS_TILTDISCSET;
		memcpy(rotorData + 2, (char *)(&curPHM->tdd), sizeof(curPHM->tdd));
		cln->SendSvr(rotorData, sizeof(rotorData));

		/***** Finally send a start-command to the server *****/
		char startCommand[2];
		c = (__int16 *)startCommand;
		c[0] = TFT_STARTTASK;
		cln->SendSvr(startCommand, sizeof(startCommand));

		// Make the button unable 
		CButton* startBtn = (CButton*)GetDlgItem(IDC_FE_START);
		startBtn->EnableWindow(FALSE);
	}	
}

void CLeftView::stopFlightExperiment(void)
{
	char command[2];
	__int16 *c = (__int16 *)command;
	c[0] = TFT_STOPTASK;

	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	cln->SendSvr(command, sizeof(command));	

	// Update...
	endTime = CTime::GetCurrentTime();
		
	CTimeSpan tof = endTime - startTime;
	ed.tof = tof.GetTotalSeconds();
		
	// Force to serialize
	serialize(TRUE);

	((CMainFrame*)AfxGetMainWnd())->enableMenuItems(TRUE);

}