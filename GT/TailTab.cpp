// TailTab.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "TailTab.h"


// TailTab 对话框

IMPLEMENT_DYNAMIC(TailTab, CTabPageSSL)

TailTab::TailTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(TailTab::IDD, pParent)
	, tailPWM1(0)
	, tailPWM2(0)
	, tailPWM3(0)
	, tailPWM4(0)
	, tailPWM5(0)
	, tailAngle1(0)
	, tailAngle2(0)
	, tailAngle3(0)
	, tailAngle4(0)
	, tailAngle5(0)
{

}

TailTab::~TailTab()
{
}

void TailTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TAIL_PWM_EDIT1, tailPWM1);
	DDX_Text(pDX, IDC_TAIL_PWM_EDIT2, tailPWM2);
	DDX_Text(pDX, IDC_TAIL_PWM_EDIT3, tailPWM3);
	DDX_Text(pDX, IDC_TAIL_PWM_EDIT4, tailPWM4);
	DDX_Text(pDX, IDC_TAIL_PWM_EDIT5, tailPWM5);
	DDX_Text(pDX, IDC_TAIL_ANGLE_EDIT1, tailAngle1);
	DDX_Text(pDX, IDC_TAIL_ANGLE_EDIT2, tailAngle2);
	DDX_Text(pDX, IDC_TAIL_ANGLE_EDIT3, tailAngle3);
	DDX_Text(pDX, IDC_TAIL_ANGLE_EDIT4, tailAngle4);
	DDX_Text(pDX, IDC_TAIL_ANGLE_EDIT5, tailAngle5);
}


BEGIN_MESSAGE_MAP(TailTab, CTabPageSSL)
	ON_BN_CLICKED(IDC_TAIL_PWM_BUTTON1, &TailTab::OnBnClickedTailPWMButton1)
	ON_BN_CLICKED(IDC_TAIL_PWM_BUTTON2, &TailTab::OnBnClickedTailPWMButton2)
	ON_BN_CLICKED(IDC_TAIL_PWM_BUTTON3, &TailTab::OnBnClickedTailPWMButton3)
	ON_BN_CLICKED(IDC_TAIL_PWM_BUTTON4, &TailTab::OnBnClickedTailPWMButton4)
	ON_BN_CLICKED(IDC_TAIL_PWM_BUTTON5, &TailTab::OnBnClickedTailPWMButton5)
	ON_BN_CLICKED(IDC_TAIL_ANGLE_BUTTON1, &TailTab::OnBnClickedTailAngleButton1)
	ON_BN_CLICKED(IDC_TAIL_ANGLE_BUTTON2, &TailTab::OnBnClickedTailAngleButton2)
	ON_BN_CLICKED(IDC_TAIL_ANGLE_BUTTON3, &TailTab::OnBnClickedTailAngleButton3)
	ON_BN_CLICKED(IDC_TAIL_ANGLE_BUTTON4, &TailTab::OnBnClickedTailAngleButton4)
	ON_BN_CLICKED(IDC_TAIL_ANGLE_BUTTON5, &TailTab::OnBnClickedTailAngleButton5)
END_MESSAGE_MAP()


// TailTab 消息处理程序

void TailTab::OnBnClickedTailPWMButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void TailTab::OnBnClickedTailPWMButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void TailTab::OnBnClickedTailPWMButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void TailTab::OnBnClickedTailPWMButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}

void TailTab::OnBnClickedTailPWMButton5()
{
	// TODO: 在此添加控件通知处理程序代码
}

void TailTab::OnBnClickedTailAngleButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void TailTab::OnBnClickedTailAngleButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void TailTab::OnBnClickedTailAngleButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void TailTab::OnBnClickedTailAngleButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}

void TailTab::OnBnClickedTailAngleButton5()
{
	// TODO: 在此添加控件通知处理程序代码
}
