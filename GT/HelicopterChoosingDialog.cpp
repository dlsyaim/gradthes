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
	this->pHM = pHM;

	
}


CHelicopterChoosingDialog::~CHelicopterChoosingDialog()
{
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
	/***** 1. Construct a helicopter model and save it into files, or update a helicopter model already in the files. *****/
	this->UpdateData(TRUE);
	
	if (pHM == NULL) {
		AfxMessageBox("Failed to create a helicopter model\n", MB_OK | MB_ICONSTOP);
		CDialog::OnOK();
		return;
	}
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

	/***** Then use ofstream to save the helicopter model into the file. *****/
	if (!isNew) {
		// We need to read all the helicopter model from the file
		CString tName;
		// A boolean variable indicates if the helicopter name has been changed
		BOOL isChanged = TRUE;
		std::ifstream ifs("uh.hm", std::ios::binary);
		int countRead, hmCount;
		ifs.seekg(0, std::ios::end);
		hmCount = ifs.tellg() / sizeof(HelicopterModel);
		ifs.seekg(0, std::ios::beg);
		// Temporay helicopter model array
		PHelicopterModel temp = new HelicopterModel[hmCount + 1];
		// Index
		int idx = 0;
		while(TRUE) {	
			ifs.read((char*)(temp + idx), sizeof(temp[idx]));
			countRead = ifs.gcount();
			if (countRead != sizeof(temp[idx]))
				break;
			tName = temp[idx].helicopterName;
			if (tName == m_bodyTab.helicopterName) {
				temp[idx] = *pHM;
				isChanged = FALSE;
			}
			idx++;
		}
		ifs.close();
		
		// Additional processing
		if (isChanged) {
			temp[idx++] = *pHM;
		}

		
		// Then write the updated helicopter models into the file
		std::ofstream ofs("uh.hm", std::ios::binary | std::ios::trunc);
		for (int i = 0; i < idx; i++) {
			ofs.write((char *)(temp + i), sizeof(temp[i]));
		}
		ofs.close();

		delete[] temp;

	} else {
		/*
		 * We just append the new helicopter model after the end of the file, so the last helicopter model is the newest.
		 * No overriding warning
		 */
		std::ofstream ofs("uh.hm", std::ios::binary | std::ios::app);
		ofs.write((char*)pHM, sizeof(*pHM));
		ofs.close();
	}
	
	/* Update the helicopter model buffer */
	CSingleton* instance = CSingleton::getInstance();
	instance->updateBuffer(isNew, pHM);
	/* Update the previous helicopter model buffer */
	instance->updatePrePHM();

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

	if (pHM->helicopterName[0] != '\0') {
		updateTabs();
	}
  
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


CString CHelicopterChoosingDialog::constructLogString(void)
{
	CString log;
	//log.Format("模型选择：%s", helicopterName);

	return log;
}

void CHelicopterChoosingDialog::updateTabs(void)
{
	if (pHM) {
		// Set the body parameters	
		m_bodyTab.helicopterName = pHM->helicopterName;
		m_bodyTab.heliMass = pHM->heliPara.BodyPara.mass;
		m_bodyTab.Ixx = pHM->heliPara.BodyPara.Ixx;
		m_bodyTab.Iyy = pHM->heliPara.BodyPara.Iyy;
		m_bodyTab.Izz = pHM->heliPara.BodyPara.Izz;
		m_bodyTab.S_frontal = pHM->heliPara.BodyPara.S_frontal;
		m_bodyTab.S_side = pHM->heliPara.BodyPara.S_side;
		m_bodyTab.S_vert = pHM->heliPara.BodyPara.S_vert;
		m_bodyTab.UpdateData(FALSE);

		// Get the main rotor parameters
		m_mainRotorTab.radius_mr = pHM->heliPara.MainrotorPara.radius_mr;
		m_mainRotorTab.lift_curve_slope_mr = pHM->heliPara.MainrotorPara.lift_curve_slope_mr;
		m_mainRotorTab.blades_mr = pHM->heliPara.MainrotorPara.blades_mr;
		m_mainRotorTab.chord_mr = pHM->heliPara.MainrotorPara.chord_mr;
		m_mainRotorTab.hinge_offset_mr = pHM->heliPara.MainrotorPara.hinge_offset_mr;
		m_mainRotorTab.I_b_mr = pHM->heliPara.MainrotorPara.I_b_mr;
		m_mainRotorTab.zero_lift_drag_coeff_mr = pHM->heliPara.MainrotorPara.zero_lift_drag_coeff_mr;
		m_mainRotorTab.max_thrust_coeff_mr = pHM->heliPara.MainrotorPara.max_thrust_coeff_mr;
		m_mainRotorTab.kc_mr = pHM->heliPara.MainrotorPara.kc_mr;
		m_mainRotorTab.thrust_mr = pHM->heliPara.MainrotorPara.thrust_mr;
		m_mainRotorTab.v_induced_mr = pHM->heliPara.MainrotorPara.v_induced_mr;
		m_mainRotorTab.h_hub_to_cg_mr = pHM->heliPara.MainrotorPara.h_hub_to_cg_mr;
		m_mainRotorTab.d_hub_to_cg_mr = pHM->heliPara.MainrotorPara.d_hub_to_cg_mr;
		m_mainRotorTab.v_tip_mr = pHM->heliPara.MainrotorPara.v_tip_mr;
		m_mainRotorTab.power_mr = pHM->heliPara.MainrotorPara.power_mr ;
		m_mainRotorTab.torque_mr = pHM->heliPara.MainrotorPara.torque_mr;
		m_mainRotorTab.rpm_mr = pHM->heliPara.MainrotorPara.rpm_mr;
		m_mainRotorTab.lock_number_mr = pHM->heliPara.MainrotorPara.lock_number_mr;
		m_mainRotorTab.omega_mr = pHM->heliPara.MainrotorPara.omega_mr;
		m_mainRotorTab.tau_mr = pHM->heliPara.MainrotorPara.tau_mr;
		m_mainRotorTab.sigma_mr = pHM->heliPara.MainrotorPara.sigma_mr;
		m_mainRotorTab.UpdateData(FALSE);

		// Get the tail rotor parameters
		m_tailRotorTab.radius_tr = pHM->heliPara.TailrotorPara.radius_tr;
		m_tailRotorTab.lift_curve_slope_tr = pHM->heliPara.TailrotorPara.lift_curve_slope_tr;
		m_tailRotorTab.blades_tr = pHM->heliPara.TailrotorPara.blades_tr;
		m_tailRotorTab.chord_tr = pHM->heliPara.TailrotorPara.chord_tr;
		m_tailRotorTab.zero_lift_drag_coeff_tr = pHM->heliPara.TailrotorPara.zero_lift_drag_coeff_tr;
		m_tailRotorTab.max_trust_coeff_tr = pHM->heliPara.TailrotorPara.max_trust_coeff_tr;
		m_tailRotorTab.thrust_tr = pHM->heliPara.TailrotorPara.thrust_tr;
		m_tailRotorTab.v_induced_tr = pHM->heliPara.TailrotorPara.v_induced_tr;
		m_tailRotorTab.h_hub_to_cg_tr = pHM->heliPara.TailrotorPara.h_hub_to_cg_tr;
		m_tailRotorTab.d_hub_to_cg_tr = pHM->heliPara.TailrotorPara.d_hub_to_cg_tr;
		m_tailRotorTab.power_tr = pHM->heliPara.TailrotorPara.power_tr;
		m_tailRotorTab.rpm_tr = pHM->heliPara.TailrotorPara.rpm_tr;
		m_tailRotorTab.omega_tr = pHM->heliPara.TailrotorPara.omega_tr;
		m_tailRotorTab.UpdateData(FALSE);
	}
}


void CHelicopterChoosingDialog::OnBnClickedCancel()
{

	CSingleton* instance = CSingleton::getInstance();
	instance->rollBackCurPHM(isNew);

	CDialog::OnCancel();
}
