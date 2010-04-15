// TailRotorTab.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "TailRotorTab.h"


// CTailRotorTab 对话框

IMPLEMENT_DYNAMIC(CTailRotorTab, CTabPageSSL)

CTailRotorTab::CTailRotorTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CTailRotorTab::IDD, pParent)
	, lift_curve_slope_tr(0)
	, blades_tr(0)
	, chord_tr(0)
	, radius_tr(0)
	, zero_lift_drag_coeff_tr(0)
	, max_trust_coeff_tr(0)
	, d_hub_to_cg_tr(0)
	, h_hub_to_cg_tr(0)
	, omega_tr(0)
	, thrust_tr(0)
	, v_induced_tr(0)
	, power_tr(0)
	, rpm_tr(0)
{

}

CTailRotorTab::~CTailRotorTab()
{
}

void CTailRotorTab::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LIFT_CURVE_SLOPE_TR, lift_curve_slope_tr);
	DDX_Text(pDX, IDC_BLADES_TR, blades_tr);
	DDX_Text(pDX, IDC_CHORD_TR, chord_tr);
	DDX_Text(pDX, IDC_RADIUS_TR, radius_tr);
	DDX_Text(pDX, IDC_ZERO_LIFT_DRAG_COEFF_TR, zero_lift_drag_coeff_tr);
	DDX_Text(pDX, IDC_MAX_TRUST_COEFF_TR, max_trust_coeff_tr);
	DDX_Text(pDX, IDC_D_HUB_TO_CG_TR, d_hub_to_cg_tr);
	DDX_Text(pDX, IDC_H_HUB_TO_CG_TR, h_hub_to_cg_tr);
	DDX_Text(pDX, IDC_OMEGA_TR, omega_tr);
	DDX_Text(pDX, IDC_THRUST_TR, thrust_tr);
	DDX_Text(pDX, IDC_V_INDUCED_TR, v_induced_tr);
	DDX_Text(pDX, IDC_POWER_TR, power_tr);
	DDX_Text(pDX, IDC_RPM_TR, rpm_tr);
}


BEGIN_MESSAGE_MAP(CTailRotorTab, CTabPageSSL)
END_MESSAGE_MAP()


// CTailRotorTab 消息处理程序
