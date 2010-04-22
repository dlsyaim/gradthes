#include "stdafx.h"
#include "TabPageSSL.h"
#include "func\NetCln.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Construction

CTabPageSSL::CTabPageSSL () {
#ifndef _AFX_NO_OCC_SUPPORT
	AfxEnableControlContainer ();
#endif // !_AFX_NO_OCC_SUPPORT
	m_bRouteCommand = false;
	m_bRouteCmdMsg = false;
	m_bRouteNotify = false;	
}

CTabPageSSL::CTabPageSSL (UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent) {
#ifndef _AFX_NO_OCC_SUPPORT
	AfxEnableControlContainer ();
#endif // !_AFX_NO_OCC_SUPPORT
	m_bRouteCommand = false;
	m_bRouteCmdMsg = false;
	m_bRouteNotify = false;
}

/////////////////////////////////////////////////////////////////////////////
// Destruction

CTabPageSSL::~CTabPageSSL () {
}

/////////////////////////////////////////////////////////////////////////////
// Message Handlers

void CTabPageSSL::OnOK (void) {
	//
	// Prevent CDialog::OnOK from calling EndDialog.
	//
}

void CTabPageSSL::OnCancel (void) {
	//
	// Prevent CDialog::OnCancel from calling EndDialog.
	//
}

BOOL CTabPageSSL::OnCommand (WPARAM wParam, LPARAM lParam) {
	// Call base class OnCommand to allow message map processing
	BOOL bReturn = CDialog::OnCommand (wParam, lParam);

	if (true == m_bRouteCommand)
	{
		//
		// Forward WM_COMMAND messages to the dialog's parent.
		//
		return GetParent ()->SendMessage (WM_COMMAND, wParam, lParam);
	}

	return bReturn;
}

BOOL CTabPageSSL::OnNotify (WPARAM wParam, LPARAM lParam, LRESULT* pResult) {
	BOOL bReturn = CDialog::OnNotify(wParam, lParam, pResult);

	if (true == m_bRouteNotify)
	{
		//
		// Forward WM_NOTIFY messages to the dialog's parent.
		//
		return GetParent ()->SendMessage (WM_NOTIFY, wParam, lParam);
	}

	return bReturn;
}

BOOL CTabPageSSL::OnCmdMsg (UINT nID, int nCode, void* pExtra,
	AFX_CMDHANDLERINFO* pHandlerInfo) {
	BOOL bReturn = CDialog::OnCmdMsg (nID, nCode, pExtra, pHandlerInfo);

#ifndef _AFX_NO_OCC_SUPPORT
	if (true == m_bRouteCmdMsg)
	{
		//
		// Forward ActiveX control events to the dialog's parent.
		//
		if (nCode == CN_EVENT)
			return GetParent ()->OnCmdMsg (nID, nCode, pExtra, pHandlerInfo);
	}
#endif // !_AFX_NO_OCC_SUPPORT

	return bReturn;
}

void CTabPageSSL::sendTestData(double value)
{
	/********** Construct the content of the servo actor demarcated command *********/
	/***** Attention 10 is not enough *****/
	char command[sizeof(ServoActorTstInsData) + 2];
	__int16 *c = (__int16 *)command;
	c[0] = SAT_SERVOACTOR_TST;

	ServoActorTstInsData satid;
	satid.ActorSerial = getActorSerial();
	satid.SetPWM = (float)value;

	memcpy(&(command[2]), (char*)&satid, sizeof(satid));
	if (!cln)
		AfxMessageBox(_T("No client"), MB_OK | MB_ICONSTOP);
	else
		cln->SendSvr(command, sizeof(command));
}

__int8 CTabPageSSL::getActorSerial(void)
{
	return 0;
}
