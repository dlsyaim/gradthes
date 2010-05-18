// GridView.cpp : 实现文件
//

#include "stdafx.h"
#include <gl/glut.h>
#include <algorithm>
#include <fstream>
#include "GT.h"
#include "MainFrm.h"
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

	mapTex = NULL;
}

CGridView::~CGridView()
{
	if (m_pGridCtrl) {
		delete m_pGridCtrl;
	}

	//std::vector<PathPointData*>::iterator iter;
	//for (iter = path.begin(); iter != path.end(); iter++) {
	//	delete *iter;
	//}

	if (mapTex)
		delete mapTex;
}

void CGridView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_GridControl(pDX, IDC_GRID, *m_pGridCtrl); 
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
	ON_BN_CLICKED(IDC_ADD_POINT, &CGridView::OnBnClickedAddPoint)
	ON_BN_CLICKED(IDC_SELECT_POINT, &CGridView::OnBnClickedSelectPoint)
	ON_BN_CLICKED(IDC_LOAD_IMAGE_BUTTON, &CGridView::OnBnClickedLoadImageButton)
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
		// Create the grid control object
		m_pGridCtrl = new CGridCtrl;
		if (!m_pGridCtrl) 
			return -1;

		// Create the grid control window
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
		} catch (CMemoryException* e) {
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
					Item.strText.Format(_T("X"));
					break;
				case 2:
					Item.strText.Format(_T("Y"));
					break;
				case 3:
					Item.strText.Format(_T("Z"));
					break;
				case 4:
					Item.strText.Format(_T("T"));
					break;
				case 5:
					Item.strText.Format(_T("Action"));
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
	}	

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
		// Because the grid control's client area size is 23 smaller then the CRect object which is passed
		// as a parameter of Create function, a user-defined function is invoked for resize the columns' width
		ResizeColumns(FALSE);
		//TRACE("Size: %d %d %d %d\n", rect.right, rect.bottom, rect.Width(), rect.Height());
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
	TRACE(_T("End Edit on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
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
	CSingleton *instance = CSingleton::getInstance();
	std::vector<pPathPointData> *path = instance->getPath();
	/********** When click the last cell, then should check if the text is 'Add' or 'Update' **********/
	if (pItem->iColumn == NUM_OF_COL) {
		PathPointData *ppd = NULL, *editedPoint = NULL;
		CString label = m_pGridCtrl->GetItemText(pItem->iRow, pItem->iColumn);
		if (label == "Add") {
			// New a path point
			ppd = new PathPointData();
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
			// Add the path point to the path vector
			path->push_back(ppd);
		} else if (label == "Update") {
			editedPoint = findBySerial(path, pItem->iRow - 1);
			if (editedPoint != NULL) {
				// Update the path point's data
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
		} else {
			return;
		}

		// Inform the CGTView to update
		// Set the path
		GetDocument()->lowerRightView->setPath(path);
		if (ppd)
			GetDocument()->lowerRightView->addPathPoint(ppd);
		else
			GetDocument()->lowerRightView->updatePathPoint(editedPoint);
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
	CSingleton* instance = CSingleton::getInstance();
	std::vector<pPathPointData>* path = instance->getPath();
	/********** Here we must send all the path point data to the server **********/
	if (path->size() == 0) 
		return;

	/********** Sort the path **********/
	sort(path->begin(), path->end(), lowerSorter);
	/********** Construct the content of the command to start send path points *********/
	char command[2];
	__int16 *c = (__int16 *)command;
	c[0] = TPT_LOADPATHPOINT_START;

	/********** First send the LOAD START command **********/
	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	cln->SendSvr(command, sizeof(command));

	/********** Then send the first path point **********/
	char pointCommand[sizeof(PathPointData) + 2];
	c = (__int16 *)pointCommand;
	c[0] = TPT_LOADPATHPOINTS;

	memcpy(pointCommand + 2, (char *)(*path)[0], sizeof(PathPointData));
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
	CSingleton* instance = CSingleton::getInstance();
	std::vector<pPathPointData> *path = instance->getPath();
	(*received)++;
	__int16 *c;

	CNetCln* cln = ((CGTApp*)AfxGetApp())->getCln();
	if ((*received) == path->size()) {
		char overCommand[2];
		c = (__int16 *)overCommand;
		c[0] = TPT_LOADPATHPOINT_STOP;
		cln->SendSvr(overCommand, sizeof (overCommand));
		return TRUE;
	}
	// Send one point 
	char pointCommand[sizeof(PathPointData) + INSTRUCTION_LENGTH];
	c = (__int16 *)pointCommand;
	c[0] = TPT_LOADPATHPOINTS;
	
	memcpy(pointCommand + 2, (char *)((*path)[*received]), sizeof(PathPointData));
	cln->SendSvr(pointCommand, sizeof(pointCommand));

	TRACE(_T("Point:%d, %f, %f, %f\n"), (*path)[*received]->serial, (*path)[*received]->Coordinate_X, (*path)[*received]->Coordinate_Z);

	return TRUE;
}

LRESULT CGridView::OnCheckReply(WPARAM w, LPARAM l)
{

	CSingleton *instance = CSingleton::getInstance();
	std::vector<pPathPointData> *path = instance->getPath();

	PConfigStruct pCS = instance->getCS();
	static int version = 0;
	CTime t = CTime::GetCurrentTime();  
	CString timeString = t.Format("%Y-%m-%d %H-%M-%S");
	CString verStr;	
	
	if (*state) {
		// Set the global state variable
		instance->setIsPathSet(TRUE);
		// And need to save the data into the files
		verStr.Format(_T("-%d.fp"), version++);
		timeString.Append(verStr);

		pCS->isPathSet = 1;
		memcpy(pCS->flightPathFileName, (LPCTSTR)timeString, timeString.GetLength());
		
		std::ofstream ofs(timeString, std::ios::binary);
		std::vector<PathPointData*>::iterator iter;
		for (iter = path->begin(); iter != path->end(); iter++) {
			ofs.write((char*)(*iter), sizeof(**iter));
		}
		ofs.close();
	} else {
		AfxMessageBox(_T("Failed to check the path"), MB_OK | MB_ICONSTOP);
		instance->setIsPathSet(FALSE);
	}

	return TRUE;
}

pPathPointData CGridView::findBySerial(std::vector<pPathPointData>* path, int serial)
{
	std::vector<pPathPointData>::iterator iter;
	for (iter = path->begin(); iter != path->end(); iter++) {
		if ((*iter)->serial == serial)
			return *iter;
	}
	return NULL;
}
void CGridView::OnBnClickedAddPoint()
{
	setCheckBoxStates("Add");
}

void CGridView::OnBnClickedSelectPoint()
{
	setCheckBoxStates("Select");
}

/*
 * Load a image, and turn it into a texture
 */
void CGridView::OnBnClickedLoadImageButton()
{
	/********** Open the image file **********/
	char strFilter[] = { 
		"Joint Photographic Experts Group(*.jpg;*.jpeg)|*.jpg;*.jpeg|Graphic Interchange Format(*.gif)|*.gif|Bitmap(*.bmp)| *.bmp||" };
	while (TRUE) {
		CFileDialog fileDlg(TRUE, NULL, NULL, 0, strFilter);
		CString fileName;	
		if (fileDlg.DoModal() == IDOK) {
			fileName = fileDlg.GetPathName();
			if (!mapTex)
				mapTex = new Texture();			
			if (!mapTex->loadTexture(fileName) ) {
				AfxMessageBox(_T("Invalidate image file\nChoose another one"), MB_OK | MB_ICONINFORMATION);
				delete mapTex;
				mapTex = NULL;
				continue;
			} else {
				// x1(0.0f), x2(1.0f), y1(0.0f), y2(1.0f)
				mapTex->setX1(0.0f);
				mapTex->setX2(1.0f);
				mapTex->setY1(0.0f);
				mapTex->setY2(1.0f);
				GetDocument()->lowerRightView->setMapTex(mapTex);
				break;
			}
		} else {
			break;
		}
	}
}

void CGridView::ResizeColumns(BOOL isFixedResize)
{
	if (isFixedResize) {
		if (m_pGridCtrl->GetColumnCount() <= 0) 
			return;
	} else {
		if (m_pGridCtrl->GetColumnCount() <= m_pGridCtrl->GetFixedColumnCount())
			return;
	}

	int nChanged = 0;
	int nFirstColumn = isFixedResize ? 0 : m_pGridCtrl->GetFixedColumnCount();
	int col;
	for (col = nFirstColumn; col < m_pGridCtrl->GetColumnCount(); col++) {
		if (m_pGridCtrl->GetColumnWidth(col) > 0)
			nChanged++;
	}

	if (nChanged <= 0)
		return;

	long virtualWidth = m_pGridCtrl->GetVirtualWidth();
	CRect rect;
	GetClientRect(&rect);
	int nDiffer;
	if (isFixedResize)
		nDiffer = rect.Width()/* - virtualWidth*//*- m_pGridCtrl->GetFixedColumnWidth()*/;
	else
		nDiffer = rect.Width() - m_pGridCtrl->GetFixedColumnWidth();
	if (nDiffer <= 0)
		nDiffer = rect.Width();
	int nAdjustment = nDiffer / nChanged;
	for (col = nFirstColumn; col < m_pGridCtrl->GetColumnCount(); col++) {
		// The width of columns > 1
		if (m_pGridCtrl->GetColumnWidth(col) > 0) { 
			if (nAdjustment > 1)
				m_pGridCtrl->SetColumnWidth(col, /*m_pGridCtrl->GetColumnWidth(col) + */nAdjustment - 1);
			else 
				m_pGridCtrl->SetColumnWidth(col, /*m_pGridCtrl->GetColumnWidth(col) + */nAdjustment);

		}
	}
	
	//if (nDiffer > 0) {
	//	int remainder = nDiffer % nChanged;
	//	for (int nCount = 0, col = nFirstColumn; (col < m_pGridCtrl->GetColumnCount() && nCount < remainder); col++, nCount++)
	//	{
	//		if (m_pGridCtrl->GetColumnWidth(col) > 0) {
	//			int originWidth = m_pGridCtrl->GetColumnWidth(col);
	//			TRACE(_T("Remainder:%d\n"), originWidth);
	//			m_pGridCtrl->SetColumnWidth(col, originWidth - 1);
	//		}
	//	}
	//} else {
	//	int remainder = (-nDiffer) % nChanged;
	//	for (int nCount = 0, col = nFirstColumn; (col < m_pGridCtrl->GetColumnCount() && nCount < remainder); col++, nCount++)
	//	{
	//		if (m_pGridCtrl->GetColumnWidth(col) > 0)
	//			m_pGridCtrl->SetColumnWidth(col, m_pGridCtrl->GetColumnWidth(col) - 1);
	//	}
	//}
	TRACE(_T("Changed:%d %d %d %ld\n"), nChanged, rect.right, rect.bottom, m_pGridCtrl->GetVirtualWidth());
	m_pGridCtrl->Invalidate();
}

void CGridView::updateFormView(pPathPointData selectedPoint)
{
	if (!selectedPoint)
		return;

	int nCol = 1;
	int nRow = selectedPoint->serial + 1;
	CString label;

	label.Format("%.4g", selectedPoint->Coordinate_X);
	m_pGridCtrl->SetItemText(nRow, nCol++, label);

	label.Format("%.4g", selectedPoint->Coordinate_Y);
	m_pGridCtrl->SetItemText(nRow, nCol++, label);

	label.Format("%.4g", selectedPoint->Coordinate_Z);
	m_pGridCtrl->SetItemText(nRow, nCol++, label);

	label.Format("%.4g", selectedPoint->StayTime);
	m_pGridCtrl->SetItemText(nRow, nCol++, label);

	m_pGridCtrl->Invalidate();

}

void CGridView::setCheckBoxStates(int state, CString label)
{
	CButton* addPointButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_ADD_POINT));
	CButton* selectPointButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_SELECT_POINT));
	if (label == "Add") {
		addPointButton->SetCheck(state);
		selectPointButton->SetCheck(BST_UNCHECKED);
	} else if (label == "Select") {
		selectPointButton->SetCheck(state);
		addPointButton->SetCheck(BST_UNCHECKED);
	}
}

void CGridView::setCheckBoxStates(CString label)
{
	CButton* addPointButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_ADD_POINT));
	CButton* selectPointButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_SELECT_POINT));
	if (selectPointButton && label == "Add")
		selectPointButton->SetCheck(BST_UNCHECKED);
	else if (label == "Select")
		addPointButton->SetCheck(BST_UNCHECKED);

	int checkState;
	if (label == "Add")
		checkState = addPointButton->GetCheck();
	else if (label == "Select")
		checkState = selectPointButton->GetCheck();
	((CMainFrame*)AfxGetMainWnd())->setCheckBoxStates(checkState, label);

	if (checkState == BST_CHECKED) {
		if (label == "Add")
			GetDocument()->lowerRightView->setEditState(1);
		else
			GetDocument()->lowerRightView->setEditState(2);
	} else {
		GetDocument()->lowerRightView->setEditState(-1);
	}
}

