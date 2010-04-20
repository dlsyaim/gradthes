// ServoActorDemarcateDialog.cpp : 实现文件
//

#include "stdafx.h"
#include <fstream>
#include "GT.h"
#include "ServoActorDemarcateDialog.h"
#include "Singleton.h"
#include "GSDefinition.h"

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
    return TRUE; // return TRUE unless you set the focus to a control
}

void CServoActorDemarcateDialog::OnBnClickedServoActorTestPass(void)
{
	AfxMessageBox("OK", MB_OK | MB_ICONINFORMATION);
	this->UpdateData();
	/***** Must send all of the test data to the server *****/
	/* First gain the current helicopter model */
	CSingleton *instance = CSingleton::getInstance();
	PHelicopterModel curPHM = instance->getCurPHM();

	m_tabCollective.UpdateData(TRUE);
	curPHM->sad.a1PWMValue[0] = (float)m_tabCollective.collectivePWM1;
	curPHM->sad.a1PWMValue[1] = (float)m_tabCollective.collectivePWM2;
	curPHM->sad.a1PWMValue[2] = (float)m_tabCollective.collectivePWM3;
	curPHM->sad.a1PWMValue[3] = (float)m_tabCollective.collectivePWM4;
	curPHM->sad.a1PWMValue[4] = (float)m_tabCollective.collectivePWM5;

	curPHM->sad.a1MeansureAng[0] = (float)m_tabCollective.collectiveAngle1;	
	curPHM->sad.a1MeansureAng[1] = (float)m_tabCollective.collectiveAngle2;
	curPHM->sad.a1MeansureAng[2] = (float)m_tabCollective.collectiveAngle3;
	curPHM->sad.a1MeansureAng[3] = (float)m_tabCollective.collectiveAngle4;
	curPHM->sad.a1MeansureAng[4] = (float)m_tabCollective.collectiveAngle5;

	m_tabRoll.UpdateData(TRUE);
	curPHM->sad.a2PWMValue[0] = (float)m_tabRoll.rollPWM1;
	curPHM->sad.a2PWMValue[1] = (float)m_tabRoll.rollPWM2;
	curPHM->sad.a2PWMValue[2] = (float)m_tabRoll.rollPWM3;
	curPHM->sad.a2PWMValue[3] = (float)m_tabRoll.rollPWM4;
	curPHM->sad.a2PWMValue[4] = (float)m_tabRoll.rollPWM5;

	curPHM->sad.a2MeansureAng[0] = (float)m_tabRoll.rollAngle1;	
	curPHM->sad.a2MeansureAng[1] = (float)m_tabRoll.rollAngle2;
	curPHM->sad.a2MeansureAng[2] = (float)m_tabRoll.rollAngle3;
	curPHM->sad.a2MeansureAng[3] = (float)m_tabRoll.rollAngle4;
	curPHM->sad.a2MeansureAng[4] = (float)m_tabRoll.rollAngle5;

	m_tabPitch.UpdateData(TRUE);
	curPHM->sad.a3PWMValue[0] = (float)m_tabPitch.pitchPWM1;
	curPHM->sad.a3PWMValue[1] = (float)m_tabPitch.pitchPWM2;
	curPHM->sad.a3PWMValue[2] = (float)m_tabPitch.pitchPWM3;
	curPHM->sad.a3PWMValue[3] = (float)m_tabPitch.pitchPWM4;
	curPHM->sad.a3PWMValue[4] = (float)m_tabPitch.pitchPWM5;

	curPHM->sad.a3MeansureAng[0] = (float)m_tabPitch.pitchAngle1;	
	curPHM->sad.a3MeansureAng[1] = (float)m_tabPitch.pitchAngle2;
	curPHM->sad.a3MeansureAng[2] = (float)m_tabPitch.pitchAngle3;
	curPHM->sad.a3MeansureAng[3] = (float)m_tabPitch.pitchAngle4;
	curPHM->sad.a3MeansureAng[4] = (float)m_tabPitch.pitchAngle5;

	m_tabTail.UpdateData(TRUE);
	curPHM->sad.a4PWMValue[0] = (float)m_tabTail.tailPWM1;
	curPHM->sad.a4PWMValue[1] = (float)m_tabTail.tailPWM2;
	curPHM->sad.a4PWMValue[2] = (float)m_tabTail.tailPWM3;
	curPHM->sad.a4PWMValue[3] = (float)m_tabTail.tailPWM4;
	curPHM->sad.a4PWMValue[4] = (float)m_tabTail.tailPWM5;

	curPHM->sad.a4MeansureAng[0] = (float)m_tabTail.tailAngle1;	
	curPHM->sad.a4MeansureAng[1] = (float)m_tabTail.tailAngle2;
	curPHM->sad.a4MeansureAng[2] = (float)m_tabTail.tailAngle3;
	curPHM->sad.a4MeansureAng[3] = (float)m_tabTail.tailAngle4;
	curPHM->sad.a4MeansureAng[4] = (float)m_tabTail.tailAngle5;

	/********** Construct the content of the servo actor demarcated data *********/
	/****** ATTENTION 162 is not enough ******/
	char command[162];
	__int16 *c = (__int16 *)command;
	c[0] = TAS_ACTORSET;

	memcpy(&(command[2]), (char*)&curPHM->sad, sizeof(curPHM->sad));
	command[2 + sizeof(curPHM->sad)] = '\0';
	
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	cln->SendSvr(command, 162);


	/***** Must save all of the test data into the files *****/
	
	// Open the uh.hm files and update it
	
	std::ifstream ifs("uh.hm", std::ios::binary | std::ios::in | std::ios::out);
	int numberOfHM;
	ifs.seekg(0, std::ios::end);
	numberOfHM = ifs.tellg() / sizeof(HelicopterModel);
	ifs.seekg(0, std::ios::beg);
	// Build a temporay helicopter model array
	PHelicopterModel tmpArray = new HelicopterModel[numberOfHM + 1];
	// The index of the above array
	int bytesRead, idx = 0;
	BOOL isFound = FALSE;
	// Start to read the file
	while (TRUE) {
		ifs.read((char *)(tmpArray + idx), sizeof(tmpArray[idx]));
		bytesRead = ifs.gcount();
		if (bytesRead != sizeof(tmpArray[idx])) { 
			break;
		}
		if (!strcmp(tmpArray[idx].helicopterName, curPHM->helicopterName)) {
			// Means found in the file
			isFound = TRUE;		
			tmpArray[idx] = *curPHM;
		}
		idx ++;
	}
	ifs.close();
	if (!isFound) {
		TRACE(_T("Theoretically this line of code can't be reached\n"));
		tmpArray[idx++] = *curPHM;
	}

	// Start to write to the file
	std::ofstream ofs("uh.hm", std::ios::binary | std::ios::trunc);
	for (int i = 0; i < idx; i++) {
		ofs.write((char *)(tmpArray + i), sizeof(tmpArray[i]));
	}
	ofs.close();

	delete[] tmpArray;

	/***** Set the global flag variable *****/
	instance->setIsServoActorDemarcated(TRUE);
}

void CServoActorDemarcateDialog::OnBnClickedServoActorTestFailure(void)
{
	/***** Set the global flag variable *****/
	AfxMessageBox(_T("Failed to demarcate the servo actor"), MB_OK | MB_ICONSTOP);
	CSingleton *instance = CSingleton::getInstance();
	instance->setIsServoActorDemarcated(FALSE);
}
 