#pragma once



// CDPLeftFormView 窗体视图
class CGTDoc;
class CDPLeftFormView : public CFormView
{
	DECLARE_DYNCREATE(CDPLeftFormView)

protected:
	CDPLeftFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDPLeftFormView();

public:
	enum { IDD = IDD_DP_LEFT_FORMVIEW };
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
	long dpStartTime;
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
	afx_msg void OnBnClickedDPStart();
	afx_msg void OnBnClickedDPPause();
	afx_msg void OnBnClickedDPStop();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in DPLeftFormView.cpp
inline CGTDoc* CDPLeftFormView::GetDocument() const
   { return reinterpret_cast<CGTDoc*>(m_pDocument); }
#endif


