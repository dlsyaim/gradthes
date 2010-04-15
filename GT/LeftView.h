#pragma once



// CLeftView ������ͼ
class CGTDoc;
class CLeftView : public CFormView
{
	DECLARE_DYNCREATE(CLeftView)

protected:
	CLeftView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CLeftView();

public:
	enum { IDD = IDD_LEFT_FORMVIEW };
public:
	CGTDoc* GetDocument() const;
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	int feHour;
	int feMinute;
	int feSecond;
	double feRoll;
	double feRollUpper;
	double feRollLower;
	double fePitch;
	double fePitchUpper;
	double fePitchLower;
	double feHead;
	double feHeadUpper;
	double feHeadLower;
	CString feFileName;
	afx_msg void OnBnClickedFEStart();
	afx_msg void OnBnClickedFEStop();
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CGTDoc* CLeftView::GetDocument() const
   { return reinterpret_cast<CGTDoc*>(m_pDocument); }
#endif

