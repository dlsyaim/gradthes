#pragma once

#include "TabPageSSL.h"
// PitchRotorDiskTab �Ի���

class PitchRotorDiskTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(PitchRotorDiskTab)

public:
	PitchRotorDiskTab(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PitchRotorDiskTab();

// �Ի�������
	enum { IDD = IDD_PITCH_ROTORDISK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
