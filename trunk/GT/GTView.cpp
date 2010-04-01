
// GTView.cpp : implementation of the CGTView class
//

#include "stdafx.h"
#include "GT.h"
#include "MainFrm.h"

#include <GL/glut.h>
#include <GL/glaux.h>
#include <vector>


#include "GTDoc.h"
#include "GTView.h"
#include "HelicopterChoosingDialog.h"
#include "CommunicationTestDialog.h"
#include "ServoActorDemarcateDialog.h"
#include "GyroTestDialog.h"
#include "GPSTestDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Some global variables.
char commandData[2];
int count=0;
int start=0;
CString str;
CString aLine = _T("");


// Flag variable indicating the right mouse button is pressed or not.
BOOL  rbDown = FALSE;

// CGTView

IMPLEMENT_DYNCREATE(CGTView, CView)

BEGIN_MESSAGE_MAP(CGTView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGTView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	//ON_COMMAND(ID_AHRS_START, &CGTView::OnAHRSStart)
	//ON_COMMAND(ID_AHRS_STOP, &CGTView::OnAHRSStop)
	ON_MESSAGE(WM_COMM_RXCHAR, &CGTView::OnCommunication)
	ON_WM_RBUTTONDOWN()
	
	ON_COMMAND(ID_32774, &CGTView::OnCommunicationTest)
	ON_COMMAND(ID_32775, &CGTView::OnServoActorDemarcate)
	ON_COMMAND(ID_32776, &CGTView::OnGyroTest)
	ON_COMMAND(ID_32777, &CGTView::OnGPSTest)
END_MESSAGE_MAP()

// CGTView construction/destruction

CGTView::CGTView()
{
	// TODO: add construction code here
}

CGTView::~CGTView()
{
}

BOOL CGTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = cs.style | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

// CGTView drawing

void CGTView::OnDraw(CDC* /*pDC*/)
{
	CGTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	
	// Set m_hRC to be the current render context.
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	// Clear the color buffer.
	glClear(GL_COLOR_BUFFER_BIT);	

	// Set the cursor's position to the center of the window client area.
	//POINT cursorPos;
	//cursorPos.x = m_rect.right / 2;
	//cursorPos.y = m_rect.bottom / 2;
	//ClientToScreen(&cursorPos);
	//SetCursorPos(cursorPos.x, cursorPos.y);

	if (!m_Renderer)
		return;
	
	m_Renderer->setBase(base);

	GetClientRect(&m_rect);
	//m_Renderer->draw(&m_rect);
	// Swap the front and back framebuffer
	SwapBuffers(wglGetCurrentDC());
}


// CGTView printing


void CGTView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CGTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGTView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CGTView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGTView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CGTView diagnostics

#ifdef _DEBUG
void CGTView::AssertValid() const
{
	CView::AssertValid();
}

void CGTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGTDoc* CGTView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGTDoc)));
	return (CGTDoc*)m_pDocument;
}
#endif //_DEBUG


// CGTView message handlers

void CGTView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);	
	
	glDepthFunc(GL_LEQUAL);												
	glEnable(GL_DEPTH_TEST);												

	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GetClientRect(&m_rect);
	glViewport(0, 0, m_rect.right, m_rect.bottom);

	m_left = -m_rect.right / 2.0;
	m_right = m_rect.right / 2.0;
	m_top = m_rect.bottom / 2.0;
	m_bottom = -m_rect.bottom / 2.0;
	m_near = -1000;
	m_far = 1000;
}

int CGTView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pDC = new CClientDC(this);
	ASSERT(m_pDC != NULL);

	// TODO: Add extra initialization here
	m_nBaud=115200;
	m_nCom=1;
	m_cParity='N';
	m_nDatabits=8;
	m_nStopbits=1;
	m_dwCommEvents = EV_RXFLAG | EV_RXCHAR;
	
	if (m_Port.InitPort(this, m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits, m_dwCommEvents, 512)) {
		m_Port.StartMonitoring();
	} else {
		AfxMessageBox(_T("Could not found a com number"));
	}

	if (!cSetupPixelFormat())
		return -1;

	// Create render context.
	m_hRC = wglCreateContext(m_pDC->GetSafeHdc());
	// Set m_hRC to be the current RC
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	// Build font. (Must after wglMakeCurrent)
	if (!cBuildFont())
		return -1;

	m_Renderer = new Renderer(FLY_STATISTICS);
	if (!m_Renderer->loadConfiguration())
		return -1;

	if (GetDocument() != NULL) {
		pSvrSock = new CNetSvrUdp(m_Renderer, GetDocument());

		// 5518 is the port we monitor
		pSvrSock->port = 5518;
		if (!pSvrSock->StartSvr()) {
			AfxMessageBox(_T("UDP can't establish"), MB_OK | MB_ICONSTOP);
		}
	}

	//OnStartTimer();

	return 0;
}



void CGTView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: 
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	m_left = -cx / 2.0;
	m_right = cx / 2.0;
	m_top = cy / 2.0;
	m_bottom = -cy / 2.0;
	m_near = -1000;
	m_far = 1000;

	glViewport(0, 0, cx, cy);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

BOOL CGTView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 
	// This line of code is quite important.
	return TRUE;
}

void CGTView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(m_hRC);
	delete m_pDC;
	
	// Delete 256 characters.
	glDeleteLists(base, 256);	

	//OnStopTimer();

	OnAHRSStop();
	delete m_Renderer;
	delete pSvrSock;
}

// 
void CGTView::OnStartTimer(void)
{
	m_nTimer = SetTimer(1, 1000, 0);
}

// 
void CGTView::OnStopTimer(void)
{
	KillTimer(m_nTimer);
}

void CGTView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 
	CGTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc | !m_Renderer)
		return;

	// TODO: We just need 9 floats or doubles.
	if (!pDoc->getFlyStatistics(m_Renderer->getStat(), FLY_STATISTICS)) {
		return;
	}

	if (!m_Renderer) {
		return;
	}

	// Then we could update the intruments' data.
	m_Renderer->updateInstrumentsData();
	Invalidate(FALSE);

	CView::OnTimer(nIDEvent);
}

void CGTView::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rec;
	GetClientRect(&rec);
	CPoint middlePoint(rec.right >> 1, rec.bottom >> 1);
	ClientToScreen(&middlePoint);
	if (rbDown) {
			m_Renderer->updateCamera(&middlePoint);
			Invalidate(FALSE);
	}

	CView::OnMouseMove(nFlags, point);
}

BOOL CGTView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 
	// We know the WM_KEYDOWN and WM_CHAR message are two messages whose source are different.
	// If a WM_KEYDOWN message arrives, we leave the handling of pressing lower 26 english letters to the WM_CHAR messages.
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam) {
			case 'M':
				m_Renderer->setIsMultiport(TRUE);
				break;
			default:
				m_Renderer->updateCamera(pMsg->wParam);
				break;
		}
	}	

	// Here we just handle the lower 26 english letters
	if (pMsg->message == WM_CHAR) {
		if ((pMsg->wParam >= 97 && pMsg->wParam <= 112)) {
			switch (pMsg->wParam) {
				case 'm':
					m_Renderer->setIsMultiport(FALSE);
					break;
				default:
					break;
			}
		}
	}
	
	Invalidate(FALSE);
	return CView::PreTranslateMessage(pMsg);
}

void CGTView::OnAHRSStart()
{
	// TODO: 
	commandData[0] = 0xfe;
	commandData[1] = 0x83;
	m_Port.WriteToPort(commandData,2);
}

void CGTView::OnAHRSStop()
{
	// TODO:
	commandData[0] = 0xfe;
	commandData[1] = 0xfe;
	m_Port.WriteToPort(commandData,2);
}


// When a byte arrives at the comm port, this method is invoked.
long CGTView::OnCommunication(WPARAM ch, LPARAM port)
{
	count++;
	if ((count <= 50) && (start == 0))
	{
		if(count == 50)
		{
			count = 0;
			start = 1;
		}
		return 0;
	}

	if (count < 19)
	{
		str.Format(_T("%02X"), ch);
		aLine = aLine + str;

		if (count%2 == 0)
		{
			aLine = aLine + _T("  ");
		}		
		
		// Have received the 9 number we are concerning
		//if (count == 18)
		//{
		//	aLine = aLine + "\r\n";
		//}
	}

	if (count == 36)
	{
		count = 0;
		if (!m_Renderer)
			return - 1;
	
		// TODO: We just need 9 floats or doubles
		if (!m_Renderer->updateInstrumentsData(aLine))
			return -1;

		// Restore the aLine
		aLine = _T("");
		Invalidate(FALSE);
	}

	return 0;
}

void CGTView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 

	rbDown = !rbDown;
	CView::OnRButtonDown(nFlags, point);
}



BOOL CGTView::cSetupPixelFormat()
{
	// Set the pixel format.
	static PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),		 // Size of this pixel format descriptor
			1,													 // Version number
		PFD_DRAW_TO_WINDOW|					 // Format must support window
			PFD_SUPPORT_OPENGL|					 // Format must support opengl
			PFD_DOUBLEBUFFER,						 // Must support double buffer
		PFD_TYPE_RGBA,								 // Request aan RGBA format
		24,													 // 24-bit color depth
		0,0,0,0,0,0,											 // Color bits ignored
		8,														 // 8-bit alpha buffer
		0,														 // Shift bit ignored
		0,														 // No accumulation buffer
		0,0,0,0,												 // Accumulation bits ignored
		32,													 // 32-bit z-buffer
		0,														 // No stencil buffer
		0,														 // No auxilliary buffer
		PFD_MAIN_PLANE,								 // Main Layer
		0,														 // Reserved
		0,0,0													 // Layer masks ignored
	};

	int pixelformat;

	// Choose the matched pixel format and return pixel format index.
	if((pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) ==0)
	{
		AfxMessageBox(_T("ChoosePixelFormat failed"), MB_OK | MB_ICONSTOP);
		return FALSE;
	}

	// Set the current pixel format according to the chosen pixel format index.
	if(SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		AfxMessageBox(_T("SetPixelFormat failed"), MB_OK | MB_ICONSTOP);
		return FALSE;
	}

	return TRUE;
}

BOOL CGTView::cBuildFont(void)
{
	// Used to store the new font object.
	HFONT	newFont;												
	// Used to store the origin font object.
	HFONT	oldFont;												

	// Store the 256 character
	base = glGenLists(256);	

	newFont = CreateFont(-18,									// The heigth of the font
							0,												// The width of the font
							0,												// The rotation angle
							0,												// Position angle
							FW_THIN,									// The thickness of the font
							FALSE,										// Italic
							FALSE,										// Underline
							FALSE,										// Strickout
							ANSI_CHARSET,							// Character set
							OUT_TT_PRECIS,							// Output precise
							CLIP_DEFAULT_PRECIS,				// Clip precise
							ANTIALIASED_QUALITY,				// Quality
							FF_DONTCARE | DEFAULT_PITCH,	// Character pitch
							_T("Tahoma"));								// Name of font
	// Choose the device context.
	oldFont = (HFONT)SelectObject(m_pDC->GetSafeHdc(), newFont); 		
	// Create 256 character
	wglUseFontBitmaps(m_pDC->GetSafeHdc(), 0, 256, base);			
	// Store the device context.
	SelectObject(m_pDC->GetSafeHdc(), oldFont);							
	// Delete the new font.
	DeleteObject(newFont);	
	return TRUE;
}

/***** Here start to test the communication *****/
void CGTView::OnCommunicationTest()
{
	CCommunicationTestDialog ctd;
	((CGTApp*)AfxGetApp())->setCtd(&ctd);
	ctd.DoModal();
}

void CGTView::OnServoActorDemarcate()
{
	// TODO: 
	CServoActorDemarcateDialog sgtd;
	sgtd.DoModal();
}

void CGTView::OnGyroTest()
{
	// TODO: 
	CGyroTestDialog gtd;
	gtd.DoModal();
}

void CGTView::OnGPSTest()
{
	// TODO: 
	CGPSTestDialog gtd;
	gtd.DoModal();
}
