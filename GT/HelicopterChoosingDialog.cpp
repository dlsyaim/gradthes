// HelicopterChoosingDialog.cpp : 实现文件
//

#include "stdafx.h"
#include <fstream>
#include <vector>
#include "GT.h"
#include "MainFrm.h"
#include "HelicopterChoosingDialog.h"
#include "Singleton.h"
#include "GSDefinition.h"



// CHelicopterChoosingDialog 对话框

IMPLEMENT_DYNAMIC(CHelicopterChoosingDialog, CDialog)

CHelicopterChoosingDialog::CHelicopterChoosingDialog(CWnd* pParent /*=NULL*/, BOOL isNew/* = TRUE*/, PHelicopterModel pHM/* = NULL*/)
	: CDialog(CHelicopterChoosingDialog::IDD, pParent)
{
	this->isNew = isNew;
	tempHelicopterModel = pHM;

	controller = new CHelicopterChoosingController();
}


CHelicopterChoosingDialog::~CHelicopterChoosingDialog()
{
	if (controller)
		delete controller;
}

void CHelicopterChoosingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HELICOPTER_TAB, m_heliChosTab);
}


BEGIN_MESSAGE_MAP(CHelicopterChoosingDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CHelicopterChoosingDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CHelicopterChoosingDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CHelicopterChoosingDialog 消息处理程序

void CHelicopterChoosingDialog::OnBnClickedOk()
{
	UpdateData(TRUE);

	CSingleton* instance = CSingleton::getInstance();
	PHelicopterModel pHM = instance->getCurPHM();

	// Get the body parameters
	m_bodyTab.UpdateData(TRUE);
	memcpy(pHM->helicopterName, m_bodyTab.helicopterName.GetBuffer(0), m_bodyTab.helicopterName.GetLength());
	pHM->heliPara.BodyPara.mass = m_bodyTab.heliMass;
	pHM->heliPara.BodyPara.Ixx = m_bodyTab.Ixx;
	pHM->heliPara.BodyPara.Iyy = m_bodyTab.Iyy;
	pHM->heliPara.BodyPara.Izz = m_bodyTab.Izz;
	pHM->heliPara.BodyPara.S_frontal = m_bodyTab.S_frontal;
	pHM->heliPara.BodyPara.S_side = m_bodyTab.S_side;
	pHM->heliPara.BodyPara.S_vert = m_bodyTab.S_vert;

	// Get the main rotor parameters
	m_mainRotorTab.UpdateData(TRUE);
	pHM->heliPara.MainrotorPara.radius_mr = m_mainRotorTab.radius_mr;
	pHM->heliPara.MainrotorPara.lift_curve_slope_mr = m_mainRotorTab.lift_curve_slope_mr;
	pHM->heliPara.MainrotorPara.blades_mr = m_mainRotorTab.blades_mr;
	pHM->heliPara.MainrotorPara.chord_mr = m_mainRotorTab.chord_mr;
	pHM->heliPara.MainrotorPara.hinge_offset_mr = m_mainRotorTab.hinge_offset_mr;
	pHM->heliPara.MainrotorPara.I_b_mr = m_mainRotorTab.I_b_mr;
	pHM->heliPara.MainrotorPara.zero_lift_drag_coeff_mr = m_mainRotorTab.zero_lift_drag_coeff_mr;
	pHM->heliPara.MainrotorPara.max_thrust_coeff_mr = m_mainRotorTab.max_thrust_coeff_mr;
	pHM->heliPara.MainrotorPara.kc_mr = m_mainRotorTab.kc_mr;
	pHM->heliPara.MainrotorPara.thrust_mr = m_mainRotorTab.thrust_mr;
	pHM->heliPara.MainrotorPara.v_induced_mr = m_mainRotorTab.v_induced_mr;
	pHM->heliPara.MainrotorPara.h_hub_to_cg_mr = m_mainRotorTab.h_hub_to_cg_mr;
	pHM->heliPara.MainrotorPara.d_hub_to_cg_mr = m_mainRotorTab.d_hub_to_cg_mr;
	pHM->heliPara.MainrotorPara.v_tip_mr = m_mainRotorTab.v_tip_mr;
	pHM->heliPara.MainrotorPara.power_mr = m_mainRotorTab.power_mr;
	pHM->heliPara.MainrotorPara.torque_mr = m_mainRotorTab.torque_mr;
	pHM->heliPara.MainrotorPara.rpm_mr = m_mainRotorTab.rpm_mr;
	pHM->heliPara.MainrotorPara.lock_number_mr = m_mainRotorTab.lock_number_mr;
	pHM->heliPara.MainrotorPara.omega_mr = m_mainRotorTab.omega_mr;
	pHM->heliPara.MainrotorPara.tau_mr = m_mainRotorTab.tau_mr;
	pHM->heliPara.MainrotorPara.sigma_mr = m_mainRotorTab.sigma_mr;

	// Get the tail rotor parameters
	m_tailRotorTab.UpdateData(TRUE);
	pHM->heliPara.TailrotorPara.radius_tr = m_tailRotorTab.radius_tr;
	pHM->heliPara.TailrotorPara.lift_curve_slope_tr = m_tailRotorTab.lift_curve_slope_tr;
	pHM->heliPara.TailrotorPara.blades_tr = m_tailRotorTab.blades_tr;
	pHM->heliPara.TailrotorPara.chord_tr = m_tailRotorTab.chord_tr;
	pHM->heliPara.TailrotorPara.zero_lift_drag_coeff_tr = m_tailRotorTab.zero_lift_drag_coeff_tr;
	pHM->heliPara.TailrotorPara.max_trust_coeff_tr = m_tailRotorTab.max_trust_coeff_tr;
	pHM->heliPara.TailrotorPara.thrust_tr = m_tailRotorTab.thrust_tr;
	pHM->heliPara.TailrotorPara.v_induced_tr = m_tailRotorTab.v_induced_tr;
	pHM->heliPara.TailrotorPara.h_hub_to_cg_tr = m_tailRotorTab.h_hub_to_cg_tr;
	pHM->heliPara.TailrotorPara.d_hub_to_cg_tr = m_tailRotorTab.d_hub_to_cg_tr;
	pHM->heliPara.TailrotorPara.power_tr = m_tailRotorTab.power_tr;
	pHM->heliPara.TailrotorPara.rpm_tr = m_tailRotorTab.rpm_tr;
	pHM->heliPara.TailrotorPara.omega_tr = m_tailRotorTab.omega_tr;

	if (!isNew) {
		if (memcmp(tempHelicopterModel, pHM, sizeof(HelicopterModel))) {
			if (controller->checkModel(instance->getCurHelicopterModelFileName())) {
				controller->saveModelFile(pHM);
			} else {
				controller->updateModelFile(pHM);
			}
		}
	} else {
		// Save the new helicopter model
		controller->saveModelFile(pHM);
	}

	instance->updateCurConfiguration();

	TRACE("Current Helicopter Model: %s\n", instance->getCS()->helicopterModelFileName);

	CDialog::OnOK();
}


BOOL CHelicopterChoosingDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Setup the tab control
    int nPageID = 0;
    m_bodyTab.Create(IDD_HELICOPTER_BODY_TAB, this);
    m_heliChosTab.AddSSLPage (_T("机体参数"), nPageID++, &m_bodyTab);

	m_mainRotorTab.Create(IDD_MAIN_ROTOR_TAB, this);
    m_heliChosTab.AddSSLPage(_T("主桨参数"), nPageID++, &m_mainRotorTab);
   
	m_tailRotorTab.Create(IDD_TAIL_ROTOR_TAB, this);
    m_heliChosTab.AddSSLPage(_T("尾桨参数"), nPageID++, &m_tailRotorTab);

	if (!isNew) {
		updateTabs();
	}
  
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CHelicopterChoosingDialog::updateTabs(void)
{
	if (tempHelicopterModel) {
		// Set the body parameters	
		m_bodyTab.helicopterName = tempHelicopterModel->helicopterName;
		m_bodyTab.heliMass = tempHelicopterModel->heliPara.BodyPara.mass;
		m_bodyTab.Ixx = tempHelicopterModel->heliPara.BodyPara.Ixx;
		m_bodyTab.Iyy = tempHelicopterModel->heliPara.BodyPara.Iyy;
		m_bodyTab.Izz = tempHelicopterModel->heliPara.BodyPara.Izz;
		m_bodyTab.S_frontal = tempHelicopterModel->heliPara.BodyPara.S_frontal;
		m_bodyTab.S_side = tempHelicopterModel->heliPara.BodyPara.S_side;
		m_bodyTab.S_vert = tempHelicopterModel->heliPara.BodyPara.S_vert;
		m_bodyTab.UpdateData(FALSE);

		// Set the main rotor parameters
		m_mainRotorTab.radius_mr = tempHelicopterModel->heliPara.MainrotorPara.radius_mr;
		m_mainRotorTab.lift_curve_slope_mr = tempHelicopterModel->heliPara.MainrotorPara.lift_curve_slope_mr;
		m_mainRotorTab.blades_mr = tempHelicopterModel->heliPara.MainrotorPara.blades_mr;
		m_mainRotorTab.chord_mr = tempHelicopterModel->heliPara.MainrotorPara.chord_mr;
		m_mainRotorTab.hinge_offset_mr = tempHelicopterModel->heliPara.MainrotorPara.hinge_offset_mr;
		m_mainRotorTab.I_b_mr = tempHelicopterModel->heliPara.MainrotorPara.I_b_mr;
		m_mainRotorTab.zero_lift_drag_coeff_mr = tempHelicopterModel->heliPara.MainrotorPara.zero_lift_drag_coeff_mr;
		m_mainRotorTab.max_thrust_coeff_mr = tempHelicopterModel->heliPara.MainrotorPara.max_thrust_coeff_mr;
		m_mainRotorTab.kc_mr = tempHelicopterModel->heliPara.MainrotorPara.kc_mr;
		m_mainRotorTab.thrust_mr = tempHelicopterModel->heliPara.MainrotorPara.thrust_mr;
		m_mainRotorTab.v_induced_mr = tempHelicopterModel->heliPara.MainrotorPara.v_induced_mr;
		m_mainRotorTab.h_hub_to_cg_mr = tempHelicopterModel->heliPara.MainrotorPara.h_hub_to_cg_mr;
		m_mainRotorTab.d_hub_to_cg_mr = tempHelicopterModel->heliPara.MainrotorPara.d_hub_to_cg_mr;
		m_mainRotorTab.v_tip_mr = tempHelicopterModel->heliPara.MainrotorPara.v_tip_mr;
		m_mainRotorTab.power_mr = tempHelicopterModel->heliPara.MainrotorPara.power_mr ;
		m_mainRotorTab.torque_mr = tempHelicopterModel->heliPara.MainrotorPara.torque_mr;
		m_mainRotorTab.rpm_mr = tempHelicopterModel->heliPara.MainrotorPara.rpm_mr;
		m_mainRotorTab.lock_number_mr = tempHelicopterModel->heliPara.MainrotorPara.lock_number_mr;
		m_mainRotorTab.omega_mr = tempHelicopterModel->heliPara.MainrotorPara.omega_mr;
		m_mainRotorTab.tau_mr = tempHelicopterModel->heliPara.MainrotorPara.tau_mr;
		m_mainRotorTab.sigma_mr = tempHelicopterModel->heliPara.MainrotorPara.sigma_mr;
		m_mainRotorTab.UpdateData(FALSE);

		// Set the tail rotor parameters
		m_tailRotorTab.radius_tr = tempHelicopterModel->heliPara.TailrotorPara.radius_tr;
		m_tailRotorTab.lift_curve_slope_tr = tempHelicopterModel->heliPara.TailrotorPara.lift_curve_slope_tr;
		m_tailRotorTab.blades_tr = tempHelicopterModel->heliPara.TailrotorPara.blades_tr;
		m_tailRotorTab.chord_tr = tempHelicopterModel->heliPara.TailrotorPara.chord_tr;
		m_tailRotorTab.zero_lift_drag_coeff_tr = tempHelicopterModel->heliPara.TailrotorPara.zero_lift_drag_coeff_tr;
		m_tailRotorTab.max_trust_coeff_tr = tempHelicopterModel->heliPara.TailrotorPara.max_trust_coeff_tr;
		m_tailRotorTab.thrust_tr = tempHelicopterModel->heliPara.TailrotorPara.thrust_tr;
		m_tailRotorTab.v_induced_tr = tempHelicopterModel->heliPara.TailrotorPara.v_induced_tr;
		m_tailRotorTab.h_hub_to_cg_tr = tempHelicopterModel->heliPara.TailrotorPara.h_hub_to_cg_tr;
		m_tailRotorTab.d_hub_to_cg_tr = tempHelicopterModel->heliPara.TailrotorPara.d_hub_to_cg_tr;
		m_tailRotorTab.power_tr = tempHelicopterModel->heliPara.TailrotorPara.power_tr;
		m_tailRotorTab.rpm_tr = tempHelicopterModel->heliPara.TailrotorPara.rpm_tr;
		m_tailRotorTab.omega_tr = tempHelicopterModel->heliPara.TailrotorPara.omega_tr;
		m_tailRotorTab.UpdateData(FALSE);
	}
}


void CHelicopterChoosingDialog::OnBnClickedCancel()
{
	CSingleton* instance = CSingleton::getInstance();
	TRACE("Current Helicopter Model: %s\n" , instance->getCS()->helicopterModelFileName);
	CDialog::OnCancel();
}
