// CTailTab.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "TailTab.h"


// CTailTab 对话框

IMPLEMENT_DYNAMIC(CTailTab, CTabPageSSL)

CTailTab::CTailTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CTailTab::IDD, pParent)
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

CTailTab::~CTailTab()
{
}

void CTailTab::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
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


BEGIN_MESSAGE_MAP(CTailTab, CTabPageSSL)
	ON_BN_CLICKED(IDC_TAIL_PWM_BUTTON1, &CTailTab::OnBnClickedTailPWMButton1)
	ON_BN_CLICKED(IDC_TAIL_PWM_BUTTON2, &CTailTab::OnBnClickedTailPWMButton2)
	ON_BN_CLICKED(IDC_TAIL_PWM_BUTTON3, &CTailTab::OnBnClickedTailPWMButton3)
	ON_BN_CLICKED(IDC_TAIL_PWM_BUTTON4, &CTailTab::OnBnClickedTailPWMButton4)
	ON_BN_CLICKED(IDC_TAIL_PWM_BUTTON5, &CTailTab::OnBnClickedTailPWMButton5)
	ON_BN_CLICKED(IDC_TAIL_ANGLE_BUTTON1, &CTailTab::OnBnClickedTailAngleButton1)
	ON_BN_CLICKED(IDC_TAIL_ANGLE_BUTTON2, &CTailTab::OnBnClickedTailAngleButton2)
	ON_BN_CLICKED(IDC_TAIL_ANGLE_BUTTON3, &CTailTab::OnBnClickedTailAngleButton3)
	ON_BN_CLICKED(IDC_TAIL_ANGLE_BUTTON4, &CTailTab::OnBnClickedTailAngleButton4)
	ON_BN_CLICKED(IDC_TAIL_ANGLE_BUTTON5, &CTailTab::OnBnClickedTailAngleButton5)
END_MESSAGE_MAP()


// CTailTab 消息处理程序

void CTailTab::OnBnClickedTailPWMButton1()
{
	this->UpdateData(TRUE);
	sendTestData(tailPWM1);
}

void CTailTab::OnBnClickedTailPWMButton2()
{
	this->UpdateData(TRUE);
	sendTestData(tailPWM2);
}

void CTailTab::OnBnClickedTailPWMButton3()
{
	this->UpdateData(TRUE);
	sendTestData(tailPWM3);
}

void CTailTab::OnBnClickedTailPWMButton4()
{
	this->UpdateData(TRUE);
	sendTestData(tailPWM4);
}

void CTailTab::OnBnClickedTailPWMButton5()
{
	this->UpdateData(TRUE);
	sendTestData(tailPWM5);
}

void CTailTab::OnBnClickedTailAngleButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CTailTab::OnBnClickedTailAngleButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CTailTab::OnBnClickedTailAngleButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CTailTab::OnBnClickedTailAngleButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CTailTab::OnBnClickedTailAngleButton5()
{
	// TODO: 在此添加控件通知处理程序代码
}

__int8 CTailTab::getActorSerial(void)
{
	return 3;
}

void CTailTab::Initialize(float *pwm, float *angle)
{
	if (!pwm || !angle)
		return;
	
	CString str;
	CEdit* m_pEdit;
	tailPWM1 = (double)pwm[0];
	str.Format("%.4g", pwm[0]);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_TAIL_PWM_EDIT1));
	m_pEdit->SetWindowText(str);

	tailPWM2 = (double)pwm[1];
	str.Format("%.4g", pwm[1]);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_TAIL_PWM_EDIT2));
	m_pEdit->SetWindowText(str);

	tailPWM3 = (double)pwm[2];
	str.Format("%.4g", pwm[2]);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_TAIL_PWM_EDIT3));
	m_pEdit->SetWindowText(str);

	tailPWM4 = (double)pwm[3];
	str.Format("%.4g", pwm[3]);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_TAIL_PWM_EDIT4));
	m_pEdit->SetWindowText(str);

	tailPWM5 = (double)pwm[4];
	str.Format("%.4g", pwm[4]);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_TAIL_PWM_EDIT5));
	m_pEdit->SetWindowText(str);

	tailAngle1 = angle[0] / PI * 180.0f;
	str.Format("%.4g", tailAngle1);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_TAIL_ANGLE_EDIT1));
	m_pEdit->SetWindowText(str);

	tailAngle2 = angle[1] / PI * 180.0f;
	str.Format("%.4g", tailAngle2);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_TAIL_ANGLE_EDIT2));
	m_pEdit->SetWindowText(str);

	tailAngle3 = angle[2] / PI * 180.0f;
	str.Format("%.4g", tailAngle3);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_TAIL_ANGLE_EDIT3));
	m_pEdit->SetWindowText(str);

	tailAngle4 = angle[3] / PI * 180.0f;
	str.Format("%.4g", tailAngle4);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_TAIL_ANGLE_EDIT4));
	m_pEdit->SetWindowText(str);

	tailAngle5 = angle[4] / PI * 180.0f;
	str.Format("%.4g", tailAngle5);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_TAIL_ANGLE_EDIT5));
	m_pEdit->SetWindowText(str);

}