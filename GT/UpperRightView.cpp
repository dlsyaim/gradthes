// UpperRightView.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "UpperRightView.h"
#include "GTDoc.h"

// CUpperRightView

IMPLEMENT_DYNCREATE(CUpperRightView, CFormView)

CUpperRightView::CUpperRightView()
	: CFormView(CUpperRightView::IDD)
{

}

CUpperRightView::~CUpperRightView()
{
}

void CUpperRightView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUpperRightView, CFormView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CUpperRightView 诊断

#ifdef _DEBUG
void CUpperRightView::AssertValid() const
{
	CFormView::AssertValid();
}
CGTDoc* CUpperRightView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGTDoc)));
	return (CGTDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CUpperRightView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUpperRightView 消息处理程序

int CUpperRightView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	GetDocument()->upperRightView = this;

	return 0;
}

BOOL CUpperRightView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	
	//return CFormView::OnEraseBkgnd(pDC);
}
