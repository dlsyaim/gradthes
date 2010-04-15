#pragma once
#include "TabPageSSL.h"

// CMainRotorTab 对话框

class CMainRotorTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(CMainRotorTab)

public:
	CMainRotorTab(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainRotorTab();

// 对话框数据
	enum { IDD = IDD_MAIN_ROTOR_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double radius_mr;
	double lift_curve_slope_mr;
	double blades_mr;
	double chord_mr;
	double hinge_offset_mr;
	double I_b_mr;
	double zero_lift_drag_coeff_mr;
	double max_thrust_coeff_mr;
	double kc_mr;
	double thrust_mr;
	double v_induced_mr;
	double h_hub_to_cg_mr;
	double d_hub_to_cg_mr;
	double v_tip_mr;
	double power_mr;
	double torque_mr;
	double rpm_mr;
	double lock_number_mr;
	double omega_mr;
	double tau_mr;
	double sigma_mr;
};
