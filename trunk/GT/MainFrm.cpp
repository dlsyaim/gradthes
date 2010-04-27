
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "GT.h"
#include <gl/glut.h>
#include <vector>
#include <fstream>
#include "ST_SplitterWnd.h"
#include "MainFrm.h"
#include "HelicopterChoosingDialog.h"
#include "CommunicationTestDialog.h"
#include "ServoActorDemarcateDialog.h"
#include "RotorDiskDemarcateDialog.h"
#include "PIDCPDialog.h"
#include "LeftView.h"
#include "UpperRightView.h"
#include "GTView.h"
#include "GridView.h"
#include "IMUTestFormView.h"
#include "DPLeftFormView.h"
#include "DPUpperRightView.h"
#include "OPTFormView.h"
#include "GSDefinition.h"
#include "Singleton.h"

/*
 * 48000 is an estimated number
 */
#define ID_HELICOPTER_BEGIN 48000

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND(ID_NEW_HELICOPTER_MODEL, &CMainFrame::OnNewModel)
	ON_COMMAND(ID_HELICOPTER_BEGIN + 0, OnZeroModel)
	ON_COMMAND(ID_HELICOPTER_BEGIN + 1, OnFirstModel)
	ON_COMMAND(ID_HELICOPTER_BEGIN + 2, OnSecondModel)
	ON_COMMAND(ID_HELICOPTER_BEGIN + 3, OnThirdModel)
	ON_COMMAND(ID_HELICOPTER_BEGIN + 4, OnForthModel)
	ON_COMMAND(ID_32793, &CMainFrame::On32793)
	ON_WM_DESTROY()
	ON_COMMAND(ID_COMMUNICATION_TEST, &CMainFrame::OnCommunicationTest)
	ON_COMMAND(ID_SERVOACTOR_DEMARCATE, &CMainFrame::OnServoActorDemarcate)
	ON_COMMAND(ID_GYRO_TEST, &CMainFrame::OnGyroTest)
	ON_COMMAND(ID_FLIGHT_PATH_SET, &CMainFrame::OnFlightPathSet)
	ON_COMMAND(ID_READ_CONFIGURATION, &CMainFrame::OnReadConfiguration)
	ON_COMMAND(ID_SAVE_CONFIGURATION, &CMainFrame::OnSaveConfiguration)
	ON_COMMAND(ID_SAVE_AS_CONFIGURATION, &CMainFrame::OnSaveAsConfiguration)
	ON_COMMAND(ID_CONTROL_PARAMETER, &CMainFrame::OnControlParameter)
	ON_COMMAND(ID_FLIGHT_EXPERIMENT, &CMainFrame::OnFlightExperiment)
	ON_COMMAND(ID_DATA_PROCESS, &CMainFrame::OnDataProcess)
	ON_COMMAND(ID_OPT_TEST, &CMainFrame::OnOptTest)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// add member initialization code here
	numberOfMenu = 0;

	popUpMenu = NULL;

}

CMainFrame::~CMainFrame()
{
	if (popUpMenu)
		delete popUpMenu;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// Allow user-defined toolbars operations:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these five lines if you don't want the toolbar and menubar to be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);	
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Enable toolbar and docking window menu replacement
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// enable quick (Alt+drag) toolbar customization
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// load user-defined toolbar images
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			m_UserImages.SetImageSize(CSize(16, 16), FALSE);
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// enable menu personalization (most-recently used commands)
	// TODO: define your own basic commands, ensuring that each pulldown menu has at least one basic command.
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	
	//lstBasicCommands.AddTail(ID_AHRS_START);

	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	// Read the helicopter names from Registry
	readHMFromRegistry();
	// Create the recent helicopter model name menu items
	createRecentHMMenuItems();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// base class does the real work

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// enable customization button for all user toolbars
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


void CMainFrame::OnNewModel()
{
	// New a dialog
	CSingleton* instance = CSingleton::getInstance();
	CHelicopterChoosingDialog *mcd = new CHelicopterChoosingDialog(this, TRUE, instance->getHelicopterModel());
	switch (mcd->DoModal()) {
		case IDOK:
			// First add the helicopter name string
			AddName(mcd->m_bodyTab.helicopterName);
			// Then update menu items
			UpdateMenu();
			// Set the window's title
			this->SetWindowText(instance->getCurPHM()->helicopterName);
			break;
		case IDCANCEL:
			break;
		default:
			break;
	}	
}

// Deprecated
void CMainFrame::AddMenu(CString message)
{
	CMenu* mainMenu = CMenu::FromHandle(m_wndMenuBar.GetDefaultMenu());
	if (mainMenu != NULL) {
		CMenu *subMenu = NULL, *popUpMenu = NULL;

		// Iterate the main menu
		int menuCount = mainMenu->GetMenuItemCount();
		int i;
		for (i = 0; i < menuCount; i++) {
			CString menuName;
			if (mainMenu->GetMenuString(i, menuName, MF_BYPOSITION) && menuName == "����ѡ��") {
				subMenu = mainMenu->GetSubMenu(i);
				break;
			}
		}

		for (i = 0; i < (int)subMenu->GetMenuItemCount(); i++) {
			CString menuName;
			if (subMenu->GetMenuString(i, menuName, MF_BYPOSITION) && menuName == "���ģ��") {
				popUpMenu = subMenu->GetSubMenu(i);
				break;
			}
		}
		if (popUpMenu != NULL) {
			if (popUpMenu->AppendMenu(MF_STRING,  ID_HELICOPTER_BEGIN, message) ){
				m_wndMenuBar.CreateFromMenu(mainMenu->GetSafeHmenu(), TRUE, TRUE);
			}
		}
	}		
}

void CMainFrame::UpdateMenu(void)
{
	CMenu* mainMenu = CMenu::FromHandle(m_wndMenuBar.GetDefaultMenu());
	if (mainMenu != NULL) {
		CMenu *subMenu = NULL;
		//CMenu *popUpMenu = NULL;
		MENUITEMINFO info;
		info.cbSize = sizeof (MENUITEMINFO); // Must fill up this field
		info.fMask = MIIM_SUBMENU;

		// Iterate the main menu
		int menuCount = mainMenu->GetMenuItemCount();
		int i;
		for (i = 0; i < menuCount; i++) {
			CString menuName;
			if (mainMenu->GetMenuString(i, menuName, MF_BYPOSITION) && menuName == "����ѡ��") {
				subMenu = mainMenu->GetSubMenu(i);
				break;
			}
		}

		for (i = 0; i < (int)subMenu->GetMenuItemCount(); i++) {
			CString menuName;
			if (subMenu->GetMenuString(i, menuName, MF_BYPOSITION) && menuName == "�����ģ��") {
				subMenu->GetMenuItemInfo(i, &info, TRUE);
				popUpMenu = CMenu::FromHandle(info.hSubMenu);
				break;
			}
		}
		// Adding
		if (!popUpMenu) {
			popUpMenu = new CMenu();
			popUpMenu->CreateMenu();
			info.hSubMenu = popUpMenu->GetSafeHmenu();			
		}
		if (popUpMenu != NULL) {
			//Appending
			if (numberOfMenu < MAX_NUM_HELICOPTER_NAME) {
				if (popUpMenu->AppendMenu(MF_STRING, ID_HELICOPTER_BEGIN + numberOfMenu, "TEMP") ){					
					numberOfMenu++;
			    }
			}

			// Renaming
			for (int j = 0; j < (int)popUpMenu->GetMenuItemCount(); j++ ) {
				popUpMenu->ModifyMenu(ID_HELICOPTER_BEGIN + j, MF_BYCOMMAND, ID_HELICOPTER_BEGIN + j, helicopterNames[j]);					
			}
			// Updating
			subMenu->SetMenuItemInfo(i, &info, TRUE);
			m_wndMenuBar.CreateFromMenu(mainMenu->GetSafeHmenu(), TRUE, TRUE);
		}
	}	
}

void CMainFrame::AddName(CString name)
{
	// Firstly check if name exists
	DeleteName(name);
	// Secondly make room for the newly arrived name
	for (int i = MAX_NUM_HELICOPTER_NAME - 1; i > 0; i--) {
		helicopterNames[i] = helicopterNames[i - 1];
	}

	// Thirdly ...
	helicopterNames[0] = name;
}

void CMainFrame::DeleteName(CString name)
{
	int i; 
	// First find it
	for (i = 0; i < MAX_NUM_HELICOPTER_NAME; i++) {
		if (helicopterNames[i] == name) 
			break;
	}
	// Then delete it
	for (int j = i; j < MAX_NUM_HELICOPTER_NAME - 1; j++) {
		helicopterNames[j] = helicopterNames[j + 1];
	}
}

void CMainFrame::OnZeroModel(void)
{
	OnSelectModel(0);
}

void CMainFrame::OnFirstModel(void)
{
	OnSelectModel(1);
}

void CMainFrame::OnSecondModel(void)
{
	OnSelectModel(2);
}

void CMainFrame::OnThirdModel(void)
{
	OnSelectModel(3);
}

void CMainFrame::OnForthModel(void)
{
	OnSelectModel(4);
}

// Select the created helicopter model according to the index
void CMainFrame::OnSelectModel(int idx)
{
	if (idx < 0 && idx > 4) 
		return;

	CString name = helicopterNames[idx];
	/*
	 * All the helicopter models are saved into one single file
	 */
	
	CSingleton* instance = CSingleton::getInstance();
	PHelicopterModel pHM = instance->getHelicopterModel(FALSE, name);
	if (!pHM) {
		DeleteName(name);
		DeleteMenu(name);
		CString meg;
		meg.Format("No such a model: %s\n", name);
		AfxMessageBox((LPCTSTR)meg, MB_OK | MB_ICONSTOP);
		return;
	} else {
		CHelicopterChoosingDialog *hcd = new CHelicopterChoosingDialog(this, FALSE, pHM);
		switch (hcd->DoModal()) {
			case IDOK:
				// First add the helicopter name string
				AddName(hcd->m_bodyTab.helicopterName);
				// Then update menu items
				UpdateMenu();
				// Set the window's titles
				this->SetWindowText(pHM->helicopterName);
				break;
			case IDCANCEL:
				break;
			default:
				break;
		}
	}
}

void CMainFrame::DeleteMenu(CString name)
{
	CMenu* mainMenu = CMenu::FromHandle(m_wndMenuBar.GetDefaultMenu());
	if (mainMenu != NULL) {
		CMenu *subMenu = NULL;
		CMenu *popUpMenu = NULL;
		MENUITEMINFO info;
		info.cbSize = sizeof (MENUITEMINFO); // Must fill up this field
		info.fMask = MIIM_SUBMENU;

		// Iterate the main menu
		int menuCount = mainMenu->GetMenuItemCount();
		int i;
		for (i = 0; i < menuCount; i++) {
			CString menuName;
			if (mainMenu->GetMenuString(i, menuName, MF_BYPOSITION) && menuName == "����ѡ��") {
				subMenu = mainMenu->GetSubMenu(i);
				break;
			}
		}

		for (i = 0; i < (int)subMenu->GetMenuItemCount(); i++) {
			CString menuName;
			if (subMenu->GetMenuString(i, menuName, MF_BYPOSITION) && menuName == "�����ģ��") {
				subMenu->GetMenuItemInfo(i, &info, TRUE);
				popUpMenu = CMenu::FromHandle(info.hSubMenu);
				break;
			}
		}
		if (popUpMenu != NULL) {
			int pos = FindMenuItem(popUpMenu, name);
			// Delete all the items starting from pos
			int j;
			int originCount = popUpMenu->GetMenuItemCount();
			for (j = pos; j < originCount; j++) {
				// Note that the first parameter must be pos
				popUpMenu->DeleteMenu(pos, MF_BYPOSITION);
			}
			// Appending
			for (j = pos; j < numberOfMenu - 1; j++) {
				popUpMenu->AppendMenu(MF_STRING, ID_HELICOPTER_BEGIN + j, helicopterNames[j]);					
			}
			numberOfMenu--;
			
			// Updating
			subMenu->SetMenuItemInfo(i, &info, TRUE);
			m_wndMenuBar.CreateFromMenu(mainMenu->GetSafeHmenu(), TRUE, TRUE);
		}
	}	
}

int CMainFrame::FindMenuItem(CMenu* Menu, LPCTSTR MenuString)
{
	 ASSERT(Menu);
     ASSERT(::IsMenu(Menu->GetSafeHmenu()));

     int count = Menu->GetMenuItemCount();
     for (int i = 0; i < count; i++)
    {
		CString str;
        if (Menu->GetMenuString(i, str, MF_BYPOSITION) && str.Compare(MenuString) == 0)
         return i;
     }

     return -1;
}

void CMainFrame::On32793()
{
	RotorDiskDemarcateDialog rddd;
	rddd.DoModal();
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	m_pSplitterWnd = new ST_SplitterWnd();
	// First split the window vertically
	m_pSplitterWnd->Create(this, NULL, NULL, pContext, true);
	// Add views
	m_pSplitterWnd->AddView(LEFT_SIDE, RUNTIME_CLASS(CGridView), pContext);
	m_pSplitterWnd->AddView(LEFT_SIDE, RUNTIME_CLASS(CIMUTestFormView), pContext);
	m_pSplitterWnd->AddView(LEFT_SIDE, RUNTIME_CLASS(CLeftView), pContext);
	m_pSplitterWnd->AddView(LEFT_SIDE, RUNTIME_CLASS(CDPLeftFormView), pContext);
	m_pSplitterWnd->AddView(LEFT_SIDE, RUNTIME_CLASS(COPTFormView), pContext);
	
	// Then split the right side horizontally
	m_pSplitterWnd1 = m_pSplitterWnd->AddSubDivision(RIGHT_SIDE, NULL, NULL, pContext, false);
	// Add views
	m_pSplitterWnd1->AddView(TOP_SIDE, RUNTIME_CLASS(CUpperRightView), pContext);
	m_pSplitterWnd1->AddView(TOP_SIDE, RUNTIME_CLASS(CDPUpperRightView), pContext);
	m_pSplitterWnd1->AddView(BOTTOM_SIDE, RUNTIME_CLASS(CGTView), pContext);

	m_pSplitterWnd1->SetInitialStatus();
	m_pSplitterWnd->SetInitialStatus();

	if (!m_pSplitterWnd1->IsSideHidden(TOP_SIDE))
		m_pSplitterWnd1->ToggleSide(TOP_SIDE);
	if (m_pSplitterWnd1->IsSideHidden(BOTTOM_SIDE))
		m_pSplitterWnd1->ToggleSide(BOTTOM_SIDE);
	
	/***** This line of code must be placed here not somewhere above *****/
	if (!m_pSplitterWnd->IsSideHidden(LEFT_SIDE))
		m_pSplitterWnd->ToggleSide(LEFT_SIDE);

	return TRUE;
}


void CMainFrame::readHMFromRegistry(void)
{
	// This variable will allow us to keep track of the KEY
	HKEY hk;
	// This variable will be used to hold the type of value
	DWORD dwType;
	// This variable will represent the size of the value
	DWORD dwLength;
	// Check the HKEY_CURRENT_USER node and look for the RemHMCreated node under it
	// If it exists, open it
	RegOpenKeyEx(HKEY_CURRENT_USER,"RemHMCreated", 0, KEY_QUERY_VALUE, &hk);
	// Retrieve the value of the first helicopter model name
	unsigned char buf[256];
	char res[5];

	for (int i = 0 ; i < MAX_NUM_HELICOPTER_NAME; i++) {
		itoa(i,res,10);
		memset(buf, 0, 256);
		dwLength = 256;	
		RegQueryValueEx(hk, res, NULL, &dwType, (LPBYTE)buf, &dwLength);
		helicopterNames[i] = buf;
	}
	
	// We have finished reading the registry,
	// so free the resources we were using
	RegCloseKey(hk);
	return;
}

void CMainFrame::createRecentHMMenuItems(void)
{
	// No first means nothing
	if (helicopterNames[0].GetLength() == 0) {
		return;
	}

	CMenu* mainMenu = CMenu::FromHandle(m_wndMenuBar.GetDefaultMenu());
	if (mainMenu != NULL) {
		CMenu *subMenu = NULL;
		/*CMenu *popUpMenu = NULL;*/
		MENUITEMINFO info;
		info.cbSize = sizeof (MENUITEMINFO); // Must fill up this field
		info.fMask = MIIM_SUBMENU;             


		// Iterate the main menu
		int menuCount = mainMenu->GetMenuItemCount();
		int i;
		for (i = 0; i < menuCount; i++) {
			CString menuName;
			if (mainMenu->GetMenuString(i, menuName, MF_BYPOSITION) && menuName == "����ѡ��") {
				subMenu = mainMenu->GetSubMenu(i);
				break;
			}
		}

		for (i = 0; i < (int)subMenu->GetMenuItemCount(); i++) {
			CString menuName;
			if (subMenu->GetMenuString(i, menuName, MF_BYPOSITION) && menuName == "�����ģ��") {
				subMenu->GetMenuItemInfo(i, &info, TRUE);
				break;
			}
		}
		// Adding
		if (!info.hSubMenu) {
			popUpMenu = new CMenu();
			popUpMenu->CreateMenu();
			info.hSubMenu = popUpMenu->GetSafeHmenu();			
		}

		if (popUpMenu) {
			// Appending
			int j;
			for (j = 0; j < MAX_NUM_HELICOPTER_NAME; j++) {
				if (helicopterNames[j].GetLength() != 0) {
					if (popUpMenu->AppendMenu(MF_STRING, ID_HELICOPTER_BEGIN + j, "TEMP")){					
						numberOfMenu++;
					}
				}
			}
			// Renaming
			for (j = 0; j < (int)popUpMenu->GetMenuItemCount(); j++) {
				popUpMenu->ModifyMenu(ID_HELICOPTER_BEGIN + j, MF_BYCOMMAND, ID_HELICOPTER_BEGIN + j, helicopterNames[j]);					
			}
			// Updating
			subMenu->SetMenuItemInfo(i, &info, TRUE);
			m_wndMenuBar.CreateFromMenu(mainMenu->GetSafeHmenu(), TRUE, TRUE);
		}
	}
}
void CMainFrame::OnDestroy()
{
	CFrameWndEx::OnDestroy();

	/***** Here we must keep the helicopter names in the Registry *****/
	HKEY hk;
	DWORD dwDisp;
	// Check the HKEY_CURRENT_USER key and look for the RemHMCreated node under it
	// If you don't find it, then create it
	RegCreateKeyEx(HKEY_CURRENT_USER, "RemHMCreated", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hk, &dwDisp);
	// Store the first name in a key named 0
	// But first convert the CString into a null-terminated string
	
	unsigned char buf[256];
	char res[5];

	for (int i = 0; i < MAX_NUM_HELICOPTER_NAME ; i++) {	
		itoa(i,res,10);
		memcpy(buf, helicopterNames[i].GetBuffer(0), helicopterNames[i].GetLength());
		buf[helicopterNames[i].GetLength()] = '\0';
		RegSetValueEx(hk,res,0, REG_SZ,(PBYTE)buf, helicopterNames[i].GetLength() + 1);
	}
	

	if (m_pSplitterWnd)
		delete m_pSplitterWnd;
	if (m_pSplitterWnd1)
		delete m_pSplitterWnd1;

	// We have finished with the registry,
	// so liberate the resources we were using		
	RegCloseKey(hk);
}

void CMainFrame::OnCommunicationTest()
{
	CCommunicationTestDialog ctd;
	((CGTApp*)AfxGetApp())->setCtd(&ctd);
	ctd.DoModal();
}

void CMainFrame::OnServoActorDemarcate()
{
	CSingleton *instance = CSingleton::getInstance();
	if (!instance->getCurPHM())
	{
		AfxMessageBox(_T("Must choose a helicopter model first"), MB_OK | MB_ICONSTOP);
		return;
	}
	CServoActorDemarcateDialog sadd;
	switch (sadd.DoModal()) {
		case IDOK:
			break;
		case IDCANCEL:
			break;
		default:
			break;
	}
}

void CMainFrame::OnGyroTest()
{
	/***** First toggle on the left side, then switch to IMUTestFormView *****/
	if (m_pSplitterWnd->IsSideHidden(LEFT_SIDE))
		m_pSplitterWnd->ToggleSide(LEFT_SIDE);
	m_pSplitterWnd->SwitchToView(LEFT_SIDE, 1);

	/***** Then toggle off the upper right side *****/
	if (!m_pSplitterWnd1->IsSideHidden(TOP_SIDE)) {
		m_pSplitterWnd1->ToggleSide(TOP_SIDE);
	}

	/***** Inform GTView to draw the static 3D helicopter model *****/
	CGTView* pView = getLowerRightPane();	
	if (pView != NULL)  {
		pView->setRenderMode(CGTView::IMU_TEST);
	}
}

CGTView* CMainFrame::getLowerRightPane(void)
{
	CWnd* pWnd = NULL;
	CGTView* pView = NULL;
	if (m_pSplitterWnd1->IsSideHidden(TOP_SIDE)) {
		pWnd = m_pSplitterWnd1->GetPane(0, 0)/*.GetPane(0, 1)*/;
		pView = DYNAMIC_DOWNCAST(CGTView, pWnd);
	} else if (!m_pSplitterWnd1->IsSideHidden(BOTTOM_SIDE)) {
		pWnd = m_pSplitterWnd1->GetPane(1, 0);
		pView = DYNAMIC_DOWNCAST(CGTView, pWnd);		
	}
	return pView;	
}

void CMainFrame::OnFlightPathSet()
{
	/***** First toggle on the left side, switch to GridView *****/
	if (m_pSplitterWnd->IsSideHidden(LEFT_SIDE))
		m_pSplitterWnd->ToggleSide(LEFT_SIDE);
	m_pSplitterWnd->SwitchToView(LEFT_SIDE, 0);

	/***** Then toggle off the upper right side *****/
	if (!m_pSplitterWnd1->IsSideHidden(TOP_SIDE)) {
		m_pSplitterWnd1->ToggleSide(TOP_SIDE);
	}

	if (getLowerRightPane()) {
		getLowerRightPane()->setRenderMode(CGTView::FLIGHT_PATH_SET);
	}
}

void CMainFrame::OnReadConfiguration()
{
	/***** Open the configuration file *****/
	char strFilter[] = { "UNHE configuration files (*.uhc)|*.uhc| All files (*.*) | *.*|" };
	CFileDialog FileDlg(TRUE, ".uhc", NULL, 0, strFilter);
	if (FileDlg.DoModal() == IDOK) {
		CString fileName = FileDlg.GetFileName();
		TRACE(fileName);
		// Open it
	}
}

void CMainFrame::OnSaveConfiguration()
{
	
}

void CMainFrame::OnSaveAsConfiguration()
{
	char strFilter[] = { "UNHE configuration files (*.uhc)|*.uhc| All files (*.*) | *.*|" };
	CFileDialog FileDlg(FALSE, ".uhc", NULL, 0, strFilter);
	if (FileDlg.DoModal() == IDOK) {
		CString fileName = FileDlg.GetFileName();
		TRACE(fileName);
		// Save it
	}
}

void CMainFrame::OnControlParameter()
{
	CPIDCPDialog cpd;
	cpd.DoModal();
}

void CMainFrame::OnFlightExperiment()
{
	/***** First toggle on the left side, then switch to LeftView *****/
	if (m_pSplitterWnd->IsSideHidden(LEFT_SIDE))
		m_pSplitterWnd->ToggleSide(LEFT_SIDE);
	m_pSplitterWnd->SwitchToView(LEFT_SIDE, 2);

	/***** Then toggle on the upper right side, then switch to UpperRightView *****/
	if (m_pSplitterWnd1->IsSideHidden(TOP_SIDE)) 
		m_pSplitterWnd1->ToggleSide(TOP_SIDE);
	m_pSplitterWnd1->SwitchToView(TOP_SIDE, 0);
	

	if (m_pSplitterWnd1->IsSideHidden(BOTTOM_SIDE)) 
		m_pSplitterWnd1->ToggleSide(BOTTOM_SIDE);

	m_pSplitterWnd1->SwitchToView(BOTTOM_SIDE, 0);
	// Change the render mode
	if (getLowerRightPane())
		getLowerRightPane()->setRenderMode(CGTView::FLIGHT_EXPERIMENT);
}

void CMainFrame::OnDataProcess()
{
	/***** First toggle on the left side, then switch to LeftView *****/
	if (m_pSplitterWnd->IsSideHidden(LEFT_SIDE))
		m_pSplitterWnd->ToggleSide(LEFT_SIDE);
	m_pSplitterWnd->SwitchToView(LEFT_SIDE, 3);

	/***** Then toggle on the upper right side, then switch to LeftView *****/
	if (m_pSplitterWnd1->IsSideHidden(TOP_SIDE)) 
		m_pSplitterWnd1->ToggleSide(TOP_SIDE);
	m_pSplitterWnd1->SwitchToView(TOP_SIDE, 1);
	

	if (m_pSplitterWnd1->IsSideHidden(BOTTOM_SIDE)) 
		m_pSplitterWnd1->ToggleSide(BOTTOM_SIDE);

	m_pSplitterWnd1->SwitchToView(BOTTOM_SIDE, 0);

	// Change the render mode
	if (getLowerRightPane())
		getLowerRightPane()->setRenderMode(CGTView::DATA_PROCESS);
}

void CMainFrame::OnOptTest()
{
	/***** First toggle on the left side, then switch to IMUTestFormView *****/
	if (m_pSplitterWnd->IsSideHidden(LEFT_SIDE))
		m_pSplitterWnd->ToggleSide(LEFT_SIDE);
	m_pSplitterWnd->SwitchToView(LEFT_SIDE, 4);

	/***** Then toggle off the upper right side *****/
	if (!m_pSplitterWnd1->IsSideHidden(TOP_SIDE)) {
		m_pSplitterWnd1->ToggleSide(TOP_SIDE);
	}

	/***** Inform GTView to draw the static 3D helicopter model *****/
	CGTView* pView = getLowerRightPane();	
	if (pView != NULL)  {
		pView->setRenderMode(CGTView::OPT_TEST);
	}
}