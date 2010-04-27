
// GTView.h : interface of the CGTView class
//


#pragma once
#include <map>
#include "Renderer.h"
#include "SerialPort.h"

//#include "NetSvrUdp.h"

#define FLY_STATISTICS 9
class CGTDoc;

class CGTView : public CView
{
protected: // create from serialization only
	CGTView();
	DECLARE_DYNCREATE(CGTView)

// Attributes
public:
	// User defined variables
	CClientDC *m_pDC;
	HGLRC m_hRC;
	CRect m_rect;
	double m_left,m_right,m_bottom,m_top,m_near,m_far;
	
	// This variable renders the 3D helicopter model
	Renderer *m_Renderer;
	
	// Timer identifier
	UINT m_nTimer;
	
	// The first display list name of the font.
	GLuint base;

	CSerialPort m_Port;
	
	int m_nBaud;          //Baud rate
	int m_nCom;			//Com number
	char m_cParity;		//Check out
	int m_nDatabits;     //Data bits
	int m_nStopbits;     //Stop bits
	
	// Socket to receive the flight state statistics
	//CNetSvrUdp* pSvrSock;

	// Mode
	enum RENDER_MODE {
		IMU_TEST,
		FLIGHT_PATH_SET,
		FLIGHT_EXPERIMENT,
		DATA_PROCESS,
		OPT_TEST
	};

	CGTDoc* GetDocument() const;
private:
	// Rendering mode
	RENDER_MODE renderMode;
	// Left mouse button's state
	int lbState;
	// Map stores the window coordinates and the 3D coordinates
	std::map<pPathPointData, POINT> mapCoor;
	// For mouse moving or up
	int moveOrUp;
	// The selected path point
	PathPointData* selectedPathPoint;
	// For adding or selecting: 1 for add and 2 for select
	int addOrSelect;
	// Left button pushed
	int selected;

// Operations
public:
	// Setters and getters
	inline void setRenderMode(RENDER_MODE m) {this->renderMode = m; Invalidate(FALSE);}
	inline void setPath(std::vector<PathPointData*> *pPath) {m_Renderer->setPPath(pPath); this->Invalidate(FALSE);}
	void addPathPoint(pPathPointData p);
	void updatePathPoint(pPathPointData p);
	void updateMapCoor(void);

	inline void setEditState(int ste) {this->addOrSelect = ste;}

	// Update the data for the IMU test
	void updateIMUData(IMUTestData* itd);
	// Update the data for the OPT test
	void updateOPTData(pOPTTRACETestData otd);
	// Update the data for the flying state
	void updateFS(pFlyState fs);

protected:
	// Setup pixel format.
	BOOL cSetupPixelFormat(void);
	// Build font.
	BOOL cBuildFont(void);

	// Utility function for the timer.
	void OnStartTimer(void);
	void OnStopTimer(void);
	// 
	DWORD m_dwCommEvents;

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnAHRSStart();
	afx_msg void OnAHRSStop();
	afx_msg LONG OnCommunication(WPARAM ch, LPARAM port);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnGPSTest();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

private:
// Operations
	// 1 for x-axis, 2 for y-axis, 3 for z-axis, -1 for none
	int selectNavigator(CPoint *pP);

};

#ifndef _DEBUG  // debug version in GTView.cpp
inline CGTDoc* CGTView::GetDocument() const
   { return reinterpret_cast<CGTDoc*>(m_pDocument); }
#endif
