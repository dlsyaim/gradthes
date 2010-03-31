// RollTab.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "RollTab.h"


// RollTab 对话框

IMPLEMENT_DYNAMIC(RollTab, CTabPageSSL)

RollTab::RollTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(RollTab::IDD, pParent)
	, rollPWM1(0)
	, rollPWM2(0)
	, rollPWM3(0)
	, rollPWM4(0)
	, rollPWM5(0)
	, rollAngle1(0)
	, rollAngle2(0)
	, rollAngle3(0)
	, rollAngle4(0)
	, rollAngle5(0)
{

}

RollTab::~RollTab()
{
}

void RollTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ROLL_PWM_EDIT1, rollPWM1);
	DDX_Text(pDX, IDC_ROLL_PWM_EDIT2, rollPWM2);
	DDX_Text(pDX, IDC_ROLL_PWM_EDIT3, rollPWM3);
	DDX_Text(pDX, IDC_ROLL_PWM_EDIT4, rollPWM4);
	DDX_Text(pDX, IDC_ROLL_PWM_EDIT5, rollPWM5);
	DDX_Text(pDX, IDC_ROLL_ANGLE_EDIT1, rollAngle1);
	DDX_Text(pDX, IDC_ROLL_ANGLE_EDIT2, rollAngle2);
	DDX_Text(pDX, IDC_ROLL_ANGLE_EDIT3, rollAngle3);
	DDX_Text(pDX, IDC_ROLL_ANGLE_EDIT4, rollAngle4);
	DDX_Text(pDX, IDC_ROLL_ANGLE_EDIT5, rollAngle5);
}


BEGIN_MESSAGE_MAP(RollTab, CTabPageSSL)
	ON_BN_CLICKED(IDC_ROLL_PWM_BUTTON1, &RollTab::OnBnClickedRollPWMButton1)
	ON_BN_CLICKED(IDC_ROLL_PWM_BUTTON2, &RollTab::OnBnClickedRollPWMButton2)
	ON_BN_CLICKED(IDC_ROLL_PWM_BUTTON3, &RollTab::OnBnClickedRollPWMButton3)
	ON_BN_CLICKED(IDC_ROLL_PWM_BUTTON4, &RollTab::OnBnClickedRollPWMButton4)
	ON_BN_CLICKED(IDC_ROLL_PWM_BUTTON5, &RollTab::OnBnClickedRollPWMButton5)
	ON_BN_CLICKED(IDC_ROLL_ANGLE_BUTTON1, &RollTab::OnBnClickedRollAngleButton1)
	ON_BN_CLICKED(IDC_ROLL_ANGLE_BUTTON2, &RollTab::OnBnClickedRollAngleButton2)
	ON_BN_CLICKED(IDC_ROLL_ANGLE_BUTTON3, &RollTab::OnBnClickedRollAngleButton3)
	ON_BN_CLICKED(IDC_ROLL_ANGLE_BUTTON4, &RollTab::OnBnClickedRollAngleButton4)
	ON_BN_CLICKED(IDC_ROLL_ANGLE_BUTTON5, &RollTab::OnBnClickedRollAngleButton5)
END_MESSAGE_MAP()


// RollTab 消息处理程序

void RollTab::OnBnClickedRollPWMButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void RollTab::OnBnClickedRollPWMButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void RollTab::OnBnClickedRollPWMButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void RollTab::OnBnClickedRollPWMButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}

void RollTab::OnBnClickedRollPWMButton5()
{
	// TODO: 在此添加控件通知处理程序代码
}

void RollTab::OnBnClickedRollAngleButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void RollTab::OnBnClickedRollAngleButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void RollTab::OnBnClickedRollAngleButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void RollTab::OnBnClickedRollAngleButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}

void RollTab::OnBnClickedRollAngleButton5()
{
	// TODO: 在此添加控件通知处理程序代码
}
