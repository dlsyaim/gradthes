#pragma once



// COPTFormView 窗体视图
class CGTDoc;
class COPTFormView : public CFormView
{
	DECLARE_DYNCREATE(COPTFormView)

protected:
	COPTFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~COPTFormView();

public:
	enum { IDD = IDD_OPTTRACE_FORMVIEW };
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	double phi;
	double theta;
	double psi;
	double N_Speed;
	double E_Speed;
	double D_Speed;
	double N_Acc;
	double E_Acc;
	double D_Acc;
	afx_msg void OnBnClickedOPTTestStart();
	afx_msg void OnBnClickedOPTTestStop();
	afx_msg void OnBnClickedOPTTestPass();
	afx_msg void OnBnClickedOPTTestFailure();
	afx_msg LRESULT OnReplyMsgArrived(WPARAM w, LPARAM l);

	void updateData(pOPTTRACETestData d);
	double opt_n_coord;
	double opt_e_coord;
	double opt_d_coord;
	double opt_roll_vel;
	double opt_pitch_vel;
	double opt_head_vel;
};

#ifndef _DEBUG  // debug version in OPTFormView.cpp
inline CGTDoc* COPTFormView::GetDocument() const
   { return reinterpret_cast<CGTDoc*>(m_pDocument); }
#endif


