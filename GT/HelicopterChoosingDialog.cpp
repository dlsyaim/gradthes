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
	, helicopterName(_T(""))
	, helicopterMass(0.5)
	, mainBladeLength(0)
	, helicopterLength(0)
	, mainBladeRPM(0)
	, xInertia(0)
{
	isNew = TRUE;
}

CHelicopterChoosingDialog::CHelicopterChoosingDialog(CString _helicopterName, double _helicopterMass, double _helicopterLength, 
		double _mainBladeLength, double _mainBladeRPM, double _xInertia,
		CWnd* pParent/* = NULL*/) 
: CDialog(CHelicopterChoosingDialog::IDD, pParent)
, helicopterName(_helicopterName)
, helicopterMass(_helicopterMass)
, mainBladeLength(_mainBladeLength)
, helicopterLength(_helicopterLength)
, mainBladeRPM(_mainBladeRPM)
, xInertia(_xInertia)
{
	isNew = FALSE;
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


// CHelicopterChoosingDialog 消息处理程序

void CHelicopterChoosingDialog::OnBnClickedOk()
{
	// TODO:1. Construct a helicopter model and save it into files, or update a helicopter model already in the files.
	this->UpdateData();
	/***** Construct a flight model *****/
	/*
		HelicopterModel hm;
		hm.setHelicopterName(helicopterName);
		hm.setHelicopterMass(helicopterMass);
	    ...
	*/
	
	/***** Then use ofstream to save the helicopter model into files. *****/
	
	/*
		if (!isNew) {
			// We need to read all the helicopter model from the files
			std::vector<HelicopterModel*> HMV;
			HelicopterModel hmT;
			std::ifstream ifs("helicopterModel.hm", std::ios::binary);
			while(!eof()) {				
				ifs.read((char*) hmT, sizeof(hmT));
				if (hmT.helicopterName == hm.helicopterName)
					HMV.insert(HMV.begin(), &hm);
			    else 
					HMV.insert(HMV.begin(), &hmT);
			}
			ifs.close();
			
			// Then write the updated helicopter models into files
			ofstream ofs("helicopterModel.hm", std::ios::binary | std::ios::trunc);
			std::vector<HelicopterModel*>::iterator itr;
			for (itr = HMV.begin(); itr != HMV.end(); itr++) {
				ofs.write((char*)itr, sizeof(*itr));
			}
			ofs.close();

		} else {
			// We just append the new helicopter model into the end of the files
			std::ofstream ofs("helicopterModel.hm", std::ios::binary | std::ios::app);
			ofs.write((char*)&hm, sizeof(hm));
			ofs.close();
		}
		
	*/

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
	// The first edit control gets the focus.
	GetDlgItem(IDC_HELICOPTERNAME_EDIT)->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


CString CHelicopterChoosingDialog::constructLogString(void)
{
	CString log;
	log.Format("模型选择：%s", helicopterName);

	return log;
}

