// GPSTestDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GT.h"
#include "GPSTestDialog.h"


// CGPSTestDialog �Ի���

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


// CGPSTestDialog ��Ϣ�������
