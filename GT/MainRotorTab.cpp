// MainRotorTab.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "MainRotorTab.h"


// CMainRotorTab 对话框

IMPLEMENT_DYNAMIC(CMainRotorTab, CTabPageSSL)

CMainRotorTab::CMainRotorTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CMainRotorTab::IDD, pParent)
	, radius_mr(0)
	, lift_curve_slope_mr(0)
	, blades_mr(0)
	, chord_mr(0)
	, hinge_offset_mr(0)
	, I_b_mr(0)
	, zero_lift_drag_coeff_mr(0)
	, max_thrust_coeff_mr(0)
	, kc_mr(0)
	, thrust_mr(0)
	, v_induced_mr(0)
	, h_hub_to_cg_mr(0)
	, d_hub_to_cg_mr(0)
	, v_tip_mr(0)
	, power_mr(0)
	, torque_mr(0)
	, rpm_mr(0)
	, lock_number_mr(0)
	, omega_mr(0)
	, tau_mr(0)
	, sigma_mr(0)
{

}

CMainRotorTab::~CMainRotorTab()
{
}

void CMainRotorTab::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RADIUS_MR, radius_mr);
	DDX_Text(pDX, IDC_LIFT_CURVE_SLOPE_MR, lift_curve_slope_mr);
	DDX_Text(pDX, IDC_BLADES_MR, blades_mr);
	DDX_Text(pDX, IDC_CHORD_MR, chord_mr);
	DDX_Text(pDX, IDC_HINGE_OFFSET_MR, hinge_offset_mr);
	DDX_Text(pDX, IDC_I_B_MR, I_b_mr);
	DDX_Text(pDX, IDC_ZERO_LIFT_DRAG_COEF_MR, zero_lift_drag_coeff_mr);
	DDX_Text(pDX, IDC_MAX_THRUST_COEF_MR, max_thrust_coeff_mr);
	DDX_Text(pDX, IDC_KC_MR, kc_mr);
	DDX_Text(pDX, IDC_THRUST_MR, thrust_mr);
	DDX_Text(pDX, IDC_V_INDUCED_MR, v_induced_mr);
	DDX_Text(pDX, IDC_H_HUB_TO_CG_MR, h_hub_to_cg_mr);
	DDX_Text(pDX, IDC_D_HUB_TO_CG_MR, d_hub_to_cg_mr);
	DDX_Text(pDX, IDC_V_TIP_MR, v_tip_mr);
	DDX_Text(pDX, IDC_POWER_MR, power_mr);
	DDX_Text(pDX, IDC_TORQUE_MR, torque_mr);
	DDX_Text(pDX, IDC_RPM_MR, rpm_mr);
	DDX_Text(pDX, IDC_LOCK_NUMBER_MR, lock_number_mr);
	DDX_Text(pDX, IDC_OMEGA_MR, omega_mr);
	DDX_Text(pDX, IDC_TAU_MR, tau_mr);
	DDX_Text(pDX, IDC_SIGMA_MR, sigma_mr);
}


BEGIN_MESSAGE_MAP(CMainRotorTab, CTabPageSSL)
END_MESSAGE_MAP()


// CMainRotorTab 消息处理程序
