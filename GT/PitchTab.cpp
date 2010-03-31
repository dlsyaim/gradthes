// PitchTab.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "PitchTab.h"


// PitchTab 对话框

IMPLEMENT_DYNAMIC(PitchTab, CTabPageSSL)

PitchTab::PitchTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(PitchTab::IDD, pParent)
	, pitchPWM1(0)
	, pitchPWM2(0)
	, pitchPWM3(0)
	, pitchPWM4(0)
	, pitchPWM5(0)
	, pitchAngle1(0)
	, pitchAngle2(0)
	, pitchAngle3(0)
	, pitchAngle4(0)
	, pitchAngle5(0)
{

}

PitchTab::~PitchTab()
{
}

void PitchTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PITCH_PWM_EDIT1, pitchPWM1);
	DDX_Text(pDX, IDC_PITCH_PWM_EDIT2, pitchPWM2);
	DDX_Text(pDX, IDC_PITCH_PWM_EDIT3, pitchPWM3);
	DDX_Text(pDX, IDC_PITCH_PWM_EDIT4, pitchPWM4);
	DDX_Text(pDX, IDC_PITCH_PWM_EDIT5, pitchPWM5);
	DDX_Text(pDX, IDC_PITCH_ANGLE_EDIT1, pitchAngle1);
	DDX_Text(pDX, IDC_PITCH_ANGLE_EDIT2, pitchAngle2);
	DDX_Text(pDX, IDC_PITCH_ANGLE_EDIT3, pitchAngle3);
	DDX_Text(pDX, IDC_PITCH_ANGLE_EDIT4, pitchAngle4);
	DDX_Text(pDX, IDC_PITCH_ANGLE_EDIT5, pitchAngle5);
}


BEGIN_MESSAGE_MAP(PitchTab, CTabPageSSL)
	ON_BN_CLICKED(IDC_PITCH_PWM_BUTTON1, &PitchTab::OnBnClickedPitchPWMButton1)
	ON_BN_CLICKED(IDC_PITCH_PWM_BUTTON2, &PitchTab::OnBnClickedPitchPWMButton2)
	ON_BN_CLICKED(IDC_PITCH_PWM_BUTTON3, &PitchTab::OnBnClickedPitchPWMButton3)
	ON_BN_CLICKED(IDC_PITCH_PWM_BUTTON4, &PitchTab::OnBnClickedPitchPWMButton4)
	ON_BN_CLICKED(IDC_PITCH_PWM_BUTTON5, &PitchTab::OnBnClickedPitchPWMButton5)
	ON_BN_CLICKED(IDC_PITCH_ANGLE_BUTTON1, &PitchTab::OnBnClickedPitchAngleButton1)
	ON_BN_CLICKED(IDC_PITCH_ANGLE_BUTTON2, &PitchTab::OnBnClickedPitchAngleButton2)
	ON_BN_CLICKED(IDC_PITCH_ANGLE_BUTTON3, &PitchTab::OnBnClickedPitchAngleButton3)
	ON_BN_CLICKED(IDC_PITCH_ANGLE_BUTTON4, &PitchTab::OnBnClickedPitchAngleButton4)
	ON_BN_CLICKED(IDC_PITCH_ANGLE_BUTTON5, &PitchTab::OnBnClickedPitchAngleButton5)
END_MESSAGE_MAP()


// PitchTab 消息处理程序

void PitchTab::OnBnClickedPitchPWMButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void PitchTab::OnBnClickedPitchPWMButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void PitchTab::OnBnClickedPitchPWMButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void PitchTab::OnBnClickedPitchPWMButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}

void PitchTab::OnBnClickedPitchPWMButton5()
{
	// TODO: 在此添加控件通知处理程序代码
}

void PitchTab::OnBnClickedPitchAngleButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void PitchTab::OnBnClickedPitchAngleButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void PitchTab::OnBnClickedPitchAngleButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void PitchTab::OnBnClickedPitchAngleButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}

void PitchTab::OnBnClickedPitchAngleButton5()
{
	// TODO: 在此添加控件通知处理程序代码
}
