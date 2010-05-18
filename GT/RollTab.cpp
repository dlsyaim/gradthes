// CRollTab.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "RollTab.h"


// CRollTab 对话框

IMPLEMENT_DYNAMIC(CRollTab, CTabPageSSL)

CRollTab::CRollTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CRollTab::IDD, pParent)
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

CRollTab::~CRollTab()
{
}

void CRollTab::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
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


BEGIN_MESSAGE_MAP(CRollTab, CTabPageSSL)
	ON_BN_CLICKED(IDC_ROLL_PWM_BUTTON1, &CRollTab::OnBnClickedRollPWMButton1)
	ON_BN_CLICKED(IDC_ROLL_PWM_BUTTON2, &CRollTab::OnBnClickedRollPWMButton2)
	ON_BN_CLICKED(IDC_ROLL_PWM_BUTTON3, &CRollTab::OnBnClickedRollPWMButton3)
	ON_BN_CLICKED(IDC_ROLL_PWM_BUTTON4, &CRollTab::OnBnClickedRollPWMButton4)
	ON_BN_CLICKED(IDC_ROLL_PWM_BUTTON5, &CRollTab::OnBnClickedRollPWMButton5)
	ON_BN_CLICKED(IDC_ROLL_ANGLE_BUTTON1, &CRollTab::OnBnClickedRollAngleButton1)
	ON_BN_CLICKED(IDC_ROLL_ANGLE_BUTTON2, &CRollTab::OnBnClickedRollAngleButton2)
	ON_BN_CLICKED(IDC_ROLL_ANGLE_BUTTON3, &CRollTab::OnBnClickedRollAngleButton3)
	ON_BN_CLICKED(IDC_ROLL_ANGLE_BUTTON4, &CRollTab::OnBnClickedRollAngleButton4)
	ON_BN_CLICKED(IDC_ROLL_ANGLE_BUTTON5, &CRollTab::OnBnClickedRollAngleButton5)
END_MESSAGE_MAP()


// CRollTab 消息处理程序

void CRollTab::OnBnClickedRollPWMButton1()
{
	this->UpdateData(TRUE);
	sendTestData(rollPWM1);	
}

void CRollTab::OnBnClickedRollPWMButton2()
{
	this->UpdateData(TRUE);
	sendTestData(rollPWM2);	
}

void CRollTab::OnBnClickedRollPWMButton3()
{
	this->UpdateData(TRUE);
	sendTestData(rollPWM3);	
}

void CRollTab::OnBnClickedRollPWMButton4()
{
	this->UpdateData(TRUE);
	sendTestData(rollPWM4);	
}

void CRollTab::OnBnClickedRollPWMButton5()
{
	this->UpdateData(TRUE);
	sendTestData(rollPWM5);	
}

void CRollTab::OnBnClickedRollAngleButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CRollTab::OnBnClickedRollAngleButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CRollTab::OnBnClickedRollAngleButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CRollTab::OnBnClickedRollAngleButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CRollTab::OnBnClickedRollAngleButton5()
{
	// TODO: 在此添加控件通知处理程序代码
}

__int8 CRollTab::getActorSerial(void)
{
	return 0;
}

void CRollTab::Initialize(float *pwm, float *angle)
{
	if (!pwm || !angle)
		return;
	CString str;
	CEdit* m_pEdit;
	rollPWM1 = (double)pwm[0];
	str.Format("%.4g", pwm[0]);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_ROLL_PWM_EDIT1));
	m_pEdit->SetWindowText(str);

	rollPWM2 = (double)pwm[1];
	str.Format("%.4g", pwm[1]);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_ROLL_PWM_EDIT2));
	m_pEdit->SetWindowText(str);

	rollPWM3 = (double)pwm[2];
	str.Format("%.4g", pwm[2]);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_ROLL_PWM_EDIT3));
	m_pEdit->SetWindowText(str);

	rollPWM4 = (double)pwm[3];
	str.Format("%.4g", pwm[3]);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_ROLL_PWM_EDIT4));
	m_pEdit->SetWindowText(str);
	
	rollPWM5 = (double)pwm[4];
	str.Format("%.4g", pwm[4]);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_ROLL_PWM_EDIT5));
	m_pEdit->SetWindowText(str);

	rollAngle1 = angle[0] / PI * 180.0f;
	str.Format("%.4g", rollAngle1);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_ROLL_ANGLE_EDIT1));
	m_pEdit->SetWindowText(str);

	rollAngle2 = angle[1] / PI * 180.0f;
	str.Format("%.4g", rollAngle2);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_ROLL_ANGLE_EDIT2));
	m_pEdit->SetWindowText(str);


	rollAngle3 = angle[2] / PI * 180.0f;
	str.Format("%.4g", rollAngle3);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_ROLL_ANGLE_EDIT3));
	m_pEdit->SetWindowText(str);


	rollAngle4 = angle[3] / PI * 180.0f;
	str.Format("%.4g", rollAngle4);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_ROLL_ANGLE_EDIT4));
	m_pEdit->SetWindowText(str);


	rollAngle5 = angle[4] / PI * 180.0f;
	str.Format("%.4g", rollAngle5);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_ROLL_ANGLE_EDIT5));
	m_pEdit->SetWindowText(str);

}
