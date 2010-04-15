// GridView.cpp : 实现文件
//

#include "stdafx.h"
#include <gl/glut.h>
#include "GT.h"
#include "GridView.h"
#include "GTDoc.h"
#include "GTView.h"


// CGridView

IMPLEMENT_DYNCREATE(CGridView, CFormView)

CGridView::CGridView()
	: CFormView(CGridView::IDD)
{
	m_pGridCtrl = NULL;

	memset(isFirst, TRUE, NUM_OF_ROW * NUM_OF_COL);
}

CGridView::~CGridView()
{
	if (m_pGridCtrl) {
		delete m_pGridCtrl;
	}

	std::vector<PathPointData*>::iterator iter;
	for (iter = path.begin(); iter != path.end(); iter++) {
		delete *iter;
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
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_GRID, OnGridStartEdit)
	ON_NOTIFY(NM_CLICK, IDC_GRID, OnGridClick)
	ON_BN_CLICKED(IDC_SET_POINT_COM, &CGridView::OnBnClickedSetPointCompleted)
	ON_BN_CLICKED(IDC_SCHEDULE_PATH, &CGridView::OnBnClickedSchedulePath)
	ON_BN_CLICKED(IDC_ASSURE_PATH, &CGridView::OnBnClickedAssurePath)
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
}

int CGridView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	GetDocument()->gridView = this;	
	
	if (m_pGridCtrl == NULL)
	{
		// Create the Gridctrl object
		m_pGridCtrl = new CGridCtrl;
		if (!m_pGridCtrl) return -1;

		// Create the Gridctrl window
		CRect rect;
		GetClientRect(rect);
		m_pGridCtrl->Create(rect, this, IDC_GRID);

		// Fill it up with stuff
		m_pGridCtrl->SetEditable(TRUE);
		m_pGridCtrl->EnableDragAndDrop(TRUE);
		
		try {
			m_pGridCtrl->SetRowCount(NUM_OF_ROW + 1);
			m_pGridCtrl->SetColumnCount(NUM_OF_COL + 1);
			m_pGridCtrl->SetFixedRowCount(1);
			m_pGridCtrl->SetFixedColumnCount(1);
		}
		catch (CMemoryException* e)
		{
			e->ReportError();
			e->Delete();
			return -1;
		}

		// Just fill the row headings
		for (int row = 1; row < m_pGridCtrl->GetRowCount(); row++) { 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT;
			Item.row = row;
			Item.col = 0;

			//Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
			Item.strText.Format(_T("%d"), row);
			m_pGridCtrl->SetItem(&Item);
		}
		// Just fill the column headings
		for (int col = 1; col < m_pGridCtrl->GetRowCount(); col++) { 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT;
			Item.row = 0;
			Item.col = col;
		
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
		    m_pGridCtrl->SetItem(&Item);
		}

		// Just fill the row headings
		for (int row = 1; row < m_pGridCtrl->GetRowCount(); row++) { 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT;
			Item.row = row;
			Item.col = 5;

			//Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX;
			Item.strText.Format(_T("Add"));
			m_pGridCtrl->SetItem(&Item);
			m_pGridCtrl->SetItemState(row, 5, m_pGridCtrl->GetItemState(row, 5) | GVIS_READONLY);
			
		}
		(*m_pGridCtrl).AutoSize();
	}	

	/***** Initialize *****/
	//// The server address
	//char *IP = "192.168.0.186";
	//// Initializing
	//if(netcln.initCln(IP, 22222) == 0)
	//{
	//	TRACE("Can't create a sending client\n");
	//}

	path.resize(10);
	return 0;
}

void CGridView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	if (m_pGridCtrl->GetSafeHwnd())
	{
		CRect rect;
		GetClientRect(rect);
		rect.bottom = rect.bottom / 2;
		m_pGridCtrl->MoveWindow(rect);
	}
}

BOOL CGridView::OnEraseBkgnd(CDC* pDC)
{
	/* 
	 * If just return true, then the form view can't be updated each time we drag the splitter bar
	 */
	return CFormView::OnEraseBkgnd(pDC);
}


void CGridView::OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    TRACE(_T("Start Edit on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
}

void CGridView::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	CString itemText = m_pGridCtrl->GetItemText(pItem->iRow, pItem->iColumn);	
}

BOOL CGridView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	if (wParam == (WPARAM)m_pGridCtrl->GetDlgCtrlID())
    {
        *pResult = 1;
        GV_DISPINFO *pDispInfo = (GV_DISPINFO*)lParam;
        if (GVN_GETDISPINFO == pDispInfo->hdr.code)
        {
            //TRACE2("Getting Display info for cell %d,%d\n", pDispInfo->item.row, pDispInfo->item.col);
            pDispInfo->item.strText.Format(_T("Message %d,%d"),pDispInfo->item.row, pDispInfo->item.col);
            return TRUE;
        }
        else if (GVN_ODCACHEHINT == pDispInfo->hdr.code)
        {
            GV_CACHEHINT *pCacheHint = (GV_CACHEHINT*)pDispInfo;
            TRACE(_T("Cache hint received for cell range %d,%d - %d,%d\n"),
                  pCacheHint->range.GetMinRow(), pCacheHint->range.GetMinCol(),
                  pCacheHint->range.GetMaxRow(), pCacheHint->range.GetMaxCol());
        }
    }
    
	return CFormView::OnNotify(wParam, lParam, pResult);
}


void CGridView::OnGridClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    TRACE(_T("Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	/***** When click the last cell, then should check if the text is 'Add' or 'Update' *****/
	if (pItem->iColumn == 5) {
		CString label = m_pGridCtrl->GetItemText(pItem->iRow, pItem->iColumn);
		if (label == "Add") {
			// Contruct a new path point
			PathPointData *ppd = new PathPointData();
			//memset(&ppd, 0, sizeof(ppd));
			// Set the serial number
			ppd->serial = pItem->iRow - 1;
			for (int i = 1; i <= NUM_OF_COL - 1; i++) {
				CString itemText = m_pGridCtrl->GetItemText(pItem->iRow, i);
				switch (i - 1) {
					case 0:
						sscanf(itemText, "%f", &ppd->Coordinate_X);
						break;
					case 1:
						sscanf(itemText, "%f", &ppd->Coordinate_Y);
						break;
					case 2:
						sscanf(itemText, "%f", &ppd->Coordinate_Z);
						break;
					case 3:
						sscanf(itemText, "%f", &ppd->StayTime);
						break;
					default:
						break;
				}
			}
			// Change the text
			m_pGridCtrl->SetItemText(pItem->iRow, pItem->iColumn, "Update");
			// Insert			
			path.insert(path.begin() + pItem->iRow - 1, ppd);
		} else if (label == "Update") {
			// Update a path point
			PathPointData* editedPoint = path[pItem->iRow - 1];
			// Means this isn't the first time editing this cell, so need to update the CGTView
			if (editedPoint != NULL) {
				// Update the point's data
				for (int i = 1; i <= NUM_OF_COL - 1; i++) {
					CString itemText = m_pGridCtrl->GetItemText(pItem->iRow, i);
					switch (i - 1) {
						case 0:
							sscanf(itemText, "%f", &editedPoint->Coordinate_X);
							break;
						case 1:
							sscanf(itemText, "%f", &editedPoint->Coordinate_Y);
							break;
						case 2:
							sscanf(itemText, "%f", &editedPoint->Coordinate_Z);
							break;
						case 3:
							sscanf(itemText, "%f", &editedPoint->StayTime);
							break;
						default:
							break;
					}
				}
			}
		}

		// Inform the CGTView to update
		GetDocument()->lowerRightView->setPath(&path);
	}	
}

void CGridView::OnBnClickedSetPointCompleted()
{
	/***** Set the state variable *****/
	isPathCompleted = TRUE;
}

void CGridView::OnBnClickedSchedulePath()
{
	schedulePath();
}

void CGridView::OnBnClickedAssurePath()
{
	/***** Here we must send all the point to the server *****/
	/********** Construct the content of the communication test command *********/
	char command[102];
	__int16 *c = (__int16 *)command;
	c[0] = FNT_NETTESTTEXT;

	// memcpy(&(command[2]), content, content.GetLength());
	// command[2 + content.GetLength()] = '\0';
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	//netcln.SendSvr(command, 102);
	cln->SendSvr(command, 102);

	/***** Set the global flag variable *****/

}


void CGridView::schedulePath(void)
{
	// TODO: 路径规划
}