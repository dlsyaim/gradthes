// SteeringGearTestDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "SteeringGearTestDialog.h"


// CSteeringGearTestDialog 对话框

IMPLEMENT_DYNAMIC(CSteeringGearTestDialog, CDialog)

CSteeringGearTestDialog::CSteeringGearTestDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSteeringGearTestDialog::IDD, pParent)
{

}

CSteeringGearTestDialog::~CSteeringGearTestDialog()
{
}

void CSteeringGearTestDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSteeringGearTestDialog, CDialog)
END_MESSAGE_MAP()


// CSteeringGearTestDialog 消息处理程序
