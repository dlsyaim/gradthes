#pragma once
#include "TabPageSSL.h"

// CHeliBodyDialog �Ի���

class CHeliBodyTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(CHeliBodyTab)

public:
	CHeliBodyTab(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHeliBodyTab();

// �Ի�������
	enum { IDD = IDD_HELICOPTER_BODY_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
