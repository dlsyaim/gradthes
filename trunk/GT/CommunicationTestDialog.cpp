// CommunicationTestDialog.cpp : 实现文件
//

#include "stdafx.h"
#include <fstream>
#include "GT.h"
#include "CommunicationTestDialog.h"
#include "NetSvrUdp.h"
#include "flysysdef.h"
#include "NetServer.h"
#include "NetClient.h"


// CCommunicationTestDialog 对话框

IMPLEMENT_DYNAMIC(CCommunicationTestDialog, CDialog)

CCommunicationTestDialog::CCommunicationTestDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCommunicationTestDialog::IDD, pParent)
	, commandDisplayer(_T(""))
	, returnMessageDisplayer(_T(""))
	, commandEdit(_T(""))
{

}

CCommunicationTestDialog::~CCommunicationTestDialog()
{
}

void CCommunicationTestDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GROUNDCOMMAND_EDIT, commandDisplayer);
	DDX_Text(pDX, IDC_RETURNMESSAGE_EDIT, returnMessageDisplayer);
	DDX_Text(pDX, IDC_EDIT, commandEdit);
}


BEGIN_MESSAGE_MAP(CCommunicationTestDialog, CDialog)
	ON_BN_CLICKED(IDC_COMMUNICATIONTEST_FAILURE, &CCommunicationTestDialog::OnBnClickedCommunicationtestFailure)
	ON_BN_CLICKED(IDC_COMMUNICATIONTEST_PASS, &CCommunicationTestDialog::OnBnClickedCommunicationtestPass)
	ON_BN_CLICKED(IDC_DEFAULTTEST_BUTTON, &CCommunicationTestDialog::OnBnClickedDefaulttestButton)
	ON_BN_CLICKED(IDC_COMMUNICATIONTEST_BUTTON, &CCommunicationTestDialog::OnBnClickedCommunicationtestButton)
END_MESSAGE_MAP()


// CCommunicationTestDialog 消息处理程序

void CCommunicationTestDialog::OnBnClickedCommunicationtestFailure()
{
	// TODO: write the log files
	std::ofstream of("communicationtest.log", std::ios::app);

	//char *buf = "log: First";
	//of.write(buf, sizeof buf);
	//of << std::endl;
	//char *buf1 = "log: Second\n\r";
	//of.write(buf1, sizeof buf1);
	//char *buf2 = "log: Third";
	//of.write(buf2, sizeof buf2);
}

void CCommunicationTestDialog::OnBnClickedCommunicationtestPass()
{
	// TODO: write the log files
	std::ofstream  of("communicationtest.log", std::ios::app);
}

void CCommunicationTestDialog::OnBnClickedDefaulttestButton()
{
	// TODO: default test and never 
}

void CCommunicationTestDialog::OnBnClickedCommunicationtestButton()
{
	// TODO: Communication test

	/********** First gain the current timestamp **********/
	// Declare a CTime object
	CTime currentTime;
	// Initialize the object
	currentTime = CTime::GetCurrentTime();
	// GetTime will return the number of seconds between the current CTime object and January 1, 1970
	time_t elapsed = currentTime.GetTime();
	unsigned long sendingTS = (unsigned long)elapsed;
	
	/********** Then Create a client to send commands **********/
	CNetClient cln;
	if (!cln.initCln("www.serveraddress.com", 0)) {
		AfxMessageBox("Failed to create a sending client", MB_OK | MB_ICONSTOP);
	}

}
