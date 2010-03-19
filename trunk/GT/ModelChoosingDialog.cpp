// ModelChoosingDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "MainFrm.h"
#include "ModelChoosingDialog.h"




// CModelChoosingDialog 对话框

IMPLEMENT_DYNAMIC(CModelChoosingDialog, CDialog)

CModelChoosingDialog::CModelChoosingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CModelChoosingDialog::IDD, pParent)
	, aircraftName(_T(""))
	, aircraftMass(0.5)
	, mainBladeLength(0)
	, aircraftLength(0)
	, mainBladeRPM(0)
	, xInertia(0)
{

}

CModelChoosingDialog::~CModelChoosingDialog()
{
}

void CModelChoosingDialog::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CModelChoosingDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CModelChoosingDialog::OnBnClickedOk)
	/*ON_EN_CHANGE(IDC_AIRCRAFTNAME_EDIT, &CModelChoosingDialog::OnEnChangeAircraftnameEdit)
	ON_EN_CHANGE(IDC_AIRCRAFTMASS_EDIT, &CModelChoosingDialog::OnEnChangeAircraftmassEdit)
	ON_EN_CHANGE(IDC_AIRCRAFTLENGHT_EDIT, &CModelChoosingDialog::OnEnChangeAircraftlenghtEdit)
	ON_EN_CHANGE(IDC_MAINBLADELENGHT_EDIT, &CModelChoosingDialog::OnEnChangeMainbladelenghtEdit)
	ON_EN_CHANGE(IDC_MAINBLADERPM_EDIT, &CModelChoosingDialog::OnEnChangeMainbladerpmEdit)
	ON_EN_CHANGE(IDC_XINERTIA_EDIT, &CModelChoosingDialog::OnEnChangeXinertiaEdit)*/
END_MESSAGE_MAP()


// CModelChoosingDialog 消息处理程序

void CModelChoosingDialog::OnBnClickedOk()
{
	// TODO: 
	//UpdateData(TRUE);
	OnOK();
}

//void CModelChoosingDialog::OnEnChangeAircraftnameEdit()
//{
//	//UpdateData(TRUE);
//}
//
//void CModelChoosingDialog::OnEnChangeAircraftmassEdit()
//{
//	//UpdateData(TRUE);
//}
//
//void CModelChoosingDialog::OnEnChangeAircraftlenghtEdit()
//{
//	//UpdateData(TRUE);
//}
//
//void CModelChoosingDialog::OnEnChangeMainbladelenghtEdit()
//{
//	//UpdateData(TRUE);
//}
//
//void CModelChoosingDialog::OnEnChangeMainbladerpmEdit()
//{
//	//UpdateData(TRUE);
//}
//
//void CModelChoosingDialog::OnEnChangeXinertiaEdit()
//{
//	//UpdateData(TRUE);
//}

BOOL CModelChoosingDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	GetDlgItem(IDC_AIRCRAFTNAME_EDIT)->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
