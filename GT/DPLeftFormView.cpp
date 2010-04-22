// DPLeftFormView.cpp : 实现文件
//

#include "stdafx.h"
#include <fstream>
#include <math.h>
#include <vector>
#include "GT.h"
#include "DPLeftFormView.h"
#include "GTDoc.h"
#include "CurveCtrl.h"
#include "GSDefinition.h"

// CDPLeftFormView

#define CURVE_WIDTH 280
#define CURVE_HEIGHT 110

#define FIRST_LEFT 9
#define FIRST_UPPER 130

#define LABEL_HEIGHT 50

#define MAX_NUMBER_POINTS 20 

#define PITCH_CURVE_NAME "dp_pitch"
#define ROLL_CURVE_NAME "dp_roll"
#define HEAD_CURVE_NAME "dp_head"

#define TIMER_IDENTIFIER_ONE 1

IMPLEMENT_DYNCREATE(CDPLeftFormView, CFormView)

CDPLeftFormView::CDPLeftFormView()
	: CFormView(CDPLeftFormView::IDD)
	, dpFileName(_T(""))
	, dpStartTime(_T(""))
	, dpFPS(20)
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
	m_pRollCurveCtrl = m_pPitchCurveCtrl = m_pHeadCurveCtrl = NULL;

	// Default is not read
	isRead = FALSE;

	// Default is stopped
	curSta = CDPLeftFormView::STOPED;

	// Default is 0
	curPos = 0;

	// Default is 0
	elapsed = 0;
}

CDPLeftFormView::~CDPLeftFormView()
{
	if (m_pRollCurveCtrl)
		delete m_pRollCurveCtrl;
	if (m_pPitchCurveCtrl)
		delete m_pPitchCurveCtrl;
	if (m_pHeadCurveCtrl)
		delete m_pHeadCurveCtrl;

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
	DDX_Control(pDX, IDC_DP_SLIDER, m_SliderCtrl);
}

BEGIN_MESSAGE_MAP(CDPLeftFormView, CFormView)
	ON_BN_CLICKED(IDC_DP_START, &CDPLeftFormView::OnBnClickedDPStart)
	ON_BN_CLICKED(IDC_DP_PAUSE, &CDPLeftFormView::OnBnClickedDPPause)
	ON_BN_CLICKED(IDC_DP_STOP, &CDPLeftFormView::OnBnClickedDPStop)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_OPEN_EXP_FILE_BTN, &CDPLeftFormView::OnBnClickedOpenEXPFileBTN)
	ON_WM_TIMER()
	ON_WM_DESTROY()
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
	 * Here we only need to read the FIRST fly state file
	 */
	this->UpdateData(TRUE);
	if (dpFileName.GetLength() == 0) {
		AfxMessageBox("Experiment file name required", MB_OK | MB_ICONINFORMATION);
		//return;
	} else if (!isRead) {
		readFSFile();
	}

	// Here we have already read the fly state from the files
	if (buf.size() == 0) {
		AfxMessageBox("No data", MB_OK | MB_ICONINFORMATION);
		//return;
	}

	m_SliderCtrl.SetRangeMin(0);
	m_SliderCtrl.SetRangeMax(3600);
	m_SliderCtrl.SetTicFreq(1);

	if (curSta == CDPLeftFormView::PAUSED || curSta == CDPLeftFormView::STOPED) {
		curSta = CDPLeftFormView::RUNNING;
		m_nTimer = SetTimer(TIMER_IDENTIFIER_ONE, dpFPS, 0);
	}

	//while (curSta == CDPLeftFormView::RUNNING && m_SliderCtrl.GetPos() < m_SliderCtrl.GetRangeMax()) {
	//	// The slider control is going
	//	m_SliderCtrl.SetPos(m_SliderCtrl.GetPos() + 1);

	//}
}

void CDPLeftFormView::OnBnClickedDPPause()
{
	if (curSta == CDPLeftFormView::RUNNING)
	{
		KillTimer(m_nTimer);
		curSta = CDPLeftFormView::PAUSED;
	}
}

void CDPLeftFormView::OnBnClickedDPStop()
{
	if (curSta == CDPLeftFormView::RUNNING)
		KillTimer(m_nTimer);
	curSta = CDPLeftFormView::STOPED;

	curPos = 0;

	restoreBuf();

	// The thumb must go back to start position
	m_SliderCtrl.SetPos(m_SliderCtrl.GetRangeMin());

	// Clear the elapsed
	elapsed = 0;
}

int CDPLeftFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	GetDocument()->dpLeftView = this;

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

void CDPLeftFormView::OnBnClickedOpenEXPFileBTN()
{
	char strFilter[] = {"Fly states(*.fs)|*.fs ||"};

	CFileDialog openDlg(TRUE, ".fs", NULL, 0, strFilter);

	if (openDlg.DoModal() == IDOK)
	{
		dpFileName = openDlg.GetFileName();
		readFSFile();
	}

	UpdateData(FALSE);

}


void CDPLeftFormView::readFSFile(void)
{
	isRead = TRUE;

	std::ifstream reserve(dpFileName, std::ios::binary);
	std::ifstream ifs;

	/*
	 * First, we must calculate the total number of FlyStateGroup
	 */

	ExperimentData ed;
	memset((char *)&ed, 0, sizeof(ed));
	reserve.read((char*)&ed, sizeof(ed));

	/* Gain the start time string and the tof */
	dpStartTime = ed.startTime;
	tof = ed.tof;

	// The total size of the fly state except for the experiment data
	reserve.seekg(0, std::ios::end);
	int totalSize = reserve.tellg();
	size = (totalSize - sizeof(ExperimentData)) / sizeof(FlyStateGroup);
	reserve.close();
	/*
	 * Loop to calculate the size
	 */
	while (ed.subExperimentData[0] != '\0') {
		reserve.open(ed.subExperimentData, std::ios::binary);
		reserve.read((char *)&ed, sizeof(ed));
		reserve.seekg(0, std::ios::end);
		totalSize = ifs.tellg();
		size += ((totalSize - sizeof(ExperimentData)) / sizeof(FlyStateGroup));
		reserve.close();
	}

	/*
	 * Then we start to read the first fly state file with the unit of the FlyStateGroup
	 */
	ifs.open(dpFileName, std::ios::binary);
	ifs.seekg(sizeof(ExperimentData), std::ios::beg);
	FlyStateGroup fsg;
	int bytesRead;
	while (TRUE) {
		ifs.read((char *)&fsg, sizeof(fsg));
		bytesRead = ifs.gcount();
		if (bytesRead != sizeof(fsg))
			break;
		buf.push_back(fsg);
	}
	ifs.close();
	
	m_SliderCtrl.SetRangeMin(0);
	m_SliderCtrl.SetRangeMax(tof);
	m_SliderCtrl.SetTicFreq(1);

	UpdateData(FALSE);
}


void CDPLeftFormView::OnTimer(UINT_PTR nIDEvent)
{
	// Update elapsed
	elapsed += dpFPS;
	// Calculate the seconds
	int seconds = elapsed / 60;

	m_SliderCtrl.SetPos(seconds);

	// We must get the data
	//curPos 

	CFormView::OnTimer(nIDEvent);
}


void CDPLeftFormView::updateBuf(void)
{

}

void CDPLeftFormView::restoreBuf(void)
{

}
void CDPLeftFormView::OnDestroy()
{
	CFormView::OnDestroy();

	// Any way, kill the timer
	KillTimer(m_nTimer);
}
