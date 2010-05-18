// UpperRightView.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "UpperRightView.h"
#include "GTDoc.h"
#include "CurveCtrl.h"

// CUpperRightView

#define FIRST_LEFT 2
#define FIRST_UPPER 25
#define CURVE_HEIGHT 180
#define CURVE_WIDTH 280

#define SPATIAL_NAME "spatial_curve"

IMPLEMENT_DYNCREATE(CUpperRightView, CFormView)

CUpperRightView::CUpperRightView()
	: CFormView(CUpperRightView::IDD)
	, feXCoor(0)
	, feYCoor(0)
{
	m_pSpatialCurveCtrl = NULL;
}

CUpperRightView::~CUpperRightView()
{
	if (m_pSpatialCurveCtrl)
		delete m_pSpatialCurveCtrl;
}

void CUpperRightView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FE_X_COOR, feXCoor);
	DDX_Text(pDX, IDC_FE_Y_COOR, feYCoor);
}

BEGIN_MESSAGE_MAP(CUpperRightView, CFormView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_FE_ZOOM_IN, &CUpperRightView::OnBnClickedFEZoomIn)
	ON_BN_CLICKED(IDC_FE_ZOOM_OUT, &CUpperRightView::OnBnClickedFEZoomOut)
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

	GetDocument()->upperRightView = this;

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

BOOL CUpperRightView::OnEraseBkgnd(CDC* pDC)
{
	//return TRUE;
	
	return CFormView::OnEraseBkgnd(pDC);
}

void CUpperRightView::OnBnClickedFEZoomIn()
{
	m_pSpatialCurveCtrl->Zoom(TRUE);
}

void CUpperRightView::OnBnClickedFEZoomOut()
{
	m_pSpatialCurveCtrl->Zoom(FALSE);
}


void CUpperRightView::updateFS(pFlyState fs)
{
	mapData.push_back(FPOINT(feXCoor, feYCoor));

	updateCurve();
}

void CUpperRightView::updateCurve(void)
{
	std::vector<FPOINT>::iterator iter;
	for (iter = mapData.begin(); iter != mapData.end(); iter++) {
		m_pSpatialCurveCtrl->AddData(SPATIAL_NAME, (*iter).first, (*iter).second);
	}

	m_pSpatialCurveCtrl->Invalidate();
}

void CUpperRightView::updateEdits(pFlyState fs)
{
	feXCoor = fs->N_Pos;
	feYCoor = fs->E_Pos;

	CEdit* m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_FE_X_COOR));
	CString text;
	text.Format("%.4g", feXCoor);
	m_pEdit->SetWindowText(text);

	m_pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_FE_Y_COOR));
	text.Format("%.4g", feYCoor);
	m_pEdit->SetWindowText(text);
}