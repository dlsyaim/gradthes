// PitchRotorDiskTab.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "PitchRotorDiskTab.h"


// PitchRotorDiskTab 对话框

IMPLEMENT_DYNAMIC(PitchRotorDiskTab, CTabPageSSL)

PitchRotorDiskTab::PitchRotorDiskTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(PitchRotorDiskTab::IDD, pParent)
	, pitchRotorDisk1(0)
	, pitchRotorDisk2(0)
	, pitchRotorDisk3(0)
	, pitchRotorDisk4(0)
	, pitchRotorDisk5(0)
	, rotorDisk1(0)
	, rotorDisk2(0)
	, rotorDisk3(0)
	, rotorDisk4(0)
	, rotorDisk5(0)
{

}

PitchRotorDiskTab::~PitchRotorDiskTab()
{
}

void PitchRotorDiskTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PITCH_ROTORDISK_EDIT1, pitchRotorDisk1);
	DDX_Text(pDX, IDC_PITCH_ROTORDISK_EDIT2, pitchRotorDisk2);
	DDX_Text(pDX, IDC_PITCH_ROTORDISK_EDIT3, pitchRotorDisk3);
	DDX_Text(pDX, IDC_PITCH_ROTORDISK_EDIT4, pitchRotorDisk4);
	DDX_Text(pDX, IDC_PITCH_ROTORDISK_EDIT5, pitchRotorDisk5);
	DDX_Text(pDX, IDC_PROTORDISK_VALUE_EDIT1, rotorDisk1);
	DDX_Text(pDX, IDC_PROTORDISK_VALUE_EDIT2, rotorDisk2);
	DDX_Text(pDX, IDC_PROTORDISK_VALUE_EDIT3, rotorDisk3);
	DDX_Text(pDX, IDC_PROTORDISK_VALUE_EDIT4, rotorDisk4);
	DDX_Text(pDX, IDC_PROTORDISK_VALUE_EDIT5, rotorDisk5);
}


BEGIN_MESSAGE_MAP(PitchRotorDiskTab, CTabPageSSL)
END_MESSAGE_MAP()


// PitchRotorDiskTab 消息处理程序
