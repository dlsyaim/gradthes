// DPUpperRightView.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "DPUpperRightView.h"
#include "GTDoc.h"

// CDPUpperRightView

IMPLEMENT_DYNCREATE(CDPUpperRightView, CFormView)

CDPUpperRightView::CDPUpperRightView()
	: CFormView(CDPUpperRightView::IDD)
	, dpXCoor(0)
	, dpYCoor(0)
{

}

CDPUpperRightView::~CDPUpperRightView()
{
}

void CDPUpperRightView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DP_X_COOR, dpXCoor);
	DDX_Text(pDX, IDC_DP_Y_COOR, dpYCoor);
}

BEGIN_MESSAGE_MAP(CDPUpperRightView, CFormView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_DP_ZOOM_IN, &CDPUpperRightView::OnBnClickedDPZoomIn)
	ON_BN_CLICKED(IDC_DP_ZOOM_OUT, &CDPUpperRightView::OnBnClickedDPZoomOut)
END_MESSAGE_MAP()


// CDPUpperRightView 诊断

#ifdef _DEBUG
void CDPUpperRightView::AssertValid() const
{
	CFormView::AssertValid();
}

CGTDoc* CDPUpperRightView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGTDoc)));
	return (CGTDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CDPUpperRightView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDPUpperRightView 消息处理程序

int CDPUpperRightView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	GetDocument()->dpUpperRightView = this;
	return 0;
}

void CDPUpperRightView::OnBnClickedDPZoomIn()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDPUpperRightView::OnBnClickedDPZoomOut()
{
	// TODO: 在此添加控件通知处理程序代码
}
