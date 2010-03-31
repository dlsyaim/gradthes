#pragma once
#include "TabPageSSL.h"

// PitchTab �Ի���

class PitchTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(PitchTab)

public:
	PitchTab(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PitchTab();

// �Ի�������
	enum { IDD = IDD_PITCH_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
};
