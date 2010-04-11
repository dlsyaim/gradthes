// IMUTestFormView.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "IMUTestFormView.h"
#include "GTDoc.h"


// CIMUTestFormView

IMPLEMENT_DYNCREATE(CIMUTestFormView, CFormView)

CIMUTestFormView::CIMUTestFormView()
	: CFormView(CIMUTestFormView::IDD)
{

}

CIMUTestFormView::~CIMUTestFormView()
{
}

void CIMUTestFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIMUTestFormView, CFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CIMUTestFormView 诊断

#ifdef _DEBUG
void CIMUTestFormView::AssertValid() const
{
	CFormView::AssertValid();
}

CGTDoc* CIMUTestFormView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGTDoc)));
	return (CGTDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CIMUTestFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIMUTestFormView 消息处理程序

int CIMUTestFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	GetDocument()->IMUView = this;
	return 0;
}
