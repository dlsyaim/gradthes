#pragma once
#include "TabPageSSL.h"

// CollectiveRotorDiskTab �Ի���

class CollectiveRotorDiskTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(CollectiveRotorDiskTab)

public:
	CollectiveRotorDiskTab(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CollectiveRotorDiskTab();

// �Ի�������
	enum { IDD = IDD_COLLECTIVE_ROTORDISK_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double collectiveRotorDisk1;
	double collectiveRotorDisk2;
	double collectiveRotorDisk3;
	double collectiveRotorDisk4;
	double collectiveRotorDisk5;
	double rotorDisk1;
	double rotorDisk2;
	double rotorDisk3;
	double rotorDisk4;
	double rotorDisk5;
};
