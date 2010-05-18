// IMUTestFormView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GT.h"
#include "IMUTestFormView.h"
#include "GTDoc.h"
#include "Singleton.h"
#include "MsgType.h"

// CIMUTestFormView

#ifndef PI
#define PI 3.14159265359
#endif

IMPLEMENT_DYNCREATE(CIMUTestFormView, CFormView)

CIMUTestFormView::CIMUTestFormView()
	: CFormView(CIMUTestFormView::IDD)
	, headingAngle(0)
	, pitchAngle(0)
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
	DDX_Text(pDX, IDC_HEADING_ANGLE_EDIT, headingAngle);
	DDX_Text(pDX, IDC_PITCH_ANGLE_EDIT, pitchAngle);
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
	ON_MESSAGE(IMU_TEST_REPLY_MSG, &CIMUTestFormView::OnTestDataReply)
END_MESSAGE_MAP()


// CIMUTestFormView ���

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


// CIMUTestFormView ��Ϣ��������

int CIMUTestFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	GetDocument()->IMUView = this;

	return 0;
}

void CIMUTestFormView::OnBnClickedIMUTestStart()
{
	/********** Construct the content of the IMU test command *********/
	char command[2];
	__int16 *c = (__int16 *)command;
	c[0] = TIT_IMUTEST_START;	
	
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	cln->SendSvr(command, 2);
}

void CIMUTestFormView::OnBnClickedIMUTestPass()
{
	/***** Set the global state variable *****/
	CSingleton *instance = CSingleton::getInstance();
	instance->setIsIMUTestPass(TRUE);
}

void CIMUTestFormView::OnBnClickedIMUTestFailure()
{
	/***** Set the global state variable *****/
	CSingleton *instance = CSingleton::getInstance();
	instance->setIsIMUTestPass(FALSE);
}

void CIMUTestFormView::OnBnClickedIMUTestStop()
{
	/********** Construct the content of the IMU test command *********/
	char command[2];
	__int16 *c = (__int16 *)command;
	c[0] = TIT_IMUTEST_STOP;	

	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	cln->SendSvr(command, 2);
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
	pitchAngle = itd->psi;
	headingAngle = itd->theta;
}


LRESULT CIMUTestFormView::OnTestDataReply(WPARAM w, LPARAM l)
{
	//UpdateData(FALSE);
	CString str;
	CEdit* m_pEdit;
	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_HEADING_ANGLE_EDIT));
	str.Format("%.4g", headingAngle / PI * 180.0f);
	m_pEdit->SetWindowText(str);

	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_PITCH_ANGLE_EDIT));
	str.Format("%.4g", pitchAngle / PI * 180.0f);
	m_pEdit->SetWindowText(str);

	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_ROLL_ANGLE_EDIT));
	str.Format("%.4g", rollAngle / PI * 180.0f);
	m_pEdit->SetWindowText(str);

	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_BODY_X_VEL_EDIT));
	str.Format("%.4g", n_x_Vel);
	m_pEdit->SetWindowText(str);

	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_BODY_Y_VEL_EDIT));
	str.Format("%.4g", e_y_Vel);
	m_pEdit->SetWindowText(str);

	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_BODY_Z_VEL_EDIT));
	str.Format("%.4g", d_z_Vel);
	m_pEdit->SetWindowText(str);

	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_BODY_X_ACC_EDIT));
	str.Format("%.4g", n_x_Acc);
	m_pEdit->SetWindowText(str);

	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_BODY_Y_ACC_EDIT));
	str.Format("%.4g", e_y_Acc);
	m_pEdit->SetWindowText(str);

	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_BODY_Z_ACC_EDIT));
	str.Format("%.4g", d_z_Acc);
	m_pEdit->SetWindowText(str);


	return TRUE;
}