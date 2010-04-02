#pragma once

#include "GridCtrl_src/GridCtrl.h"

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

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CGTDoc* CGridView::GetDocument() const
   { return reinterpret_cast<CGTDoc*>(m_pDocument); }
#endif


