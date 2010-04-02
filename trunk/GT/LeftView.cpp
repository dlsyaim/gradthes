// LeftView.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "LeftView.h"
#include "GTDoc.h"


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CFormView)

CLeftView::CLeftView()
	: CFormView(CLeftView::IDD)
{

}

CLeftView::~CLeftView()
{
}

void CLeftView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLeftView, CFormView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CLeftView 诊断

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CFormView::AssertValid();
}

CGTDoc* CLeftView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGTDoc)));
	return (CGTDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CLeftView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CLeftView 消息处理程序

int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	GetDocument()->leftView = this;
	return 0;
}

BOOL CLeftView::OnEraseBkgnd(CDC* pDC)
{
	//return TRUE;

	return CFormView::OnEraseBkgnd(pDC);
}
