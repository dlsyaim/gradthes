// TotalTab.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GT.h"
#include "TotalTab.h"


// CTotalTab �Ի���

IMPLEMENT_DYNAMIC(CTotalTab, CTabPageSSL)

CTotalTab::CTotalTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CTotalTab::IDD, pParent)
{

}

CTotalTab::~CTotalTab()
{
}

void CTotalTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTotalTab, CDialog)
END_MESSAGE_MAP()


// CTotalTab ��Ϣ�������
