// ollectiveRotorDiskTab.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "CollectiveRotorDiskTab.h"


// CollectiveRotorDiskTab 对话框

IMPLEMENT_DYNAMIC(CollectiveRotorDiskTab, CTabPageSSL)

CollectiveRotorDiskTab::CollectiveRotorDiskTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CollectiveRotorDiskTab::IDD, pParent)
	, collectiveRotorDisk1(0)
	, collectiveRotorDisk2(0)
	, collectiveRotorDisk3(0)
	, collectiveRotorDisk4(0)
	, collectiveRotorDisk5(0)
	, rotorDisk1(0)
	, rotorDisk2(0)
	, rotorDisk3(0)
	, rotorDisk4(0)
	, rotorDisk5(0)
{

}

CollectiveRotorDiskTab::~CollectiveRotorDiskTab()
{
}

void CollectiveRotorDiskTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COLLECTIVE_ROTORDISK_EDIT1, collectiveRotorDisk1);
	DDX_Text(pDX, IDC_COLLECTIVE_ROTORDISK_EDIT2, collectiveRotorDisk2);
	DDX_Text(pDX, IDC_COLLECTIVE_ROTORDISK_EDIT3, collectiveRotorDisk3);
	DDX_Text(pDX, IDC_COLLECTIVE_ROTORDISK_EDIT4, collectiveRotorDisk4);
	DDX_Text(pDX, IDC_COLLECTIVE_ROTORDISK_EDIT5, collectiveRotorDisk5);
	DDX_Text(pDX, IDC_CPROTORDISK_VALUE_EDIT1, rotorDisk1);
	DDX_Text(pDX, IDC_CPROTORDISK_VALUE_EDIT2, rotorDisk2);
	DDX_Text(pDX, IDC_CPROTORDISK_VALUE_EDIT3, rotorDisk3);
	DDX_Text(pDX, IDC_CPROTORDISK_VALUE_EDIT4, rotorDisk4);
	DDX_Text(pDX, IDC_CPROTORDISK_VALUE_EDIT5, rotorDisk5);
}


BEGIN_MESSAGE_MAP(CollectiveRotorDiskTab, CTabPageSSL)
END_MESSAGE_MAP()


// CollectiveRotorDiskTab 消息处理程序
