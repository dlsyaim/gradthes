#pragma once
#include <vector>
#include "GridCtrl_src/GridCtrl.h"
#include "afxwin.h"


#define NUM_OF_ROW 10
#define NUM_OF_COL 5

// CGridView 窗体视图
class CGTDoc;
class Texture;
class CFlightPathSetController;

class CGridView : public CFormView
{
	DECLARE_DYNCREATE(CGridView)

protected:
	CGridView();           // 动态创建所使用的受保护的构造函数
	virtual ~CGridView();

public:
	enum { IDD = IDD_FORMVIEW };
	CGTDoc* GetDocument() const;
	CGridCtrl *m_pGridCtrl;
	CFlightPathSetController* controller;

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg LRESULT OnLoadReply(WPARAM w, LPARAM l);
	afx_msg LRESULT OnCheckReply(WPARAM w, LPARAM l);
	afx_msg void OnBnClickedSetPointCompleted();
	afx_msg void OnBnClickedSchedulePath();
	afx_msg void OnBnClickedAssurePath();

	// Setter and getter
	inline void setReceived(__int32 *received) {this->received = received;}
	inline void setState(__int32 *state) {this->state = state;}

	void updateFormView(pPathPointData pP);
private:
// Operations
	// Plan the path 
	void schedulePath(void);
	// Find the path point by serial
	pPathPointData findBySerial(std::vector<pPathPointData> *path, int serial);
	// Resize the columns
	void ResizeColumns(BOOL isFixedResize);
	// Set the states of the check boxes
	void setCheckBoxStates(CString label);

// Attributes
	// The state variable
	BOOL isPathCompleted;
	// The point index the server just received
	__int32 *received;
	// The state variable
	__int32 *state;
	// Map texture
	Texture *mapTex;

	bool isChange;

public:
	afx_msg void OnBnClickedAddPoint();
	afx_msg void OnBnClickedSelectPoint();
	afx_msg void OnBnClickedLoadImageButton();
	afx_msg void OnBnClickedLoadFileButton();
	void setCheckBoxStates(int state, CString label);
	
	afx_msg void OnBnClickedSaveFpButton();

	// Update the form view and the GTView
	void updateAllViews(void);
	// Add a row
	void addRow(double wx, double wz);
};

#ifndef _DEBUG  // debug version in GridView.cpp
inline CGTDoc* CGridView::GetDocument() const
   { return reinterpret_cast<CGTDoc*>(m_pDocument); }
#endif


#pragma once


// CFPNamePrefixDialog dialog

class CFPNamePrefixDialog : public CDialog
{
	DECLARE_DYNAMIC(CFPNamePrefixDialog)

public:
	CFPNamePrefixDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFPNamePrefixDialog();

// Dialog Data
	enum { IDD = IDD_FP_NAME_PREFIX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString namePrefix;
};
