#pragma once
#include <vector>
#include "GridCtrl_src/GridCtrl.h"
#include "func\NetCln.h"



#define NUM_OF_ROW 10
#define NUM_OF_COL 5

// CGridView 窗体视图
class CGTDoc;
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

public:
	afx_msg void OnBnClickedSetPointCompleted();
	afx_msg void OnBnClickedSchedulePath();
	afx_msg void OnBnClickedAssurePath();

// Operations
private:
	void schedulePath(void);
// Attributes
	CNetCln netcln;
	// The origin path
	std::vector<PathPointData*> path;
	// The scheduled path
	std::vector<PathPointData*> scheduledPath;
	// The selected path point
	PathPointData* selectedPathPoint;
	// The state variable
	BOOL isPathCompleted;
	// This variable indicates if the cell is edit for the first time
	BOOL isFirst[NUM_OF_ROW * NUM_OF_COL];

};

#ifndef _DEBUG  // debug version in GridView.cpp
inline CGTDoc* CGridView::GetDocument() const
   { return reinterpret_cast<CGTDoc*>(m_pDocument); }
#endif


