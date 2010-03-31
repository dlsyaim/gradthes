#pragma once
#include "TabPageSSL.h"

// CollectiveRotorDiskTab 对话框

class CollectiveRotorDiskTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(CollectiveRotorDiskTab)

public:
	CollectiveRotorDiskTab(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CollectiveRotorDiskTab();

// 对话框数据
	enum { IDD = IDD_COLLECTIVE_ROTORDISK_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
