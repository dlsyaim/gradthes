// HeliBodyDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "HeliBodyTab.h"


// CHeliBodyDialog 对话框

IMPLEMENT_DYNAMIC(CHeliBodyTab, CTabPageSSL)

CHeliBodyTab::CHeliBodyTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CHeliBodyTab::IDD, pParent)
	, heliMass(0)
	, Ixx(0)
	, Iyy(0)
	, Izz(0)
	, S_frontal(0)
	, S_side(0)
	, S_vert(0)
	, helicopterName(_T(""))
{

}

CHeliBodyTab::~CHeliBodyTab()
{
}

void CHeliBodyTab::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HELICOPTER_MASS, heliMass);
	DDX_Text(pDX, IDC_X_INERTIA, Ixx);
	DDX_Text(pDX, IDC_Y_INERTIA, Iyy);
	DDX_Text(pDX, IDC_Z_INERTIA, Izz);
	DDX_Text(pDX, IDC_S_FRONTAL, S_frontal);
	DDX_Text(pDX, IDC_S_SIDE, S_side);
	DDX_Text(pDX, IDC_S_VERT, S_vert);
	DDX_Text(pDX, IDC_HELICOPTER_NAME, helicopterName);
}


BEGIN_MESSAGE_MAP(CHeliBodyTab, CTabPageSSL)
END_MESSAGE_MAP()


// CHeliBodyDialog 消息处理程序
