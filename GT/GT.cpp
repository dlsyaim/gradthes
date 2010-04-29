
// GT.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "GT.h"
#include "MainFrm.h"

#include <GL/glut.h>
#include <GL/glaux.h>
#include <vector>

#include "GTDoc.h"
#include "GTView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IP_STRING "192.168.1.144"
#define TEST_IP_STRING "127.0.0.1"
#define LOCAL_PORT 9919
#define REMOTE_PORT 8818

// CGTApp

BEGIN_MESSAGE_MAP(CGTApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CGTApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CGTApp construction

CGTApp::CGTApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	//_CrtSetBreakAlloc(1099); 
}

// The one and only CGTApp object

CGTApp theApp;


// CGTApp initialization

BOOL CGTApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();
	//if (!AfxSocketInit())
	//{
	//	AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
	//	return FALSE;
	//}

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGTDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CGTView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);



	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	/*
	 * For we shouldn't always create a thread to receive the return messages from the server,
	 * we start up a thread here. However, we should set the port we listen firstly.
	 * LOCAL_PORT is a casual digit and can be changed through discussion.
	 */
	svr.port = LOCAL_PORT;
	if (!svr.StartSvr()) {
		AfxMessageBox(_T("The server for connection failed to start up"), MB_OK | MB_ICONWARNING);
	}


	/*
	 * We set up a globally unique socket client
	 */
	//while(cln.initCln(IP_STRING, REMOTE_PORT) == 0)
	//{
	//	Sleep(100);
	//}
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CGTApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CGTApp customization load/save methods

void CGTApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CGTApp::LoadCustomState()
{
}

void CGTApp::SaveCustomState()
{
}

CGTDoc* CGTApp::getDoc(void)
{
	// Get the position of the first document template
	POSITION pos = GetFirstDocTemplatePosition();
	// Do we have a valid template position?
	if (pos)
	{
		// Get a pointer to the document template
		CDocTemplate* pDocTemp = GetNextDocTemplate(pos);
		// Do we have a valid pointer?
		if (pDocTemp)
		{
			// Get the position of the first document
			POSITION dPos = pDocTemp->GetFirstDocPosition();
			// Do we have a valid document position?
			if (dPos)
			{
				// Get a pointer to the document
				CGTDoc* pDocWnd = (CGTDoc*)pDocTemp->GetNextDoc(dPos);
				// Do we have a valid pointer?
				if (pDocWnd)
					return pDocWnd;
			}
		}
	}	
	return NULL;
}

// CGTApp message handlers



