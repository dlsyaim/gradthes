// DPUpperRightView.cpp : ʵ���ļ�
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


// CDPUpperRightView ���

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


// CDPUpperRightView ��Ϣ�������

int CDPUpperRightView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	GetDocument()->dpUpperRightView = this;
	return 0;
}

void CDPUpperRightView::OnBnClickedDPZoomIn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CDPUpperRightView::OnBnClickedDPZoomOut()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
