#pragma once
#include "TabPageSSL.h"

// CHeliBodyDialog 对话框

class CHeliBodyTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(CHeliBodyTab)

public:
	CHeliBodyTab(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHeliBodyTab();

// 对话框数据
	enum { IDD = IDD_HELICOPTER_BODY_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double heliMass;
	double Ixx;
	double Iyy;
	double Izz;
	double S_frontal;
	double S_side;
	double S_vert;
	CString helicopterName;
};
