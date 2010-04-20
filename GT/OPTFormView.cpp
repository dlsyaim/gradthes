// OPTFormView.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "OPTFormView.h"
#include "GTDoc.h"
#include "Singleton.h"
#include "MsgType.h"
// COPTFormView

IMPLEMENT_DYNCREATE(COPTFormView, CFormView)

COPTFormView::COPTFormView()
	: CFormView(COPTFormView::IDD)
	, phi(0)
	, theta(0)
	, psi(0)
	, N_Speed(0)
	, E_Speed(0)
	, D_Speed(0)
	, N_Acc(0)
	, E_Acc(0)
	, D_Acc(0)
{

}

COPTFormView::~COPTFormView()
{
}

void COPTFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OPT_ROLL_ANGLE_EDIT, phi);
	DDX_Text(pDX, IDC_OPT_PITCHANGLE_EDIT, theta);
	DDX_Text(pDX, IDC_OPT_HEADINGANGLE_EDIT, psi);
	DDX_Text(pDX, IDC_OPT_BODY_X_VEL_EDIT, N_Speed);
	DDX_Text(pDX, IDC_OPT_BODY_Y_VEL_EDIT, E_Speed);
	DDX_Text(pDX, IDC_OPT_BODY_Z_VEL_EDIT, D_Speed);
	DDX_Text(pDX, IDC_OPT_BODY_X_ACC_EDIT, N_Acc);
	DDX_Text(pDX, IDC_OPT_BODY_Y_ACC_EDIT, E_Acc);
	DDX_Text(pDX, IDC_OPT_BODY_Z_ACC_EDIT, D_Acc);
}

BEGIN_MESSAGE_MAP(COPTFormView, CFormView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_OPT_TEST_START, &COPTFormView::OnBnClickedOPTTestStart)
	ON_BN_CLICKED(IDC_OPT_TEST_STOP, &COPTFormView::OnBnClickedOPTTestStop)
	ON_BN_CLICKED(IDC_OPT_TEST_PASS, &COPTFormView::OnBnClickedOPTTestPass)
	ON_BN_CLICKED(IDC_OPT_TEST_FAILURE, &COPTFormView::OnBnClickedOPTTestFailure)
	ON_MESSAGE(OPT_TEST_REPLY_MSG, &OnReplyMsgArrived)
END_MESSAGE_MAP()


// COPTFormView 诊断

#ifdef _DEBUG
void COPTFormView::AssertValid() const
{
	CFormView::AssertValid();
}
CGTDoc* COPTFormView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGTDoc)));
	return (CGTDoc*)m_pDocument;
}


#ifndef _WIN32_WCE
void COPTFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// COPTFormView 消息处理程序

int COPTFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	GetDocument()->optView = this;

	return 0;
}

void COPTFormView::OnBnClickedOPTTestStart()
{
	/********** Construct the content of the IMU test command *********/
	char command[2];
	__int16 *c = (__int16 *)command;
	c[0] = TOT_OPTTRACETEST_START;	
	
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	cln->SendSvr(command, 2);
}

void COPTFormView::OnBnClickedOPTTestStop()
{
	/********** Construct the content of the IMU test command *********/
	char command[2];
	__int16 *c = (__int16 *)command;
	c[0] = TOT_OPTTRACETEST_STOP;	
	
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	cln->SendSvr(command, 2);
}

void COPTFormView::OnBnClickedOPTTestPass()
{
	/***** Set the global flag variable *****/
	CSingleton *instance = CSingleton::getInstance();
	instance->setIsOPTTestPass(FALSE);
}

void COPTFormView::OnBnClickedOPTTestFailure()
{
	/***** Set the global flag variable *****/
	CSingleton *instance = CSingleton::getInstance();
	instance->setIsOPTTestPass(FALSE);
}

void COPTFormView::updateData (pOPTTRACETestData d)
{
	phi = d->phi;
	psi = d->psi;
	theta = d->theta;

	N_Speed = d->N_Speed;
	E_Speed = d->E_Speed;
	D_Speed = d->D_Speed;

	N_Acc = d->N_Acc;
	E_Acc = d->E_Acc;
	D_Acc = d->D_Acc;

	//UpdateData(FALSE);
}

LRESULT COPTFormView::OnReplyMsgArrived(WPARAM w, LPARAM l)
{
	//// The message returns
	//const CNetSvrHeli* svr = ((CGTApp*)AfxGetApp())->getSvr();
	//returnMessageDisplayer.Append((char *)svr->recvbuf + 2);
	//returnMessageDisplayer.Append(_T("\r\n"));
	//this->UpdateData(FALSE);
	//return TRUE;
	UpdateData(FALSE);
	return TRUE;
}

