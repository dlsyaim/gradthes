// GyroTestDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GT.h"
#include "GyroTestDialog.h"


// CGyroTestDialog �Ի���

IMPLEMENT_DYNAMIC(CGyroTestDialog, CDialog)

CGyroTestDialog::CGyroTestDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGyroTestDialog::IDD, pParent)
{

}

CGyroTestDialog::~CGyroTestDialog()
{
}

void CGyroTestDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGyroTestDialog, CDialog)
END_MESSAGE_MAP()


// CGyroTestDialog ��Ϣ�������
