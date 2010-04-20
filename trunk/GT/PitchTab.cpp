// CPitchTab.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "PitchTab.h"


// CPitchTab 对话框

IMPLEMENT_DYNAMIC(CPitchTab, CTabPageSSL)

CPitchTab::CPitchTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CPitchTab::IDD, pParent)
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

CPitchTab::~CPitchTab()
{
}

void CPitchTab::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
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


BEGIN_MESSAGE_MAP(CPitchTab, CTabPageSSL)
	ON_BN_CLICKED(IDC_PITCH_PWM_BUTTON1, &CPitchTab::OnBnClickedPitchPWMButton1)
	ON_BN_CLICKED(IDC_PITCH_PWM_BUTTON2, &CPitchTab::OnBnClickedPitchPWMButton2)
	ON_BN_CLICKED(IDC_PITCH_PWM_BUTTON3, &CPitchTab::OnBnClickedPitchPWMButton3)
	ON_BN_CLICKED(IDC_PITCH_PWM_BUTTON4, &CPitchTab::OnBnClickedPitchPWMButton4)
	ON_BN_CLICKED(IDC_PITCH_PWM_BUTTON5, &CPitchTab::OnBnClickedPitchPWMButton5)
	ON_BN_CLICKED(IDC_PITCH_ANGLE_BUTTON1, &CPitchTab::OnBnClickedPitchAngleButton1)
	ON_BN_CLICKED(IDC_PITCH_ANGLE_BUTTON2, &CPitchTab::OnBnClickedPitchAngleButton2)
	ON_BN_CLICKED(IDC_PITCH_ANGLE_BUTTON3, &CPitchTab::OnBnClickedPitchAngleButton3)
	ON_BN_CLICKED(IDC_PITCH_ANGLE_BUTTON4, &CPitchTab::OnBnClickedPitchAngleButton4)
	ON_BN_CLICKED(IDC_PITCH_ANGLE_BUTTON5, &CPitchTab::OnBnClickedPitchAngleButton5)
END_MESSAGE_MAP()


// CPitchTab 消息处理程序

void CPitchTab::OnBnClickedPitchPWMButton1()
{
	this->UpdateData(TRUE);
	sendTestData(pitchPWM1);	
}

void CPitchTab::OnBnClickedPitchPWMButton2()
{
	this->UpdateData(TRUE);
	sendTestData(pitchPWM2);
}

void CPitchTab::OnBnClickedPitchPWMButton3()
{
	this->UpdateData(TRUE);
	sendTestData(pitchPWM3);
}

void CPitchTab::OnBnClickedPitchPWMButton4()
{
	this->UpdateData(TRUE);
	sendTestData(pitchPWM4);
}

void CPitchTab::OnBnClickedPitchPWMButton5()
{
	this->UpdateData(TRUE);
	sendTestData(pitchPWM5);
}

void CPitchTab::OnBnClickedPitchAngleButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CPitchTab::OnBnClickedPitchAngleButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CPitchTab::OnBnClickedPitchAngleButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CPitchTab::OnBnClickedPitchAngleButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CPitchTab::OnBnClickedPitchAngleButton5()
{
	// TODO: 在此添加控件通知处理程序代码
}

__int8 CPitchTab::getActorSerial(void)
{
	return 2;
}
