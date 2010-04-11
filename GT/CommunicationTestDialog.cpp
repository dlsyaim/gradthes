// CommunicationTestDialog.cpp : 实现文件
//

#include "stdafx.h"
#include <fstream>
#include "GT.h"
#include "CommunicationTestDialog.h"
#include "define\sysdef.h"
#include "func\NetCln.h"
#include "func\NetSvrHeli.h"
#include "MsgType.h"
#include "GlobalExperimentData.h"



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
	ON_BN_CLICKED(IDC_COMMUNICATIONTEST_FAILURE, &CCommunicationTestDialog::OnBnClickedCommunicationTestFailure)
	ON_BN_CLICKED(IDC_COMMUNICATIONTEST_PASS, &CCommunicationTestDialog::OnBnClickedCommunicationTestPass)
	ON_BN_CLICKED(IDC_DEFAULTTEST_BUTTON, &CCommunicationTestDialog::OnBnClickedDefaultTestButton)
	ON_BN_CLICKED(IDC_COMMUNICATIONTEST_BUTTON, &CCommunicationTestDialog::OnBnClickedCommunicationTestButton)
	ON_MESSAGE(COMMUNICATION_TEST_REPLY_MSG, &OnReplyMsgArrived)
END_MESSAGE_MAP()


// CCommunicationTestDialog 消息处理程序

void CCommunicationTestDialog::OnBnClickedCommunicationTestFailure()
{
	// TODO: Write the log files	
	/*
		std::ofstream of("communicationtest.log", std::ios::app);
		char *buf = "通讯测试: 失败";
		of.write(buf, sizeof buf);
		of << std::endl;
		of.close();
	*/	

	/********** Update the global experimental states **********/
	GlobalExperimentData::isCommunicationTestPass = FALSE;
}

void CCommunicationTestDialog::OnBnClickedCommunicationTestPass()
{
	// TODO: Write the log files	
	
	/*
		std::ofstream  of("communicationtest.log", std::ios::app);	
		char *buf = "通讯测试: 成功";
		of.write(buf, sizeof buf);
		of << std::endl;	
		of.close();
	*/

	/********** Update the global experimental states **********/
	GlobalExperimentData::isCommunicationTestPass = TRUE;
}

void CCommunicationTestDialog::OnBnClickedDefaultTestButton()
{
	/********** Create a default command **********/
	CString content = _T("This is the default command");
	sendCommunicationTestCommand(content);

}

void CCommunicationTestDialog::OnBnClickedCommunicationTestButton()
{
	
	/********** First check if the user enter commands or not **********/
	this->UpdateData(TRUE);
	if (!commandEdit.GetLength()) {
		AfxMessageBox("Commands required", MB_OK | MB_ICONSTOP);
		return;
	}
	
	sendCommunicationTestCommand(commandEdit);
}

LRESULT CCommunicationTestDialog::OnReplyMsgArrived(WPARAM w, LPARAM l)
{
	const CNetSvrHeli* svr = ((CGTApp*)AfxGetApp())->getSvr();
	returnMessageDisplayer.Append((char *)svr->recvbuf + 2);
	returnMessageDisplayer.Append(_T("\r\n"));
	this->UpdateData(FALSE);
	return TRUE;
}

void CCommunicationTestDialog::sendCommunicationTestCommand(CString content)
{
	/********** Firstly create a client to send commands **********/
	
	// The client point of the socket
	CNetCln netcln;
	// The server address
	char *IP = "192.168.0.186";
	// Initializing
	if(netcln.initCln(IP, 22222) == 0)
	{
		AfxMessageBox("Failed to create a sending client", MB_OK | MB_ICONSTOP);
		return;
	}

	/********** Construct the content of the communication test command *********/
	char command[102];
	__int16 *c = (__int16 *)command;
	c[0] = FNT_NETTESTTEXT;

	memcpy(&(command[2]), content, content.GetLength());
	command[2 + content.GetLength()] = '\0';
	netcln.SendSvr(command, 102);

	/********** Update the "display list" *********/
	commandDisplayer.Append(content + _T("\r\n"));
	this->UpdateData(FALSE);
}
