// GPSTestDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "GPSTestDialog.h"


// CGPSTestDialog 对话框

IMPLEMENT_DYNAMIC(CGPSTestDialog, CDialog)

CGPSTestDialog::CGPSTestDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGPSTestDialog::IDD, pParent)
{

}

CGPSTestDialog::~CGPSTestDialog()
{
}

void CGPSTestDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGPSTestDialog, CDialog)
END_MESSAGE_MAP()


// CGPSTestDialog 消息处理程序
