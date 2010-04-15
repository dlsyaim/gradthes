// IMUTestFormView.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "IMUTestFormView.h"
#include "GTDoc.h"
#include "GlobalExperimentData.h"

// CIMUTestFormView

IMPLEMENT_DYNCREATE(CIMUTestFormView, CFormView)

CIMUTestFormView::CIMUTestFormView()
	: CFormView(CIMUTestFormView::IDD)
	//, rollAngle(0)
	//, rollAngleVel(0)
	, headingAngle(0)
	//, pitchAngleVel(0)
	, pitchAngle(0)
	//, headingAngleVel(0)
	, rollAngle(0)
	, n_x_Vel(0)
	, e_y_Vel(0)
	, d_z_Vel(0)
	, n_x_Acc(0)
	, e_y_Acc(0)
	, d_z_Acc(0)
{
	
}

CIMUTestFormView::~CIMUTestFormView()
{
}

void CIMUTestFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_ROLL_ANGLE_EDIT, rollAngle);
	//DDX_Text(pDX, IDC_ROLLANGLEVEL_EDIT, rollAngleVel);
	DDX_Text(pDX, IDC_HEADINGANGLE_EDIT, headingAngle);
	//DDX_Text(pDX, IDC_PITCHANGLEVEL_EDIT, pitchAngleVel);
	DDX_Text(pDX, IDC_PITCHANGLE_EDIT, pitchAngle);
	//DDX_Text(pDX, IDC_HEADINGANGLEVEL_EDIT, headingAngleVel);
	DDX_Text(pDX, IDC_ROLL_ANGLE_EDIT, rollAngle);
	DDX_Text(pDX, IDC_BODY_X_VEL_EDIT, n_x_Vel);
	DDX_Text(pDX, IDC_BODY_Y_VEL_EDIT, e_y_Vel);
	DDX_Text(pDX, IDC_BODY_Z_VEL_EDIT, d_z_Vel);
	DDX_Text(pDX, IDC_BODY_X_ACC_EDIT, n_x_Acc);
	DDX_Text(pDX, IDC_BODY_Y_ACC_EDIT, e_y_Acc);
	DDX_Text(pDX, IDC_BODY_Z_ACC_EDIT, d_z_Acc);
}

BEGIN_MESSAGE_MAP(CIMUTestFormView, CFormView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_IMU_TEST_START, &CIMUTestFormView::OnBnClickedIMUTestStart)
	ON_BN_CLICKED(IDC_IMU_TEST_PASS, &CIMUTestFormView::OnBnClickedIMUTestPass)
	ON_BN_CLICKED(IDC_IMU_TEST_STOP, &CIMUTestFormView::OnBnClickedIMUTestStop)
	ON_BN_CLICKED(IDC_IMU_TEST_FAILURE, &CIMUTestFormView::OnBnClickedIMUTestFailure)
END_MESSAGE_MAP()


// CIMUTestFormView 诊断

#ifdef _DEBUG
void CIMUTestFormView::AssertValid() const
{
	CFormView::AssertValid();
}

CGTDoc* CIMUTestFormView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGTDoc)));
	return (CGTDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CIMUTestFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIMUTestFormView 消息处理程序

int CIMUTestFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	GetDocument()->IMUView = this;

	/***** Initialize *****/
	//// The server address
	//char *IP = "192.168.0.186";
	//// Initializing
	//if(netcln.initCln(IP, 22222) == 0)
	//{
	//	TRACE("Can't create a sending client\n");
	//}

	return 0;
}

void CIMUTestFormView::OnBnClickedIMUTestStart()
{
	/********** Construct the content of the communication test command *********/
	char command[2];
	__int16 *c = (__int16 *)command;
	c[0] = TIT_IMUTEST_START;	
	//netcln.SendSvr(command, 2);
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	cln->SendSvr(command, 2);
}

void CIMUTestFormView::OnBnClickedIMUTestPass()
{
	/***** Set the global flag variable *****/
	GlobalExperimentData::isIMUTestPass = TRUE;
}

void CIMUTestFormView::OnBnClickedIMUTestStop()
{
	/********** Construct the content of the communication test command *********/
	char command[2];
	__int16 *c = (__int16 *)command;
	c[0] = TIT_IMUTEST_STOP;	
	//netcln.SendSvr(command, 2);

	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	cln->SendSvr(command, 2);
}

void CIMUTestFormView::OnBnClickedIMUTestFailure()
{
	/***** Set the global flag variable *****/
	GlobalExperimentData::isIMUTestPass = FALSE;

}

void CIMUTestFormView::updateData(IMUTestData *itd)
{
	/***** Update the form view *****/
	n_x_Vel = itd->N_Speed;
	e_y_Vel = itd->E_Speed;
	d_z_Vel = itd->D_Speed;

	n_x_Acc = itd->N_Acc;
	e_y_Acc = itd->E_Acc;
	d_z_Acc = itd->D_Acc;
	rollAngle = itd->phi;
	//rollAngleVel = itd->phi_Acc;

	pitchAngle = itd->psi;
	//pitchAngleVel = itd->psi_Acc;

	headingAngle = itd->theta;
	//headingAngleVel = itd->theta_Acc;

	UpdateData(FALSE);
}
