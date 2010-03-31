#pragma once
#include "TabPageSSL.h"

// RollTab �Ի���

class RollTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(RollTab)

public:
	RollTab(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RollTab();

// �Ի�������
	enum { IDD = IDD_ROLL_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double rollPWM1;
	double rollPWM2;
	double rollPWM3;
	double rollPWM4;
	double rollPWM5;
	double rollAngle1;
	double rollAngle2;
	double rollAngle3;
	double rollAngle4;
	double rollAngle5;
	afx_msg void OnBnClickedRollPWMButton1();
	afx_msg void OnBnClickedRollPWMButton2();
	afx_msg void OnBnClickedRollPWMButton3();
	afx_msg void OnBnClickedRollPWMButton4();
	afx_msg void OnBnClickedRollPWMButton5();
	afx_msg void OnBnClickedRollAngleButton1();
	afx_msg void OnBnClickedRollAngleButton2();
	afx_msg void OnBnClickedRollAngleButton3();
	afx_msg void OnBnClickedRollAngleButton4();
	afx_msg void OnBnClickedRollAngleButton5();
};
