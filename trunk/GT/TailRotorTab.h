#pragma once
#include "TabPageSSL.h"

// CTailRotorTab 对话框

class CTailRotorTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(CTailRotorTab)

public:
	CTailRotorTab(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTailRotorTab();

// 对话框数据
	enum { IDD = IDD_TAIL_ROTOR_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double lift_curve_slope_tr;
	double blades_tr;
	double chord_tr;
	double radius_tr;
	double zero_lift_drag_coeff_tr;
	double max_trust_coeff_tr;
	double d_hub_to_cg_tr;
	double h_hub_to_cg_tr;
	double omega_tr;
	double thrust_tr;
	double v_induced_tr;
	double power_tr;
	double rpm_tr;
};
