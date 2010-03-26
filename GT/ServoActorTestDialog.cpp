// ServoActorTestDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "ServoActorTestDialog.h"


// CServoActorTestDialog 对话框

IMPLEMENT_DYNAMIC(CServoActorTestDialog, CDialog)

CServoActorTestDialog::CServoActorTestDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CServoActorTestDialog::IDD, pParent)
{

}

CServoActorTestDialog::~CServoActorTestDialog()
{
}

void CServoActorTestDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PARAMETER_TAB, m_tabServoActor);
}


BEGIN_MESSAGE_MAP(CServoActorTestDialog, CDialog)
END_MESSAGE_MAP()


// CServoActorTestDialog 消息处理程序

BOOL CServoActorTestDialog::OnInitDialog()
{
	CDialog::OnInitDialog ();

   // Setup the tab control
   int nPageID = 0;
   m_tabCollective.Create(IDD_COLLECTIVE_TAB, this);
   m_tabServoActor.AddSSLPage (_T("总距标定"), nPageID++, &m_tabCollective);
   m_tabRoll.Create(IDD_ROLL_TAB, this);
   m_tabServoActor.AddSSLPage(_T("侧滚舵机标定"), nPageID++, &m_tabRoll);
   m_tabPitch.Create(IDD_PITCH_TAB, this);
   m_tabServoActor.AddSSLPage(_T("俯仰舵机标定"), nPageID++, &m_tabPitch);
   m_tabTail.Create(IDD_TAIL_TAB, this);
   m_tabServoActor.AddSSLPage(_T("方向舵机标定"), nPageID++, &m_tabTail);
   return TRUE; // return TRUE unless you set the focus to a control
}
