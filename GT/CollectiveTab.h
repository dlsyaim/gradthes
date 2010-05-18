#pragma once
#include "TabPageSSL.h"

// CCollectiveTab 对话框

class CCollectiveTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(CCollectiveTab)

public:
	CCollectiveTab(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCollectiveTab();

// 对话框数据
	enum { IDD = IDD_COLLECTIVE_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double collectivePWM1;
	double collectivePWM2;
	double collectivePWM3;
	double collectivePWM4;
	double collectivePWM5;
	double collectiveAngle1;
	double collectiveAngle2;
	double collectiveAngle3;
	double collectiveAngle4;
	double collectiveAngle5;
	afx_msg void OnBnClickedCollectivePWMButton1();
	afx_msg void OnBnClickedCollectivePWMButton2();
	afx_msg void OnBnClickedCollectivePWMButton3();
	afx_msg void OnBnClickedCollectivePWMButton4();
	afx_msg void OnBnClickedCollectivePWMButton5();
	afx_msg void OnBnClickedCollectiveAngleButton1();
	afx_msg void OnBnClickedCollectiveAngleButton2();
	afx_msg void OnBnClickedCollectiveAngleButton3();
	afx_msg void OnBnClickedCollectiveAngleButton4();
	afx_msg void OnBnClickedCollectiveAngleButton5();

	void Initialize(float* pwm, float* angle);
protected:
	__int8 getActorSerial(void);
};
