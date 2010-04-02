// GridView.cpp : 实现文件
//

#include "stdafx.h"
#include "GT.h"
#include "GridView.h"
#include "GTDoc.h"

// CGridView

IMPLEMENT_DYNCREATE(CGridView, CFormView)

CGridView::CGridView()
	: CFormView(CGridView::IDD)
{
	m_pGridCtrl = NULL;
}

CGridView::~CGridView()
{
	if (m_pGridCtrl) {
		delete m_pGridCtrl;
	}
}

void CGridView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, *m_pGridCtrl); 
}

BEGIN_MESSAGE_MAP(CGridView, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CGridView 诊断

#ifdef _DEBUG
void CGridView::AssertValid() const
{
	CFormView::AssertValid();
}

CGTDoc* CGridView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGTDoc)));
	return (CGTDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CGridView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGridView 消息处理程序

void CGridView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
		if (m_pGridCtrl == NULL)
	{
		// Create the Gridctrl object
		m_pGridCtrl = new CGridCtrl;
		if (!m_pGridCtrl) return;

		// Create the Gridctrl window
		CRect rect;
		GetClientRect(rect);
		m_pGridCtrl->Create(rect, this, 100);

		// fill it up with stuff
		m_pGridCtrl->SetEditable(TRUE);
		m_pGridCtrl->EnableDragAndDrop(TRUE);

		try {
			m_pGridCtrl->SetRowCount(11);
			m_pGridCtrl->SetColumnCount(5);
			m_pGridCtrl->SetFixedRowCount(1);
			m_pGridCtrl->SetFixedColumnCount(1);
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
			return;
		}

		// Just fill the row headings
		for (int row = 1; row < m_pGridCtrl->GetRowCount(); row++) { 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = row;
			Item.col = 0;

			Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
			Item.strText.Format(_T("%d"), row);
			//if (row < 1) {
			//	Item.nFormat = DT_LEFT|DT_WORDBREAK;
			//	Item.strText.Format(_T("Column %d"),col);
			//} else if (col < 1) {
			//	Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
			//	Item.strText.Format(_T("Row %d"),row);
			//} else {
			//	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
			//	Item.strText.Format(_T("%d"),row*col);
			//}
			m_pGridCtrl->SetItem(&Item);
		}
		// Just fill the column headings
		for (int col = 1; col < m_pGridCtrl->GetRowCount(); col++) { 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = 0;
			Item.col = col;

			Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
			
			switch (col) {
				case 1:
					Item.strText.Format(_T("  X  "));
					break;
				case 2:
					Item.strText.Format(_T("  Y  "));
					break;
				case 3:
					Item.strText.Format(_T("  Z  "));
					break;
				case 4:
					Item.strText.Format(_T("  T  "));
					break;
				default:
					break;
			}
			//if (row < 1) {
			//	Item.nFormat = DT_LEFT|DT_WORDBREAK;
			//	Item.strText.Format(_T("Column %d"),col);
			//} else if (col < 1) {
			//	Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
			//	Item.strText.Format(_T("Row %d"),row);
			//} else {
			//	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
			//	Item.strText.Format(_T("%d"),row*col);
			//}
			m_pGridCtrl->SetItem(&Item);
		}
		


		m_pGridCtrl->AutoSize();
	}	
}

int CGridView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	GetDocument()->gridView = this;
	return 0;
}

void CGridView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	if (m_pGridCtrl->GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(rect);
		m_pGridCtrl->MoveWindow(rect);
	}
}

BOOL CGridView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;

	//return CFormView::OnEraseBkgnd(pDC);
}
