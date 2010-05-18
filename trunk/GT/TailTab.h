#pragma once
#include "TabPageSSL.h"

// CTailTab 对话框

class CTailTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(CTailTab)

public:
	CTailTab(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTailTab();

// 对话框数据
	enum { IDD = IDD_TAIL_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double tailPWM1;
	double tailPWM2;
	double tailPWM3;
	double tailPWM4;
	double tailPWM5;
	double tailAngle1;
	double tailAngle2;
	double tailAngle3;
	double tailAngle4;
	double tailAngle5;
	afx_msg void OnBnClickedTailPWMButton1();
	afx_msg void OnBnClickedTailPWMButton2();
	afx_msg void OnBnClickedTailPWMButton3();
	afx_msg void OnBnClickedTailPWMButton4();
	afx_msg void OnBnClickedTailPWMButton5();
	afx_msg void OnBnClickedTailAngleButton1();
	afx_msg void OnBnClickedTailAngleButton2();
	afx_msg void OnBnClickedTailAngleButton3();
	afx_msg void OnBnClickedTailAngleButton4();
	afx_msg void OnBnClickedTailAngleButton5();

	void Initialize(float *pwm, float *angle);
private:
	__int8 getActorSerial(void);
};
