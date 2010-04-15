#pragma once
#include "TabPageSSL.h"

// CTailRotorTab �Ի���

class CTailRotorTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(CTailRotorTab)

public:
	CTailRotorTab(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTailRotorTab();

// �Ի�������
	enum { IDD = IDD_TAIL_ROTOR_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
