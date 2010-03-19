
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#define MAX_NUM_HELICOPTER_NAME 5

class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
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
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

	// A string array to store names of helicopter models already created.
	CString helicopterNames[MAX_NUM_HELICOPTER_NAME];
	// Number of menu items created
	int numberOfMenu;
	// User defined variable
	//CMFCToolBar m_wndAHRSToolBar;

	// If a new model is 
	BOOL isNew;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnNewModel();
	afx_msg void OnZeroModel();
	afx_msg void OnFirstModel();
	afx_msg void OnSecondModel();
	afx_msg void OnThirdModel();
	afx_msg void OnForthModel();

private:
	void AddName(CString name);
	void DeleteName(CString name);

	void UpdateMenu(void);
};


