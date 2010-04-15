// CollectiveTab.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "CollectiveTab.h"

#include "func\NetCln.h"
#include "func\NetSvrHeli.h"
#include "MsgType.h"
#include "GlobalExperimentData.h"


// CCollectiveTab 对话框

//IMPLEMENT_DYNAMIC(CCollectiveTab, CTabPageSSL)

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

//CCollectiveTab::~CCollectiveTab()
//{
//}

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


// CCollectiveTab 消息处理程序

void CCollectiveTab::OnBnClickedCollectivePWMButton1()
{
	this->UpdateData();
	sendTestData(collectivePWM1);
	
}

void CCollectiveTab::OnBnClickedCollectivePWMButton2()
{
	this->UpdateData();
	sendTestData(collectivePWM2);	
	
}

void CCollectiveTab::OnBnClickedCollectivePWMButton3()
{
	this->UpdateData();
	sendTestData(collectivePWM3);
}

void CCollectiveTab::OnBnClickedCollectivePWMButton4()
{
	this->UpdateData();
	sendTestData(collectivePWM4);	
}

void CCollectiveTab::OnBnClickedCollectivePWMButton5()
{
	this->UpdateData();
	sendTestData(collectivePWM5);	
}

void CCollectiveTab::OnBnClickedCollectiveAngleButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CCollectiveTab::OnBnClickedCollectiveAngleButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CCollectiveTab::OnBnClickedCollectiveAngleButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CCollectiveTab::OnBnClickedCollectiveAngleButton4()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CCollectiveTab::OnBnClickedCollectiveAngleButton5()
{
	// TODO: 在此添加控件通知处理程序代码
}

__int8 CCollectiveTab::getActorSerial(void)
{
	return 0;
}