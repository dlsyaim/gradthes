#pragma once
#include "afxcmn.h"


// CDPLeftFormView 窗体视图
class CGTDoc;
class CCurveCtrl;

class CDPLeftFormView : public CFormView
{
	DECLARE_DYNCREATE(CDPLeftFormView)

protected:
	CDPLeftFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDPLeftFormView();

public:
	enum { IDD = IDD_DP_LEFT_FORMVIEW };

	enum PLAY_STATE{
		RUNNING,
		PAUSED,
		STOPED
	};
public:
	CGTDoc* GetDocument() const;
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString dpFileName;
	CString dpStartTime;
	int dpFPS;
	int dpHour;
	int dpMinute;
	int dpSecond;
	double dpRoll;
	double dpRollUpper;
	double dpRollLower;
	double dpPitch;
	double dpPitchUpper;
	double dpPitchLower;
	double dpHead;
	double dpHeadUpper;
	double dpHeadLower;

	// A slider control
	CSliderCtrl m_SliderCtrl;
	// The curve control pointer
	CCurveCtrl *m_pRollCurveCtrl, *m_pPitchCurveCtrl, *m_pHeadCurveCtrl;

	afx_msg void OnBnClickedDPStart();
	afx_msg void OnBnClickedDPPause();
	afx_msg void OnBnClickedDPStop();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedOpenEXPFileBTN();
private:
// Attributes
	std::vector<FlyStateGroup> buf;
	// The time of flight
	long tof;
	// The total size of FlyStateGroup
	int size;
	// A tag variable
	BOOL isRead;
	// Timer identifier
	int m_nTimer;
	// Current state
	PLAY_STATE curSta;
	// Current playing position
	int curPos;
	// Elapsed time
	long elapsed;
// Operations 
	void readFSFile(void);
	// Update the buf
	void updateBuf(void);
	// Restore the buf
	void restoreBuf(void);

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // debug version in DPLeftFormView.cpp
inline CGTDoc* CDPLeftFormView::GetDocument() const
   { return reinterpret_cast<CGTDoc*>(m_pDocument); }
#endif


