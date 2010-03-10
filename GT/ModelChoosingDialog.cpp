// ModelChoosingDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "ModelChoosingDialog.h"


// CModelChoosingDialog 对话框

IMPLEMENT_DYNAMIC(CModelChoosingDialog, CDialog)

CModelChoosingDialog::CModelChoosingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CModelChoosingDialog::IDD, pParent)
{

}

CModelChoosingDialog::~CModelChoosingDialog()
{
}

void CModelChoosingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelChoosingDialog, CDialog)
END_MESSAGE_MAP()


// CModelChoosingDialog 消息处理程序
