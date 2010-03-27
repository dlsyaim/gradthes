// HelicopterChoosingDialog.cpp : 实现文件
//

#include "stdafx.h"
#include <fstream>
#include "GT.h"
#include "MainFrm.h"
#include "HelicopterChoosingDialog.h"



// CHelicopterChoosingDialog 对话框

IMPLEMENT_DYNAMIC(CHelicopterChoosingDialog, CDialog)

CHelicopterChoosingDialog::CHelicopterChoosingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CHelicopterChoosingDialog::IDD, pParent)
	, aircraftName(_T(""))
	, aircraftMass(0.5)
	, mainBladeLength(0)
	, aircraftLength(0)
	, mainBladeRPM(0)
	, xInertia(0)
{

}

CHelicopterChoosingDialog::~CHelicopterChoosingDialog()
{
}

void CHelicopterChoosingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_AIRCRAFTNAME_EDIT, aircraftName);
	DDX_Text(pDX, IDC_AIRCRAFTMASS_EDIT, aircraftMass);
	DDX_Text(pDX, IDC_MAINBLADELENGHT_EDIT, mainBladeLength);
	DDX_Text(pDX, IDC_AIRCRAFTLENGHT_EDIT, aircraftLength);
	DDX_Text(pDX, IDC_MAINBLADERPM_EDIT, mainBladeRPM);
	DDX_Text(pDX, IDC_XINERTIA_EDIT, xInertia);
	DDV_MinMaxDouble(pDX, aircraftMass, 0.5, 1000);
}


BEGIN_MESSAGE_MAP(CHelicopterChoosingDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CHelicopterChoosingDialog::OnBnClickedOk)
	/*ON_EN_CHANGE(IDC_AIRCRAFTNAME_EDIT, &CHelicopterChoosingDialog::OnEnChangeAircraftnameEdit)
	ON_EN_CHANGE(IDC_AIRCRAFTMASS_EDIT, &CHelicopterChoosingDialog::OnEnChangeAircraftmassEdit)
	ON_EN_CHANGE(IDC_AIRCRAFTLENGHT_EDIT, &CHelicopterChoosingDialog::OnEnChangeAircraftlenghtEdit)
	ON_EN_CHANGE(IDC_MAINBLADELENGHT_EDIT, &CHelicopterChoosingDialog::OnEnChangeMainbladelenghtEdit)
	ON_EN_CHANGE(IDC_MAINBLADERPM_EDIT, &CHelicopterChoosingDialog::OnEnChangeMainbladerpmEdit)
	ON_EN_CHANGE(IDC_XINERTIA_EDIT, &CHelicopterChoosingDialog::OnEnChangeXinertiaEdit)*/
END_MESSAGE_MAP()


// CHelicopterChoosingDialog 消息处理程序

void CHelicopterChoosingDialog::OnBnClickedOk()
{
	// TODO: 
	//UpdateData(TRUE);
	this->UpdateData();
	// Construct a flight model
	// ...
	// Then use ofstream to store the flightmodel into files.
	CDialog::OnOK();
}

//void CHelicopterChoosingDialog::OnEnChangeAircraftnameEdit()
//{
//	//UpdateData(TRUE);
//}
//
//void CHelicopterChoosingDialog::OnEnChangeAircraftmassEdit()
//{
//	//UpdateData(TRUE);
//}
//
//void CHelicopterChoosingDialog::OnEnChangeAircraftlenghtEdit()
//{
//	//UpdateData(TRUE);
//}
//
//void CHelicopterChoosingDialog::OnEnChangeMainbladelenghtEdit()
//{
//	//UpdateData(TRUE);
//}
//
//void CHelicopterChoosingDialog::OnEnChangeMainbladerpmEdit()
//{
//	//UpdateData(TRUE);
//}
//
//void CHelicopterChoosingDialog::OnEnChangeXinertiaEdit()
//{
//	//UpdateData(TRUE);
//}

BOOL CHelicopterChoosingDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	GetDlgItem(IDC_AIRCRAFTNAME_EDIT)->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


