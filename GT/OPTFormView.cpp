// OPTFormView.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "OPTFormView.h"
#include "GTDoc.h"
#include "Singleton.h"
#include "MsgType.h"
// COPTFormView

#ifndef PI
#define PI 3.14159265359
#endif

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
	, opt_n_coord(0)
	, opt_e_coord(0)
	, opt_d_coord(0)
	, opt_roll_vel(0)
	, opt_pitch_vel(0)
	, opt_head_vel(0)
{

}

COPTFormView::~COPTFormView()
{
}

void COPTFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OPT_ROLL_ANGLE_EDIT, phi);
	DDX_Text(pDX, IDC_OPT_PITCH_ANGLE_EDIT, theta);
	DDX_Text(pDX, IDC_OPT_HEADING_ANGLE_EDIT, psi);
	DDX_Text(pDX, IDC_OPT_BODY_X_VEL_EDIT, N_Speed);
	DDX_Text(pDX, IDC_OPT_BODY_Y_VEL_EDIT, E_Speed);
	DDX_Text(pDX, IDC_OPT_BODY_Z_VEL_EDIT, D_Speed);
	DDX_Text(pDX, IDC_OPT_BODY_X_ACC_EDIT, N_Acc);
	DDX_Text(pDX, IDC_OPT_BODY_Y_ACC_EDIT, E_Acc);
	DDX_Text(pDX, IDC_OPT_BODY_Z_ACC_EDIT, D_Acc);
	DDX_Text(pDX, IDC_OPT_X_COOR, opt_n_coord);
	DDX_Text(pDX, IDC_OPT_Y_COOR, opt_e_coord);
	DDX_Text(pDX, IDC_OPT_Z_COOR, opt_d_coord);
	DDX_Text(pDX, IDC_OPT_ROLL_VEL, opt_roll_vel);
	DDX_Text(pDX, IDC_OPT_PITCH_VEL, opt_pitch_vel);
	DDX_Text(pDX, IDC_OPT_HEAD_VEL, opt_head_vel);
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
	instance->setIsOPTTestPass(TRUE);
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

	opt_n_coord = d->N_Pos;
	opt_e_coord = d->E_Pos;
	opt_d_coord = d->D_Pos;

	opt_roll_vel = d->phi_Acc;
	opt_pitch_vel = d->theta_Acc;
	opt_head_vel = d->psi_Acc;

}

LRESULT COPTFormView::OnReplyMsgArrived(WPARAM w, LPARAM l)
{
	//UpdateData(FALSE);
	CString str;
	CEdit *m_pEdit;

	str.Format("%.4g", phi / PI * 180.0f);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_OPT_ROLL_ANGLE_EDIT));
	m_pEdit->SetWindowText(str);

	str.Format("%.4g", theta / PI * 180.0f);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_OPT_PITCH_ANGLE_EDIT));
	m_pEdit->SetWindowText(str);

	str.Format("%.4g", psi / PI * 180.0f);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_OPT_HEADING_ANGLE_EDIT));
	m_pEdit->SetWindowText(str);

	str.Format("%.4g", N_Speed);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_OPT_BODY_X_VEL_EDIT));
	m_pEdit->SetWindowText(str);

	str.Format("%.4g", E_Speed);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_OPT_BODY_Y_VEL_EDIT));
	m_pEdit->SetWindowText(str);

	str.Format("%.4g", D_Speed);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_OPT_BODY_Z_VEL_EDIT));
	m_pEdit->SetWindowText(str);

	str.Format("%.4g", N_Acc);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_OPT_BODY_X_ACC_EDIT));
	m_pEdit->SetWindowText(str);

	str.Format("%.4g", E_Acc);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_OPT_BODY_Y_ACC_EDIT));
	m_pEdit->SetWindowText(str);

	str.Format("%.4g", D_Acc);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_OPT_BODY_Z_ACC_EDIT));
	m_pEdit->SetWindowText(str);

	str.Format("%.4g", opt_n_coord);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_OPT_X_COOR));
	m_pEdit->SetWindowText(str);

	str.Format("%.4g", opt_e_coord);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_OPT_Y_COOR));
	m_pEdit->SetWindowText(str);

	str.Format("%.4g", opt_d_coord);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_OPT_Z_COOR));
	m_pEdit->SetWindowText(str);

	str.Format("%.4g", opt_roll_vel);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_OPT_ROLL_VEL));
	m_pEdit->SetWindowText(str);

	str.Format("%.4g", opt_pitch_vel);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_OPT_PITCH_VEL));
	m_pEdit->SetWindowText(str);

	str.Format("%.4g", opt_head_vel);
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_OPT_HEAD_VEL));
	m_pEdit->SetWindowText(str);
	return TRUE;
}

