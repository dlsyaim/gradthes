
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#define MAX_NUM_HELICOPTER_NAME 5
class ST_SplitterWnd;
class CGTView;
class CMainFrmController;

class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Operations
public:
	// Deprecated
	void AddMenu(CString name);

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	// User added
	CMFCToolBar       m_wndFEToolBar;
	CMFCToolBar		  m_wndFPToolBar;		
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

	// A string array to store names of helicopter models already created.
	CString helicopterNames[MAX_NUM_HELICOPTER_NAME];
	// Number of menu items created
	int numberOfMenu;
	// Splitter window
	ST_SplitterWnd* m_pSplitterWnd;
	ST_SplitterWnd* m_pSplitterWnd1;

	CImageList	imageList;
	CImageList  disabledImageList;
	CImageList  hotImageList;
	CBitmap		bitmap;
	
	CMainFrmController* controller;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnNewModel(void);
	afx_msg void OnZeroModel(void);
	afx_msg void OnFirstModel(void);
	afx_msg void OnSecondModel(void);
	afx_msg void OnThirdModel(void);
	afx_msg void OnForthModel(void);

private:
// Operations
	// Operations about the helicopter name array
	void AddName(CString name);
	void DeleteName(CString name);

	// Operations about the recent menu items
	void UpdateMenu(void);
	void DeleteMenu(CString name);
	int FindMenuItem(CMenu*, LPCTSTR str);

	// Select the created helicopter model according to the index
	void OnSelectModel(int idx);
	
	// Read the helicopter model name from the Registry
	void readHMFromRegistry(void);
	// Create the recent helicopter model name menu items
	void createRecentHMMenuItems(void);
	// Get the GTView pointer
	CGTView* getLowerRightPane(void);
	// Set the GTView's edit state
	void setGTViewEditState(CString buttonLabel);
	// Load the configuration parameters
	void loadConfigurationFiles(void);
//Attributes
	CMenu* popUpMenu;
	
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnRotorDiskDemarcated();
	afx_msg void OnDestroy();
	afx_msg void OnCommunicationTest();
	afx_msg void OnServoActorDemarcate();
	afx_msg void OnGyroTest();
	afx_msg void OnFlightPathSet();
	afx_msg void OnReadConfiguration();
	afx_msg void OnSaveConfiguration();
	afx_msg void OnSaveAsConfiguration();
	afx_msg void OnControlParameter();
	afx_msg void OnFlightExperiment();
	afx_msg void OnDataProcess();
	afx_msg void OnOptTest();
	afx_msg void OnClickedFEStart();
	afx_msg void OnClickedFEStop();
	afx_msg void OnClickedAddCB();
	afx_msg void OnClickedSelectCB();
	afx_msg LRESULT OnErrInst(WPARAM w, LPARAM l);

	void setCheckBoxStates(int state, CString label);

	// Enable / Disable menu items
	void enableMenuItems(BOOL isEnable);
};


