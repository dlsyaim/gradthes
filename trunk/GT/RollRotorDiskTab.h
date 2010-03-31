#pragma once
#include "TabPageSSL.h"

// RollRotorDiskTab 对话框

class RollRotorDiskTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(RollRotorDiskTab)

public:
	RollRotorDiskTab(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RollRotorDiskTab();

// 对话框数据
	enum { IDD = IDD_ROLL_ROTORDISK_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
