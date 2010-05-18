#pragma once
#include "func\NetCln.h"
// CIMUTestFormView 窗体视图

class CGTDoc;
class CIMUTestFormView : public CFormView
{
	DECLARE_DYNCREATE(CIMUTestFormView)

protected:
	CIMUTestFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CIMUTestFormView();

public:
	enum { IDD = IDD_IMU_TEST_FORMVIEW };
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
	afx_msg void OnBnClickedIMUTestStart();
	afx_msg void OnBnClickedIMUTestPass();
	afx_msg void OnBnClickedIMUTestStop();
	afx_msg void OnBnClickedIMUTestFailure();
	afx_msg LRESULT OnTestDataReply(WPARAM w, LPARAM l);
	void updateData(IMUTestData *itd);
// Attributes
	// The client point of the socket
	CNetCln netcln;
	double headingAngle;
	double pitchAngle;
	double rollAngle;
	double n_x_Vel;
	double e_y_Vel;
	double d_z_Vel;
	double n_x_Acc;
	double e_y_Acc;
	double d_z_Acc;
};

#ifndef _DEBUG  // debug version in IMUTestFormView.cpp
inline CGTDoc* CIMUTestFormView::GetDocument() const
   { return reinterpret_cast<CGTDoc*>(m_pDocument); }
#endif

