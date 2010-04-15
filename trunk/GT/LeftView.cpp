// LeftView.cpp : 实现文件
//

#include "stdafx.h"
#include <fstream>
#include "GT.h"
#include "LeftView.h"
#include "GTDoc.h"
#include "GlobalExperimentData.h"


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CFormView)

CLeftView::CLeftView()
	: CFormView(CLeftView::IDD)
	, feHour(0)
	, feMinute(0)
	, feSecond(0)
	, feRoll(0)
	, feRollUpper(0)
	, feRollLower(0)
	, fePitch(0)
	, fePitchUpper(0)
	, fePitchLower(0)
	, feHead(0)
	, feHeadUpper(0)
	, feHeadLower(0)
	, feFileName(_T(""))
{

}

CLeftView::~CLeftView()
{
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
	if (!GlobalExperimentData::isCommunicationTestPass ||
		!GlobalExperimentData::isControlParameterSet || 
		!GlobalExperimentData::isFlightPathSet ||
		!GlobalExperimentData::isIMUTestPass ||
		!GlobalExperimentData::isServoActorDemarcated) 
		return;

	/***** Then need to send the helicopter model to the server *****/
	if (!GlobalExperimentData::std) {
		// Then we need to read the servo actor configuration files
		std::ifstream ifs("", std::ios::binary);
	}

	/***** Then need to send all the servo actor demarcated data to the server *****/
	
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();

	char servoData[162];
	__int16 *c = (__int16 *)servoData;
	c[0] = TAS_ACTORSET;
	
	//memcpy(servoData + 2, );
	

	/***** Finally send a command to the server *****/
	char command[2];
	__int16 *c1 = (__int16 *)command;
	c1[0] = TFT_STARTTASK;
	
	
	cln->SendSvr(command, sizeof(command));

}

void CLeftView::OnBnClickedFEStop()
{
	char command[2];
	__int16 *c = (__int16 *)command;
	c[0] = TFT_STARTSTOP;

	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	cln->SendSvr(command, sizeof(command));

	
}
