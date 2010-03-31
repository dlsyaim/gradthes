// RollRotorDiskTab.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "RollRotorDiskTab.h"


// RollRotorDiskTab 对话框

IMPLEMENT_DYNAMIC(RollRotorDiskTab, CTabPageSSL)

RollRotorDiskTab::RollRotorDiskTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(RollRotorDiskTab::IDD, pParent)
	, rollValue1(0)
	, rollValue2(0)
	, rollValue3(0)
	, rollValue4(0)
	, rollValue5(0)
	, rotorDiskValue1(0)
	, rotorDiskValue2(0)
	, rotorDiskValue3(0)
	, rotorDiskValue4(0)
	, rotorDiskValue5(0)
{

}

RollRotorDiskTab::~RollRotorDiskTab()
{
}

void RollRotorDiskTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ROLL_ROTORDISK_EDIT1, rollValue1);
	DDX_Text(pDX, IDC_ROLL_ROTORDISK_EDIT2, rollValue2);
	DDX_Text(pDX, IDC_ROLL_ROTORDISK_EDIT3, rollValue3);
	DDX_Text(pDX, IDC_ROLL_ROTORDISK_EDIT4, rollValue4);
	DDX_Text(pDX, IDC_ROLL_ROTORDISK_EDIT5, rollValue5);
	DDX_Text(pDX, IDC_ROTORDISK_VALUE_EDIT1, rotorDiskValue1);
	DDX_Text(pDX, IDC_ROTORDISK_VALUE_EDIT2, rotorDiskValue2);
	DDX_Text(pDX, IDC_ROTORDISK_VALUE_EDIT3, rotorDiskValue3);
	DDX_Text(pDX, IDC_ROTORDISK_VALUE_EDIT4, rotorDiskValue4);
	DDX_Text(pDX, IDC_ROTORDISK_VALUE_EDIT5, rotorDiskValue5);
}


BEGIN_MESSAGE_MAP(RollRotorDiskTab, CTabPageSSL)
END_MESSAGE_MAP()


// RollRotorDiskTab 消息处理程序
