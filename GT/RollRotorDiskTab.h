#pragma once
#include "TabPageSSL.h"

// RollRotorDiskTab �Ի���

class RollRotorDiskTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(RollRotorDiskTab)

public:
	RollRotorDiskTab(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RollRotorDiskTab();

// �Ի�������
	enum { IDD = IDD_ROLL_ROTORDISK_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double rollValue1;
	double rollValue2;
	double rollValue3;
	double rollValue4;
	double rollValue5;
	double rotorDiskValue1;
	double rotorDiskValue2;
	double rotorDiskValue3;
	double rotorDiskValue4;
	double rotorDiskValue5;
};
