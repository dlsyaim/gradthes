// ServoActorDemarcateDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "ServoActorDemarcateDialog.h"
#include "define\sysdef.h"
#include "PitchTab.h"
#include "CollectiveTab.h"
#include "RollTab.h"
#include "TailTab.h"


// CServoActorDemarcateDialog 对话框

IMPLEMENT_DYNAMIC(CServoActorDemarcateDialog, CDialog)

CServoActorDemarcateDialog::CServoActorDemarcateDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CServoActorDemarcateDialog::IDD, pParent)
{
	// Initialize a socket client
	// The server address
	char *IP = "192.168.0.186";
	// Initializing
	if(netcln.initCln(IP, 22222) == 0)
		AfxMessageBox("Failed to create a sending client", MB_OK | MB_ICONSTOP);
}

CServoActorDemarcateDialog::~CServoActorDemarcateDialog()
{
}

void CServoActorDemarcateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PARAMETER_TAB, m_tabServoActor);
}


BEGIN_MESSAGE_MAP(CServoActorDemarcateDialog, CDialog)
	ON_BN_CLICKED(IDC_SERVOACTOR_TEST_FAILURE_BUTTON, &CServoActorDemarcateDialog::OnBnClickedServoActorTestFailure)
	ON_BN_CLICKED(IDC_SERVOACTOR_TEST_PASS_BUTTON, &CServoActorDemarcateDialog::OnBnClickedServoActorTestPass)
END_MESSAGE_MAP()


// CServoActorDemarcateDialog 消息处理程序

BOOL CServoActorDemarcateDialog::OnInitDialog()
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

   // Set the net cln
   m_tabCollective.setCln(&netcln);
   m_tabRoll.setCln(&netcln);
   m_tabPitch.setCln(&netcln);
   m_tabTail.setCln(&netcln);
   return TRUE; // return TRUE unless you set the focus to a control
}

void CServoActorDemarcateDialog::OnBnClickedServoActorTestPass(void)
{
	AfxMessageBox("OK", MB_OK | MB_ICONINFORMATION);
	/***** Must send all of the test data to the server *****/	

	ServoActorData sad;

	((CCollectiveTab*)&m_tabCollective)->UpdateData();
	sad.a1PWMValue[0] = (float)((CCollectiveTab*)&m_tabCollective)->collectivePWM1;
	sad.a1PWMValue[1] = (float)((CCollectiveTab*)&m_tabCollective)->collectivePWM2;
	sad.a1PWMValue[2] = (float)((CCollectiveTab*)&m_tabCollective)->collectivePWM3;
	sad.a1PWMValue[3] = (float)((CCollectiveTab*)&m_tabCollective)->collectivePWM4;
	sad.a1PWMValue[4] = (float)((CCollectiveTab*)&m_tabCollective)->collectivePWM5;

	sad.a1MeansureAng[0] = (float)((CCollectiveTab*)&m_tabCollective)->collectiveAngle1;	
	sad.a1MeansureAng[1] = (float)((CCollectiveTab*)&m_tabCollective)->collectiveAngle2;
	sad.a1MeansureAng[2] = (float)((CCollectiveTab*)&m_tabCollective)->collectiveAngle3;
	sad.a1MeansureAng[3] = (float)((CCollectiveTab*)&m_tabCollective)->collectiveAngle4;
	sad.a1MeansureAng[4] = (float)((CCollectiveTab*)&m_tabCollective)->collectiveAngle5;

	((CRollTab*)&m_tabRoll)->UpdateData();
	sad.a2PWMValue[0] = (float)((CRollTab*)&m_tabRoll)->rollPWM1;
	sad.a2PWMValue[1] = (float)((CRollTab*)&m_tabRoll)->rollPWM2;
	sad.a2PWMValue[2] = (float)((CRollTab*)&m_tabRoll)->rollPWM3;
	sad.a2PWMValue[3] = (float)((CRollTab*)&m_tabRoll)->rollPWM4;
	sad.a2PWMValue[4] = (float)((CRollTab*)&m_tabRoll)->rollPWM5;

	sad.a2MeansureAng[0] = (float)((CRollTab*)&m_tabRoll)->rollAngle1;	
	sad.a2MeansureAng[1] = (float)((CRollTab*)&m_tabRoll)->rollAngle2;
	sad.a2MeansureAng[2] = (float)((CRollTab*)&m_tabRoll)->rollAngle3;
	sad.a2MeansureAng[3] = (float)((CRollTab*)&m_tabRoll)->rollAngle4;
	sad.a2MeansureAng[4] = (float)((CRollTab*)&m_tabRoll)->rollAngle5;

	((CPitchTab*)&m_tabPitch)->UpdateData();
	sad.a3PWMValue[0] = (float)((CPitchTab*)&m_tabPitch)->pitchPWM1;
	sad.a3PWMValue[1] = (float)((CPitchTab*)&m_tabPitch)->pitchPWM2;
	sad.a3PWMValue[2] = (float)((CPitchTab*)&m_tabPitch)->pitchPWM3;
	sad.a3PWMValue[3] = (float)((CPitchTab*)&m_tabPitch)->pitchPWM4;
	sad.a3PWMValue[4] = (float)((CPitchTab*)&m_tabPitch)->pitchPWM5;

	sad.a3MeansureAng[0] = (float)((CPitchTab*)&m_tabPitch)->pitchAngle1;	
	sad.a3MeansureAng[1] = (float)((CPitchTab*)&m_tabPitch)->pitchAngle2;
	sad.a3MeansureAng[2] = (float)((CPitchTab*)&m_tabPitch)->pitchAngle3;
	sad.a3MeansureAng[3] = (float)((CPitchTab*)&m_tabPitch)->pitchAngle4;
	sad.a3MeansureAng[4] = (float)((CPitchTab*)&m_tabPitch)->pitchAngle5;

	((CTailTab*)&m_tabTail)->UpdateData();
	sad.a4PWMValue[0] = (float)((CTailTab*)&m_tabTail)->tailPWM1;
	sad.a4PWMValue[1] = (float)((CTailTab*)&m_tabTail)->tailPWM2;
	sad.a4PWMValue[2] = (float)((CTailTab*)&m_tabTail)->tailPWM3;
	sad.a4PWMValue[3] = (float)((CTailTab*)&m_tabTail)->tailPWM4;
	sad.a4PWMValue[4] = (float)((CTailTab*)&m_tabTail)->tailPWM5;

	sad.a4MeansureAng[0] = (float)((CTailTab*)&m_tabTail)->tailAngle1;	
	sad.a4MeansureAng[1] = (float)((CTailTab*)&m_tabTail)->tailAngle2;
	sad.a4MeansureAng[2] = (float)((CTailTab*)&m_tabTail)->tailAngle3;
	sad.a4MeansureAng[3] = (float)((CTailTab*)&m_tabTail)->tailAngle4;
	sad.a4MeansureAng[4] = (float)((CTailTab*)&m_tabTail)->tailAngle5;

	/********** Construct the content of the communication test command *********/
	char command[162];
	__int16 *c = (__int16 *)command;
	c[0] = TAS_ACTORSET;

	memcpy(&(command[2]), (char*)&sad, sizeof(sad));
	command[2 + sizeof(sad)] = '\0';
	netcln.SendSvr(command, 162);
}


void CServoActorDemarcateDialog::OnBnClickedServoActorTestFailure(void)
{
	AfxMessageBox("Failed", MB_OK | MB_ICONINFORMATION);
}
 