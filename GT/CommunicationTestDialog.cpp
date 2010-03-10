// CommunicationTestDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "CommunicationTestDialog.h"


// CCommunicationTestDialog 对话框

IMPLEMENT_DYNAMIC(CCommunicationTestDialog, CDialog)

CCommunicationTestDialog::CCommunicationTestDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCommunicationTestDialog::IDD, pParent)
{

}

CCommunicationTestDialog::~CCommunicationTestDialog()
{
}

void CCommunicationTestDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCommunicationTestDialog, CDialog)
END_MESSAGE_MAP()


// CCommunicationTestDialog 消息处理程序
