#pragma once
#include "afxwin.h"
#include <olectl.h>
#include <ole2.h>


// CFPSFormView 窗体视图
/*
 * FPS is the abbreviation for 'Flight Path Set'
 */

class CGTDoc;

class CFPSFormView : public CFormView
{
	DECLARE_DYNCREATE(CFPSFormView)

protected:
	CFPSFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CFPSFormView();

public:
	enum { IDD = IDD_FLIGHT_PATH_SET_FORMVIEW };
	CGTDoc* GetDocument() const;
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
	double mapLongitude;
	double mapLatitude;
	double jointZCoordinate;
	CStatic m_Map;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
// Operations
	HBITMAP LoadAnImage(CString fileName);
};

#ifndef _DEBUG  // debug version in FPSFormView.cpp
inline CGTDoc* CFPSFormView::GetDocument() const
   { return reinterpret_cast<CGTDoc*>(m_pDocument); }
#endif


