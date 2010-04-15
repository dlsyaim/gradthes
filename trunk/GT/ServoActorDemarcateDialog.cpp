// ServoActorDemarcateDialog.cpp : 实现文件
//

#include "stdafx.h"
#include <fstream>
#include "GT.h"
#include "ServoActorDemarcateDialog.h"

#include "GlobalExperimentData.h"


// CServoActorDemarcateDialog 对话框

IMPLEMENT_DYNAMIC(CServoActorDemarcateDialog, CDialog)

CServoActorDemarcateDialog::CServoActorDemarcateDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CServoActorDemarcateDialog::IDD, pParent)
{
	
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

	/***** Initialize a socket client *****/
	//// The server IP address
	//char *IP = "192.168.0.186";
	//// Initializing
	//if(netcln.initCln(IP, 22222) == 0) {
	//	AfxMessageBox("Failed to create a socket client", MB_OK | MB_ICONSTOP);		
	//}
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	/*cln->SendSvr(command, 2);*/


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

   // Set the net client
   m_tabCollective.setCln(cln);
   m_tabRoll.setCln(cln);
   m_tabPitch.setCln(cln);
   m_tabTail.setCln(cln);
   return TRUE; // return TRUE unless you set the focus to a control
}

void CServoActorDemarcateDialog::OnBnClickedServoActorTestPass(void)
{
	AfxMessageBox("OK", MB_OK | MB_ICONINFORMATION);
	this->UpdateData();
	/***** Must send all of the test data to the server *****/
	
	ServoActorData sad;

	m_tabCollective.UpdateData();
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

	m_tabRoll.UpdateData();
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

	m_tabPitch.UpdateData();
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

	m_tabTail.UpdateData();
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
	/****** Attention 162 is not enough ******/
	char command[162];
	__int16 *c = (__int16 *)command;
	c[0] = TAS_ACTORSET;

	memcpy(&(command[2]), (char*)&sad, sizeof(sad));
	command[2 + sizeof(sad)] = '\0';
	//netcln.SendSvr(command, 162);
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	cln->SendSvr(command, 162);


	/***** Must save all of the test data into the files *****/
	std::ofstream ofs("1.sad", std::ios::binary);
	ofs.write((char *)&sad, sizeof(sad));

	/***** Set the global flag variable *****/
	GlobalExperimentData::isServoActorDemarcated = TRUE;
}



void CServoActorDemarcateDialog::OnBnClickedServoActorTestFailure(void)
{
	AfxMessageBox("Failed", MB_OK | MB_ICONINFORMATION);
	/***** Set the global flag variable *****/
	GlobalExperimentData::isServoActorDemarcated = FALSE;
}
 