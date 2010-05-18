// CollectiveTab.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GT.h"
#include "CollectiveTab.h"
#include "func\NetCln.h"
#include "func\NetSvrHeli.h"
#include "MsgType.h"
#include "GlobalExperimentData.h"


// CCollectiveTab �Ի���

IMPLEMENT_DYNAMIC(CCollectiveTab, CTabPageSSL)

CCollectiveTab::CCollectiveTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CCollectiveTab::IDD, pParent)
	, collectivePWM1(0)
	, collectivePWM2(0)
	, collectivePWM3(0)
	, collectivePWM4(0)
	, collectivePWM5(0)
	, collectiveAngle1(0)
	, collectiveAngle2(0)
	, collectiveAngle3(0)
	, collectiveAngle4(0)
	, collectiveAngle5(0)
{

}

CCollectiveTab::~CCollectiveTab()
{
}

void CCollectiveTab::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COLLECTIVE_PWM_EDIT1, collectivePWM1);
	DDX_Text(pDX, IDC_COLLECTIVE_PWM_EDIT2, collectivePWM2);
	DDX_Text(pDX, IDC_COLLECTIVE_PWM_EDIT3, collectivePWM3);
	DDX_Text(pDX, IDC_COLLECTIVE_PWM_EDIT4, collectivePWM4);
	DDX_Text(pDX, IDC_COLLECTIVE_PWM_EDIT5, collectivePWM5);
	DDX_Text(pDX, IDC_COLLECTIVE_ANGLE_EDIT1, collectiveAngle1);
	DDX_Text(pDX, IDC_COLLECTIVE_ANGLE_EDIT2, collectiveAngle2);
	DDX_Text(pDX, IDC_COLLECTIVE_ANGLE_EDIT3, collectiveAngle3);
	DDX_Text(pDX, IDC_COLLECTIVE_ANGLE_EDIT4, collectiveAngle4);
	DDX_Text(pDX, IDC_COLLECTIVE_ANGLE_EDIT5, collectiveAngle5);
}


BEGIN_MESSAGE_MAP(CCollectiveTab, CTabPageSSL)
	ON_BN_CLICKED(IDC_COLLECTIVE_PWM_BUTTON1, &CCollectiveTab::OnBnClickedCollectivePWMButton1)
	ON_BN_CLICKED(IDC_COLLECTIVE_PWM_BUTTON2, &CCollectiveTab::OnBnClickedCollectivePWMButton2)
	ON_BN_CLICKED(IDC_COLLECTIVE_PWM_BUTTON3, &CCollectiveTab::OnBnClickedCollectivePWMButton3)
	ON_BN_CLICKED(IDC_COLLECTIVE_PWM_BUTTON4, &CCollectiveTab::OnBnClickedCollectivePWMButton4)
	ON_BN_CLICKED(IDC_COLLECTIVE_PWM_BUTTON5, &CCollectiveTab::OnBnClickedCollectivePWMButton5)
	ON_BN_CLICKED(IDC_COLLECTIVE_ANGLE_BUTTON1, &CCollectiveTab::OnBnClickedCollectiveAngleButton1)
	ON_BN_CLICKED(IDC_COLLECTIVE_ANGLE_BUTTON2, &CCollectiveTab::OnBnClickedCollectiveAngleButton2)
	ON_BN_CLICKED(IDC_COLLECTIVE_ANGLE_BUTTON3, &CCollectiveTab::OnBnClickedCollectiveAngleButton3)
	ON_BN_CLICKED(IDC_COLLECTIVE_ANGLE_BUTTON4, &CCollectiveTab::OnBnClickedCollectiveAngleButton4)
	ON_BN_CLICKED(IDC_COLLECTIVE_ANGLE_BUTTON5, &CCollectiveTab::OnBnClickedCollectiveAngleButton5)
END_MESSAGE_MAP()


// CCollectiveTab ��Ϣ�������

void CCollectiveTab::OnBnClickedCollectivePWMButton1()
{
	this->UpdateData(TRUE);
	sendTestData(collectivePWM1);
	
}

void CCollectiveTab::OnBnClickedCollectivePWMButton2()
{
	this->UpdateData(TRUE);
	sendTestData(collectivePWM2);	
	
}

void CCollectiveTab::OnBnClickedCollectivePWMButton3()
{
	this->UpdateData(TRUE);
	sendTestData(collectivePWM3);
}

void CCollectiveTab::OnBnClickedCollectivePWMButton4()
{
	this->UpdateData(TRUE);
	sendTestData(collectivePWM4);	
}

void CCollectiveTab::OnBnClickedCollectivePWMButton5()
{
	this->UpdateData(TRUE);
	sendTestData(collectivePWM5);	
}

void CCollectiveTab::OnBnClickedCollectiveAngleButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CCollectiveTab::OnBnClickedCollectiveAngleButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CCollectiveTab::OnBnClickedCollectiveAngleButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CCollectiveTab::OnBnClickedCollectiveAngleButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CCollectiveTab::OnBnClickedCollectiveAngleButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

__int8 CCollectiveTab::getActorSerial(void)
{
	return 2;
}

void CCollectiveTab::Initialize(float *pwm, float *angle)
{
	if (!pwm || !angle)
		return;
	// PWM value
	CString str;
	collectivePWM1 = (double)pwm[0];
	str.Format("%.4g", pwm[0]);
	CEdit* m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_COLLECTIVE_PWM_EDIT1)); 
	m_pEdit->SetWindowText(str);

	collectivePWM2 = (double)pwm[1];
	str.Format("%.4g", pwm[1]);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_COLLECTIVE_PWM_EDIT2)); 
	m_pEdit->SetWindowText(str);
	
	collectivePWM3 = (double)pwm[2];
	str.Format("%.4g", pwm[2]);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_COLLECTIVE_PWM_EDIT3));
	m_pEdit->SetWindowText(str);

	collectivePWM4 = (double)pwm[3];
	str.Format("%.4g", pwm[3]);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_COLLECTIVE_PWM_EDIT4));
	m_pEdit->SetWindowText(str);

	collectivePWM5 = (double)pwm[4];
	str.Format("%.4g", pwm[4]);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_COLLECTIVE_PWM_EDIT5));
	m_pEdit->SetWindowText(str);

	// Angle value
	collectiveAngle1 = angle[0] / PI * 180.0f;
	str.Format("%.4g", collectiveAngle1);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_COLLECTIVE_ANGLE_EDIT1)); 
	m_pEdit->SetWindowText(str);

	collectiveAngle2 = angle[1] / PI * 180.0f;
	str.Format("%.4g", collectiveAngle2);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_COLLECTIVE_ANGLE_EDIT2)); 
	m_pEdit->SetWindowText(str);
	
	collectiveAngle3 = angle[2] / PI * 180.0f;
	str.Format("%.4g", collectiveAngle3);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_COLLECTIVE_ANGLE_EDIT3)); 
	m_pEdit->SetWindowText(str);
	
	collectiveAngle4 = angle[3] / PI * 180.0f;
	str.Format("%.4g", collectiveAngle4);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_COLLECTIVE_ANGLE_EDIT4)); 
	m_pEdit->SetWindowText(str);
	
	collectiveAngle5 = angle[4] / PI * 180.0f;
	str.Format("%.4g", collectiveAngle5);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_COLLECTIVE_ANGLE_EDIT5)); 
	m_pEdit->SetWindowText(str);
}