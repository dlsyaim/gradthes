// DPUpperRightView.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "DPUpperRightView.h"
#include "GTDoc.h"
#include "CurveCtrl.h"

#define FIRST_LEFT 2
#define FIRST_UPPER 25
#define CURVE_HEIGHT 180
#define CURVE_WIDTH 280


#define SPATIAL_NAME "spatial_curve"

// CDPUpperRightView

IMPLEMENT_DYNCREATE(CDPUpperRightView, CFormView)

CDPUpperRightView::CDPUpperRightView()
	: CFormView(CDPUpperRightView::IDD)
	, dpXCoor(0)
	, dpYCoor(0)
{
	m_pSpatialCurveCtrl = NULL;
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

	m_pSpatialCurveCtrl = new CCurveCtrl;
	m_pSpatialCurveCtrl->Create(CRect(FIRST_LEFT, FIRST_UPPER, FIRST_LEFT + CURVE_WIDTH, FIRST_UPPER + CURVE_HEIGHT), this, 
		IDC_ROLL_CURVE_CONTROL);
	/*
	 * In method SetMargin, the CRect object's four coodinates don't have the actual meaning, they
	 * just represent the margin in LEFT/TOP/RIGHT/BOTTOM direction respectively
	 */
	m_pSpatialCurveCtrl->SetMargin(CRect(1, 1, 1, 1));
	// Add the curve
	int idx = m_pSpatialCurveCtrl->AddCurve(SPATIAL_NAME, RGB(0, 0, 0));
	m_pSpatialCurveCtrl->GetCurve(idx)->ShowCurve();
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

void CDPUpperRightView::updateFS(pFlyState fs)
{
	dpXCoor = fs->N_Pos;
	dpYCoor = fs->E_Pos;

	mapData.push_back(FPOINT(dpXCoor, dpYCoor));

	updateCurve();

	UpdateData(FALSE);
}

void CDPUpperRightView::updateCurve(void)
{
	std::vector<FPOINT>::iterator iter;
	for (iter = mapData.begin(); iter != mapData.end(); iter++) {
		m_pSpatialCurveCtrl->AddData(SPATIAL_NAME, (*iter).first, (*iter).second);
	}

	m_pSpatialCurveCtrl->Invalidate();
}
