// ModelChoosingDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GT.h"
#include "ModelChoosingDialog.h"


// CModelChoosingDialog �Ի���

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


// CModelChoosingDialog ��Ϣ�������
