// LeftView.cpp : 实现文件
//

#include "stdafx.h"
#include <fstream>
#include <math.h>
#include "GT.h"
#include "LeftView.h"
#include "GTDoc.h"
#include "Singleton.h"
#include "MsgType.h"
#include "CurveCtrl.h"

#define CURVE_WIDTH 280
#define CURVE_HEIGHT 110

#define FIRST_LEFT 9
#define FIRST_UPPER 85

#define LABEL_HEIGHT 40

#define MAX_NUMBER_POINTS 20 

#define PITCH_CURVE_NAME "pitch"
#define ROLL_CURVE_NAME "roll"
#define HEAD_CURVE_NAME "head"

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
}

CLeftView::~CLeftView()
{
	if (m_pRollCurveCtrl)
		delete m_pRollCurveCtrl;
	if (m_pPitchCurveCtrl)
		delete m_pPitchCurveCtrl;
	if (m_pHeadCurveCtrl)
		delete m_pHeadCurveCtrl;
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
	CString curveName;
	
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
	/***** Here we start flight experiment *****/
	
	/***** First check all the configuration *****/
	//CSingleton* instance = CSingleton::getInstance();
	//if (!instance->isReady()) {
	//	AfxMessageBox(_T("Some requirement not satisfied\n"), MB_OK | MB_ICONSTOP);
	//	return;
	//}

	///***** Gain the socket client *****/
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	//
	__int16* c;
	///***** Then need to send the helicopter parameter to the server *****/
	//if (instance->getCurPHM()) {
	//	char heliMod[100];
	//	c = (__int16 *)heliMod;
	//	c[0] = TPT_LOADHELIPARA;
	//	memcpy(heliMod + 2, (char*)(&instance->getCurPHM()->heliPara), sizeof(instance->getCurPHM()->heliPara));
	//	cln->SendSvr(heliMod, sizeof(heliMod));

	//	/***** Then need to send all the servo actor demarcated data to the server *****/
	//	char servoData[162];
	//	c = (__int16 *)servoData;
	//	c[0] = TAS_ACTORSET;
	//	memcpy(servoData + 2, (char *)(&instance->getCurPHM()->sad), sizeof(instance->getCurPHM()->sad));
	//	cln->SendSvr(servoData, sizeof(servoData));
	//}

	/***** Finally send a command to the server *****/
	char command[2];
	c = (__int16 *)command;
	c[0] = TFT_STARTTASK;
	cln->SendSvr(command, sizeof(command));
}

void CLeftView::OnBnClickedFEStop()
{
	char command[2];
	__int16 *c = (__int16 *)command;
	c[0] = TFT_STOPTASK;

	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	cln->SendSvr(command, sizeof(command));	
}


LRESULT CLeftView::OnStartTaskReply(WPARAM w, LPARAM l)
{
	if(*isStart) {
		AfxMessageBox(_T("Start task successfully"), MB_OK | MB_ICONSTOP);
	} else {
		AfxMessageBox(_T("Failed to start task"), MB_OK | MB_ICONSTOP);
	}
	return TRUE;
}

LRESULT CLeftView::OnStopTaskReply(WPARAM w, LPARAM l)
{
	if(*isStop) {
		AfxMessageBox(_T("Stop task successfully"), MB_OK | MB_ICONSTOP);
	} else {
		AfxMessageBox(_T("Failed to stop task"), MB_OK | MB_ICONSTOP);
	}
	return TRUE;
}


LRESULT CLeftView::OnFlyingStateData(WPARAM w, LPARAM l)
{
	/*
	 * First check the newest fly state
	 */
	if (!newestFS)
	{
		AfxMessageBox("No fly state", MB_OK | MB_ICONSTOP);
		return TRUE;
	}

	/* 
	 * Update the edit control
	 */
	fePitch = newestFS->theta;
	feRoll = newestFS->phi;
	feHead = newestFS->psi;

	/*
	 * Update the curve
	 */
	
	updateCurve();


	UpdateData(FALSE);

	return TRUE;
}

void CLeftView::updateCurve(void)
{
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
		 * So we need to update the vector
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
		 * So we need to update the vector
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
		 * So we need to update the vector
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
	for (iter = pitchCurveData.begin(); iter != pitchCurveData.end(); iter++) {		
		fY = *iter;
		m_pPitchCurveCtrl->AddData(PITCH_CURVE_NAME, fX, fY);
		fX += 0.1f;
	}
	/*for (float f = 0.0f; f < 6.28f; f += 0.1f)
	{
		fX = f;
		fY = 100.0 *  (sin(f));
		m_pPitchCurveCtrl->AddData(PITCH_CURVE_NAME, fX, fY);
	}*/

	m_pPitchCurveCtrl->Invalidate();

}