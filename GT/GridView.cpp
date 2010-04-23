// GridView.cpp : 实现文件
//

#include "stdafx.h"
#include <gl/glut.h>
#include <algorithm>
#include <fstream>
#include "GT.h"
#include "GridView.h"
#include "GTDoc.h"
#include "GTView.h"
#include "Singleton.h"
#include "MsgType.h"


bool lowerSorter(PathPointData* p1, PathPointData* p2)
{
	return p1->serial <= p2->serial;
}

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
	ON_MESSAGE(LOAD_POINT_REPLY_MSG, &CGridView::OnLoadReply)
	ON_MESSAGE(PATH_CHECK_REPLY_MSG, &CGridView::OnCheckReply)
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
		rect.bottom /= 2;
		m_pGridCtrl->Create(rect, this, IDC_GRID);

		// Fill it up with stuff
		m_pGridCtrl->SetEditable(TRUE);
		m_pGridCtrl->GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));
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

		// Just fill the row buttons
		for (int row = 1; row < m_pGridCtrl->GetRowCount(); row++) { 
			GV_ITEM Item;
			Item.mask = GVIF_TEXT;
			Item.row = row;
			Item.col = NUM_OF_COL;

			Item.strText.Format(_T("Add"));
			m_pGridCtrl->SetItem(&Item);
			m_pGridCtrl->SetItemState(row, NUM_OF_COL, m_pGridCtrl->GetItemState(row, NUM_OF_COL) | GVIS_READONLY);
			
		}
		(*m_pGridCtrl).AutoSize();
	}	

	/* Currently we just assume the max size is 10 */
	//path.resize(10);
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
	if (pItem->iColumn == NUM_OF_COL) {
		CString label = m_pGridCtrl->GetItemText(pItem->iRow, pItem->iColumn);
		if (label == "Add") {
			// Contruct a new path point
			PathPointData *ppd = new PathPointData();
			memset(ppd, 0, sizeof(PathPointData));
			// Set the serial number
			ppd->serial = pItem->iRow - 1;
			for (int i = 1; i <= NUM_OF_COL - 1; i++) {
				CString itemText = m_pGridCtrl->GetItemText(pItem->iRow, i);
				switch (i - 1) {
					case 0:
						sscanf_s(itemText, "%f", &ppd->Coordinate_X);
						break;
					case 1:
						sscanf_s(itemText, "%f", &ppd->Coordinate_Y);
						break;
					case 2:
						sscanf_s(itemText, "%f", &ppd->Coordinate_Z);
						break;
					case 3:
						sscanf_s(itemText, "%f", &ppd->StayTime);
						break;
					default:
						break;
				}
			}
			// Change the text
			m_pGridCtrl->SetItemText(pItem->iRow, pItem->iColumn, "Update");
			m_pGridCtrl->Invalidate();
			// Insert			
			//path.insert(path.begin() + pItem->iRow - 1, ppd);
			path.push_back(ppd);
		} else if (label == "Update") {
			// Sorting before update
			sort(path.begin(), path.end(), lowerSorter);
			// Update a path point
			PathPointData* editedPoint = path[pItem->iRow - 1];
			if (editedPoint != NULL) {
				// Update the point's data
				for (int i = 1; i <= NUM_OF_COL - 1; i++) {
					CString itemText = m_pGridCtrl->GetItemText(pItem->iRow, i);
					switch (i - 1) {
						case 0:
							sscanf_s(itemText, "%f", &editedPoint->Coordinate_X);
							break;
						case 1:
							sscanf_s(itemText, "%f", &editedPoint->Coordinate_Y);
							break;
						case 2:
							sscanf_s(itemText, "%f", &editedPoint->Coordinate_Z);
							break;
						case 3:
							sscanf_s(itemText, "%f", &editedPoint->StayTime);
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
	if (path.size() == 0) 
		return;

	/***** First sort the path *****/
	sort(path.begin(), path.end(), lowerSorter);
	/********** Construct the content of the starting path sending command *********/
	char command[2];
	__int16 *c = (__int16 *)command;
	c[0] = TPT_LOADPATHPOINT_START;

	/* First send the LOAD START command */
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	cln->SendSvr(command, sizeof(command));

	/* Here we just send the first point */
	char pointCommand[sizeof(PathPointData) + 2];
	c = (__int16 *)pointCommand;
	c[0] = TPT_LOADPATHPOINTS;

	memcpy(pointCommand + 2, (char *)path[0], sizeof(PathPointData));
	cln->SendSvr(pointCommand, sizeof(pointCommand));	
}


void CGridView::schedulePath(void)
{
	// TODO: 路径规划
}

LRESULT CGridView::OnLoadReply(WPARAM w, LPARAM l)
{
	/*
	 * A point sent before has been received, so be ready to send the next point
	 */
	(*received)++;
	__int16 *c;

	/* First send the LOAD START command */
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	if ((*received) == path.size()) {
		char overCommand[2];
		c = (__int16 *)overCommand;
		c[0] = TPT_LOADPATHPOINT_STOP;
		cln->SendSvr(overCommand, sizeof (overCommand));
		return TRUE;
	}
	/* Here we just send one point */
	char pointCommand[sizeof(PathPointData) + INSTRUCTION_LENGTH];
	c = (__int16 *)pointCommand;
	c[0] = TPT_LOADPATHPOINTS;
	
	memcpy(pointCommand + 2, (char *)(path[*received]), sizeof(PathPointData));
	cln->SendSvr(pointCommand, sizeof(pointCommand));

	return TRUE;
}

LRESULT CGridView::OnCheckReply(WPARAM w, LPARAM l)
{
	CSingleton *instance = CSingleton::getInstance();
	static int version = 0;
	CTime t = CTime::GetCurrentTime();  
	CString timeString = t.Format("%Y-%m-%d");
	CString verStr;	
	if (*state) {
		/***** Set the global flag variable *****/
		instance->setIsPathSet(TRUE);
		/* And need to save the data into the files */
		verStr.Format(_T("-%d.fp"), version++);
		timeString.Append(verStr);
		instance->setRecentFPName(timeString);
		std::ofstream ofs(timeString, std::ios::binary);
		std::vector<PathPointData*>::iterator iter;
		for (iter = path.begin(); iter != path.end(); iter++) {
			ofs.write((char*)(*iter), sizeof(**iter));
		}
		ofs.close();
	} else {
		AfxMessageBox(_T("Failed to check the path"), MB_OK | MB_ICONSTOP);
		instance->setIsPathSet(FALSE);
	}

	return TRUE;
}