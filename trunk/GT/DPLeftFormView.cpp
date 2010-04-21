// DPLeftFormView.cpp : 实现文件
//

#include "stdafx.h"
#include <fstream>
#include "GT.h"
#include "DPLeftFormView.h"
#include "GTDoc.h"

// CDPLeftFormView

IMPLEMENT_DYNCREATE(CDPLeftFormView, CFormView)

CDPLeftFormView::CDPLeftFormView()
	: CFormView(CDPLeftFormView::IDD)
	, dpFileName(_T(""))
	, dpStartTime(0)
	, dpFPS(0)
	, dpHour(0)
	, dpMinute(0)
	, dpSecond(0)
	, dpRoll(0)
	, dpRollUpper(0)
	, dpRollLower(0)
	, dpPitch(0)
	, dpPitchUpper(0)
	, dpPitchLower(0)
	, dpHead(0)
	, dpHeadUpper(0)
	, dpHeadLower(0)
{

}

CDPLeftFormView::~CDPLeftFormView()
{
}

void CDPLeftFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DP_FILENAME_EDIT, dpFileName);
	DDX_Text(pDX, IDC_DP_STARTTIME_EDIT, dpStartTime);
	DDX_Text(pDX, IDC_DP_FPS_EDIT, dpFPS);
	DDX_Text(pDX, IDC_DP_HOUR_EDIT, dpHour);
	DDX_Text(pDX, IDC_DP_MINUTE_EDIT, dpMinute);
	DDX_Text(pDX, IDC_DP_SECOND_EDIT, dpSecond);
	DDX_Text(pDX, IDC_DP_ROLL_EDIT, dpRoll);
	DDX_Text(pDX, IDC_DP_ROLL_UPPER_EDIT, dpRollUpper);
	DDX_Text(pDX, IDC_DP_ROLL_LOWER_EDIT, dpRollLower);
	DDX_Text(pDX, IDC_DP_PITCH_EDIT, dpPitch);
	DDX_Text(pDX, IDC_DP_PITCH_UPPER_EDIT, dpPitchUpper);
	DDX_Text(pDX, IDC_DP_PITCH_LOWER_EDIT, dpPitchLower);
	DDX_Text(pDX, IDC_DP_HEAD_EDIT, dpHead);
	DDX_Text(pDX, IDC_DP_HEAD_UPPER_EDIT, dpHeadUpper);
	DDX_Text(pDX, IDC_DP_HEAD_LOWER_EDIT, dpHeadLower);
}

BEGIN_MESSAGE_MAP(CDPLeftFormView, CFormView)
	ON_BN_CLICKED(IDC_DP_START, &CDPLeftFormView::OnBnClickedDPStart)
	ON_BN_CLICKED(IDC_DP_PAUSE, &CDPLeftFormView::OnBnClickedDPPause)
	ON_BN_CLICKED(IDC_DP_STOP, &CDPLeftFormView::OnBnClickedDPStop)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CDPLeftFormView 诊断

#ifdef _DEBUG
void CDPLeftFormView::AssertValid() const
{
	CFormView::AssertValid();
}

CGTDoc* CDPLeftFormView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGTDoc)));
	return (CGTDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CDPLeftFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDPLeftFormView 消息处理程序

void CDPLeftFormView::OnBnClickedDPStart()
{
	/*
	 * Here we only need to read the fly state file
	 */
	std::ifstream ifs(".fs", std::ios::binary);

	ifs.close();

}

void CDPLeftFormView::OnBnClickedDPPause()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDPLeftFormView::OnBnClickedDPStop()
{
	// TODO: 在此添加控件通知处理程序代码
}

int CDPLeftFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	GetDocument()->dpLeftView = this;

	return 0;
}
