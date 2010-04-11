#pragma once
#include "TabPageSSL.h"

// CPitchTab 对话框

class CPitchTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(CPitchTab)

public:
	CPitchTab(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPitchTab();

// 对话框数据
	enum { IDD = IDD_PITCH_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double pitchPWM1;
	double pitchPWM2;
	double pitchPWM3;
	double pitchPWM4;
	double pitchPWM5;
	double pitchAngle1;
	double pitchAngle2;
	double pitchAngle3;
	double pitchAngle4;
	double pitchAngle5;
	afx_msg void OnBnClickedPitchPWMButton1();
	afx_msg void OnBnClickedPitchPWMButton2();
	afx_msg void OnBnClickedPitchPWMButton3();
	afx_msg void OnBnClickedPitchPWMButton4();
	afx_msg void OnBnClickedPitchPWMButton5();
	afx_msg void OnBnClickedPitchAngleButton1();
	afx_msg void OnBnClickedPitchAngleButton2();
	afx_msg void OnBnClickedPitchAngleButton3();
	afx_msg void OnBnClickedPitchAngleButton4();
	afx_msg void OnBnClickedPitchAngleButton5();
protected:
	__int8 getActorSerial(void);
};
