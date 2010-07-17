// ServoActorDemarcateDialog.cpp : 实现文件
//

#include "stdafx.h"
#include <fstream>
#include "GT.h"
#include "ServoActorDemarcateDialog.h"
#include "Singleton.h"
#include "GSDefinition.h"
#include "HelicopterChoosingController.h"

#ifndef PI
#define PI 3.14159265358
#endif

// CServoActorDemarcateDialog 对话框

IMPLEMENT_DYNAMIC(CServoActorDemarcateDialog, CDialog)

CServoActorDemarcateDialog::CServoActorDemarcateDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CServoActorDemarcateDialog::IDD, pParent)
{
	pSAD = NULL;
}

// Constructor with the demarcated data
CServoActorDemarcateDialog::CServoActorDemarcateDialog(pServoActorData pSAD, CWnd* pParent/* = NULL*/)
	:CDialog(CServoActorDemarcateDialog::IDD, pParent)
{
	this->pSAD = pSAD;

	controller = new CHelicopterChoosingController();
}

CServoActorDemarcateDialog::~CServoActorDemarcateDialog()
{
	if (controller)
		delete controller;
}

void CServoActorDemarcateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PARAMETER_TAB, m_tabServoActor);
}


BEGIN_MESSAGE_MAP(CServoActorDemarcateDialog, CDialog)
	ON_BN_CLICKED(IDC_SERVOACTOR_TEST_FAILURE_BUTTON, &CServoActorDemarcateDialog::OnBnClickedServoActorTestFailure)
	ON_BN_CLICKED(IDC_SERVOACTOR_TEST_PASS_BUTTON, &CServoActorDemarcateDialog::OnBnClickedServoActorTestPass)
	ON_BN_CLICKED(IDCANCEL, &CServoActorDemarcateDialog::OnClickedCancel)
END_MESSAGE_MAP()


// CServoActorDemarcateDialog 消息处理程序

BOOL CServoActorDemarcateDialog::OnInitDialog()
{
	CDialog::OnInitDialog ();

    // Setup the tab control and tabs
    int nPageID = 0;
    m_tabCollective.Create(IDD_COLLECTIVE_TAB, this);
    m_tabServoActor.AddSSLPage (_T("总距标定"), nPageID++, &m_tabCollective);
    
	m_tabRoll.Create(IDD_ROLL_TAB, this);
    m_tabServoActor.AddSSLPage(_T("侧滚舵机标定"), nPageID++, &m_tabRoll);
    
	m_tabPitch.Create(IDD_PITCH_TAB, this);
    m_tabServoActor.AddSSLPage(_T("俯仰舵机标定"), nPageID++, &m_tabPitch);
    
	m_tabTail.Create(IDD_TAIL_TAB, this);
    m_tabServoActor.AddSSLPage(_T("方向舵机标定"), nPageID++, &m_tabTail);

    // Set the socket client
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
    m_tabCollective.setCln(cln);
    m_tabRoll.setCln(cln);
    m_tabPitch.setCln(cln);
    m_tabTail.setCln(cln);

	if (pSAD) 
	{
		// The servo actor is already demarcated, SO display the result
		m_tabCollective.Initialize(pSAD->a1PWMValue, pSAD->a1MeansureAng);
		m_tabRoll.Initialize(pSAD->a2PWMValue, pSAD->a2MeansureAng);
		m_tabPitch.Initialize(pSAD->a3PWMValue, pSAD->a3MeansureAng);
		m_tabTail.Initialize(pSAD->a4PWMValue, pSAD->a4MeansureAng);

	}

    return TRUE; // return TRUE unless you set the focus to a control
}

void CServoActorDemarcateDialog::OnBnClickedServoActorTestPass(void)
{
	// Get the data users enter
	this->UpdateData(TRUE);
	/********** Send the demarcated result to the server **********/
	
	// First get the current helicopter model 
	CSingleton *instance = CSingleton::getInstance();
	PHelicopterModel curPHM = instance->getCurPHM();
	HelicopterModel hm;
	memcpy(&hm, curPHM, sizeof(HelicopterModel));
	// Sencod fill the data
	m_tabCollective.UpdateData(TRUE);
	curPHM->sad.a1PWMValue[0] = (float)m_tabCollective.collectivePWM1;
	curPHM->sad.a1PWMValue[1] = (float)m_tabCollective.collectivePWM2;
	curPHM->sad.a1PWMValue[2] = (float)m_tabCollective.collectivePWM3;
	curPHM->sad.a1PWMValue[3] = (float)m_tabCollective.collectivePWM4;
	curPHM->sad.a1PWMValue[4] = (float)m_tabCollective.collectivePWM5;

	curPHM->sad.a1MeansureAng[0] = (float)(m_tabCollective.collectiveAngle1 / 180.0f * PI);	
	curPHM->sad.a1MeansureAng[1] = (float)(m_tabCollective.collectiveAngle2 / 180.0f * PI);
	curPHM->sad.a1MeansureAng[2] = (float)(m_tabCollective.collectiveAngle3 / 180.0f * PI);
	curPHM->sad.a1MeansureAng[3] = (float)(m_tabCollective.collectiveAngle4 / 180.0f * PI);
	curPHM->sad.a1MeansureAng[4] = (float)(m_tabCollective.collectiveAngle5 / 180.0f * PI);

	m_tabRoll.UpdateData(TRUE);
	curPHM->sad.a2PWMValue[0] = (float)m_tabRoll.rollPWM1;
	curPHM->sad.a2PWMValue[1] = (float)m_tabRoll.rollPWM2;
	curPHM->sad.a2PWMValue[2] = (float)m_tabRoll.rollPWM3;
	curPHM->sad.a2PWMValue[3] = (float)m_tabRoll.rollPWM4;
	curPHM->sad.a2PWMValue[4] = (float)m_tabRoll.rollPWM5;

	curPHM->sad.a2MeansureAng[0] = (float)(m_tabRoll.rollAngle1 / 180.0f * PI);	
	curPHM->sad.a2MeansureAng[1] = (float)(m_tabRoll.rollAngle2 / 180.0f * PI);
	curPHM->sad.a2MeansureAng[2] = (float)(m_tabRoll.rollAngle3 / 180.0f * PI);
	curPHM->sad.a2MeansureAng[3] = (float)(m_tabRoll.rollAngle4 / 180.0f * PI);
	curPHM->sad.a2MeansureAng[4] = (float)(m_tabRoll.rollAngle5 / 180.0f * PI);

	m_tabPitch.UpdateData(TRUE);
	curPHM->sad.a3PWMValue[0] = (float)m_tabPitch.pitchPWM1;
	curPHM->sad.a3PWMValue[1] = (float)m_tabPitch.pitchPWM2;
	curPHM->sad.a3PWMValue[2] = (float)m_tabPitch.pitchPWM3;
	curPHM->sad.a3PWMValue[3] = (float)m_tabPitch.pitchPWM4;
	curPHM->sad.a3PWMValue[4] = (float)m_tabPitch.pitchPWM5;

	curPHM->sad.a3MeansureAng[0] = (float)(m_tabPitch.pitchAngle1 / 180.0f * PI);	
	curPHM->sad.a3MeansureAng[1] = (float)(m_tabPitch.pitchAngle2 / 180.0f * PI);
	curPHM->sad.a3MeansureAng[2] = (float)(m_tabPitch.pitchAngle3 / 180.0f * PI);
	curPHM->sad.a3MeansureAng[3] = (float)(m_tabPitch.pitchAngle4 / 180.0f * PI);
	curPHM->sad.a3MeansureAng[4] = (float)(m_tabPitch.pitchAngle5 / 180.0f * PI);

	m_tabTail.UpdateData(TRUE);
	curPHM->sad.a4PWMValue[0] = (float)m_tabTail.tailPWM1;
	curPHM->sad.a4PWMValue[1] = (float)m_tabTail.tailPWM2;
	curPHM->sad.a4PWMValue[2] = (float)m_tabTail.tailPWM3;
	curPHM->sad.a4PWMValue[3] = (float)m_tabTail.tailPWM4;
	curPHM->sad.a4PWMValue[4] = (float)m_tabTail.tailPWM5;

	curPHM->sad.a4MeansureAng[0] = (float)(m_tabTail.tailAngle1 / 180.0f * PI);	
	curPHM->sad.a4MeansureAng[1] = (float)(m_tabTail.tailAngle2 / 180.0f * PI);
	curPHM->sad.a4MeansureAng[2] = (float)(m_tabTail.tailAngle3 / 180.0f * PI);
	curPHM->sad.a4MeansureAng[3] = (float)(m_tabTail.tailAngle4 / 180.0f * PI);
	curPHM->sad.a4MeansureAng[4] = (float)(m_tabTail.tailAngle5 / 180.0f * PI);

	// Save the permanent state
	curPHM->isDemarcated = 1;

	/********** Construct the content of the instruction *********/
	char command[sizeof(ServoActorData) + 2];
	__int16 *c = (__int16 *)command;
	c[0] = TAS_ACTORSET;

	memcpy(&(command[2]), (char*)&curPHM->sad, sizeof(curPHM->sad));
	
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	cln->SendSvr(command, sizeof(command));

	// Save the demarcated result into the file
	//instance->updateHelicopterModelFile();
	if (memcmp(&hm, curPHM, sizeof(HelicopterModel))) {
		if (controller->checkModel(instance->getCurHelicopterModelFileName())) {
			controller->saveModelFile(curPHM);
		} else {
			controller->updateModelFile(curPHM);
		}
	}

	
	/********** Set the global state variable **********/
	instance->setIsServoActorDemarcated(TRUE);
	
	OnOK();
}

void CServoActorDemarcateDialog::OnBnClickedServoActorTestFailure(void)
{
	/***** Set the global state variable *****/
	//CSingleton *instance = CSingleton::getInstance();
	//instance->setIsServoActorDemarcated(FALSE);

	OnCancel();
}

void CServoActorDemarcateDialog::OnClickedCancel()
{
	CSingleton *instance = CSingleton::getInstance();
	int result = AfxMessageBox(IDS_EXIT_SERVO_DEMARCATE, MB_YESNO | MB_ICONWARNING);
	switch (result) {
		case IDYES:
			/***** Set the global state variable *****/
			instance->setIsServoActorDemarcated(FALSE);
			OnCancel();
			break;
		case IDNO:
			break;
		default:
			break;
	}
}
 