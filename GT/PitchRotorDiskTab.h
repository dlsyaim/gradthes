#pragma once

#include "TabPageSSL.h"
// PitchRotorDiskTab 对话框

class PitchRotorDiskTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(PitchRotorDiskTab)

public:
	PitchRotorDiskTab(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PitchRotorDiskTab();

// 对话框数据
	enum { IDD = IDD_PITCH_ROTORDISK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double pitchRotorDisk1;
	double pitchRotorDisk2;
	double pitchRotorDisk3;
	double pitchRotorDisk4;
	double pitchRotorDisk5;
	double rotorDisk1;
	double rotorDisk2;
	double rotorDisk3;
	double rotorDisk4;
	double rotorDisk5;
};
