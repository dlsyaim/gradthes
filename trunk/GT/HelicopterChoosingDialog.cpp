// HelicopterChoosingDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <fstream>
#include "GT.h"
#include "MainFrm.h"
#include "HelicopterChoosingDialog.h"



// CHelicopterChoosingDialog �Ի���

IMPLEMENT_DYNAMIC(CHelicopterChoosingDialog, CDialog)

CHelicopterChoosingDialog::CHelicopterChoosingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CHelicopterChoosingDialog::IDD, pParent)
	, helicopterName(_T(""))
	, helicopterMass(0.5)
	, mainBladeLength(0)
	, helicopterLength(0)
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
	DDX_Text(pDX, IDC_HELICOPTERNAME_EDIT, helicopterName);
	DDX_Text(pDX, IDC_HELICOPTERMASS_EDIT, helicopterMass);
	DDX_Text(pDX, IDC_MAINBLADELENGHT_EDIT, mainBladeLength);
	DDX_Text(pDX, IDC_HELICOPTERLENGHT_EDIT, helicopterLength);
	DDX_Text(pDX, IDC_MAINBLADERPM_EDIT, mainBladeRPM);
	DDX_Text(pDX, IDC_XINERTIA_EDIT, xInertia);
	DDV_MinMaxDouble(pDX, helicopterMass, 0.5, 1000);
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


// CHelicopterChoosingDialog ��Ϣ�������

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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	GetDlgItem(IDC_HELICOPTERNAME_EDIT)->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


CString CHelicopterChoosingDialog::constructLogString(void)
{
	CString log;
	log.Format("ģ��ѡ��%s", helicopterName);

	return log;
}

