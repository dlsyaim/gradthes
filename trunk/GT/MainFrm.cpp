
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "GT.h"

#include "MainFrm.h"
#include "ModelChoosingDialog.h"

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
	ON_COMMAND(ID_32771, &CMainFrame::OnNewModel)
	ON_COMMAND(ID_HELICOPTER_BEGIN + 0, OnZeroModel)
	ON_COMMAND(ID_HELICOPTER_BEGIN + 1, OnFirstModel)
	ON_COMMAND(ID_HELICOPTER_BEGIN + 2, OnSecondModel)
	ON_COMMAND(ID_HELICOPTER_BEGIN + 3, OnThirdModel)
	ON_COMMAND(ID_HELICOPTER_BEGIN + 4, OnForthModel)
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
	// TODO: add member initialization code here
	numberOfMenu = 0;

	isNew = FALSE;
}

CMainFrame::~CMainFrame()
{
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
	// TODO: 在此添加命令处理程序代码
	CModelChoosingDialog *mcd = new CModelChoosingDialog(this);
	mcd->DoModal();

	// First add name
	AddName(mcd->aircraftName);
	UpdateMenu();
}

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
			if (mainMenu->GetMenuString(i, menuName, MF_BYPOSITION) && menuName == "机型选择") {
				subMenu = mainMenu->GetSubMenu(i);
				break;
			}
		}

		for (i = 0; i < (int)subMenu->GetMenuItemCount(); i++) {
			CString menuName;
			if (subMenu->GetMenuString(i, menuName, MF_BYPOSITION) && menuName == "最近模型") {
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
		static CMenu *popUpMenu = NULL;
		MENUITEMINFO info;
		info.cbSize = sizeof (MENUITEMINFO); // must fill up this field
		info.fMask = MIIM_SUBMENU;             


		// Iterate the main menu
		int menuCount = mainMenu->GetMenuItemCount();
		int i;
		for (i = 0; i < menuCount; i++) {
			CString menuName;
			if (mainMenu->GetMenuString(i, menuName, MF_BYPOSITION) && menuName == "机型选择") {
				subMenu = mainMenu->GetSubMenu(i);
				break;
			}
		}

		for (i = 0; i < (int)subMenu->GetMenuItemCount(); i++) {
			CString menuName;
			if (subMenu->GetMenuString(i, menuName, MF_BYPOSITION) && menuName == "最近的模型") {
				subMenu->GetMenuItemInfo(i, &info, TRUE);
				break;
			}
		}
		// Adding
		if (!isNew) {
			isNew = TRUE;
			popUpMenu = new CMenu();
			popUpMenu->CreateMenu();
			info.hSubMenu = popUpMenu->GetSafeHmenu();
			subMenu->SetMenuItemInfo(i, &info, TRUE);
		}
		if (popUpMenu != NULL) {
			if (numberOfMenu < MAX_NUM_HELICOPTER_NAME) {
				if (popUpMenu->AppendMenu(MF_STRING,  ID_HELICOPTER_BEGIN + numberOfMenu, "TEMP") ){					
					numberOfMenu++;
			    }
			}

			// Renaming
			for (i = 0; i < (int)popUpMenu->GetMenuItemCount(); i++ ) {
				popUpMenu->ModifyMenu(ID_HELICOPTER_BEGIN + i, MF_BYCOMMAND, ID_HELICOPTER_BEGIN + i, helicopterNames[i]);					
			}
			// Corresponding
			m_wndMenuBar.CreateFromMenu(mainMenu->GetSafeHmenu(), TRUE, TRUE);
		}
	}	
}

void CMainFrame::AddName(CString name)
{
	// First check if name exists
	DeleteName(name);
	// Then make room for the newly arrived name
	for (int i = MAX_NUM_HELICOPTER_NAME - 1; i > 0; i--) {
		helicopterNames[i] = helicopterNames[i - 1];
	}

	// Thirdly ...
	helicopterNames[0] = name;
	//newestIdx = (newestIdx++) %  MAX_NUM_HELICOPTER_NAME;
	//helicopterNames[newestIdx] = name;
}

void CMainFrame::DeleteName(CString name)
{
	int i; 
	for (i = 0 ; i < MAX_NUM_HELICOPTER_NAME; i++) {
		if (helicopterNames[i] == name) 
			break;
	}
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

void CMainFrame::OnSelectModel(int idx)
{
	if (idx < 0 && idx > 4) 
		return;

	// Open the corresponding existing file
	CString modelName = helicopterNames[idx];
	// Construct a fileName
	char fileName[256];
	GetCurrentDirectory(256, fileName);
	strcat(fileName, modelName);
	// New a CFile pointer
	CFile filePointer;
	CFileException exception;
	if (!filePointer.Open((LPCTSTR)fileName, CFile::modeRead | CFile::shareDenyWrite | CFile::modeNoTruncate, &exception)) {
		// First delete fileName from helicopterNames
		DeleteName(modelName);
		DeleteMenu(modelName);
		CString meg;
		meg.Format("File couldn't be opend %d\n", exception.m_cause);
		AfxMessageBox((LPCTSTR)meg);
		return;
	}
	// New a helicopter model.
  

}

void CMainFrame::DeleteMenu(CString name)
{
	CMenu* mainMenu = CMenu::FromHandle(m_wndMenuBar.GetDefaultMenu());
	if (mainMenu != NULL) {
		CMenu *subMenu = NULL;
		static CMenu *popUpMenu = NULL;
		MENUITEMINFO info;
		info.cbSize = sizeof (MENUITEMINFO); // must fill up this field
		info.fMask = MIIM_SUBMENU;             


		// Iterate the main menu
		int menuCount = mainMenu->GetMenuItemCount();
		int i;
		for (i = 0; i < menuCount; i++) {
			CString menuName;
			if (mainMenu->GetMenuString(i, menuName, MF_BYPOSITION) && menuName == "机型选择") {
				subMenu = mainMenu->GetSubMenu(i);
				break;
			}
		}

		for (i = 0; i < (int)subMenu->GetMenuItemCount(); i++) {
			CString menuName;
			if (subMenu->GetMenuString(i, menuName, MF_BYPOSITION) && menuName == "最近的模型") {
				subMenu->GetMenuItemInfo(i, &info, TRUE);
				popUpMenu = CMenu::FromHandle(info.hSubMenu);
				break;
			}
		}
		numberOfMenu--;
		if (popUpMenu != NULL) {
			int pos = FindMenuItem(popUpMenu, name);
			// Deleting
			int j;
			int originCount = popUpMenu->GetMenuItemCount();
			for (j = pos; j < originCount; j++) {
				popUpMenu->DeleteMenu(pos, MF_BYPOSITION);
			}
			// Adding
			for (j = pos; j < numberOfMenu; j++ ) {
				popUpMenu->AppendMenu(MF_STRING,  ID_HELICOPTER_BEGIN + j, helicopterNames[j]);					
			}
			info.hSubMenu = popUpMenu->GetSafeHmenu();
			subMenu->SetMenuItemInfo(i, &info, TRUE);
			// Corresponding
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
        if (Menu->GetMenuString(i, str, MF_BYPOSITION) &&
         str.Compare(MenuString) == 0)
         return i;
     }

     return -1;
}
