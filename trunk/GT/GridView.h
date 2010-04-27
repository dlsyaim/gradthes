#pragma once
#include <vector>
#include "GridCtrl_src/GridCtrl.h"


#define NUM_OF_ROW 10
#define NUM_OF_COL 5

// CGridView 窗体视图
class CGTDoc;
class CGridView : public CFormView
{
	DECLARE_DYNCREATE(CGridView)

protected:
	CGridView();           // 动态创建所使用的受保护的构造函数
	virtual ~CGridView();

public:
	enum { IDD = IDD_FORMVIEW };
	CGTDoc* GetDocument() const;
	CGridCtrl *m_pGridCtrl;

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg LRESULT OnLoadReply(WPARAM w, LPARAM l);
	afx_msg LRESULT OnCheckReply(WPARAM w, LPARAM l);
	afx_msg void OnBnClickedSetPointCompleted();
	afx_msg void OnBnClickedSchedulePath();
	afx_msg void OnBnClickedAssurePath();

	// Setter and getter
	inline void setReceived(__int32 *received) {this->received = received;}
	inline void setState(__int32 *state) {this->state = state;}

private:
// Operations
	void schedulePath(void);
	pPathPointData findBySerial(int serial);
// Attributes
	// The origin path
	std::vector<PathPointData*> path;
	// The scheduled path
	std::vector<PathPointData*> scheduledPath;

	// The state variable
	BOOL isPathCompleted;
	// The point index the server just received
	__int32 *received;
	// The state variable
	__int32 *state;



public:
	afx_msg void OnBnClickedAddPoint();
	afx_msg void OnBnClickedSelectPoint();
};

#ifndef _DEBUG  // debug version in GridView.cpp
inline CGTDoc* CGridView::GetDocument() const
   { return reinterpret_cast<CGTDoc*>(m_pDocument); }
#endif


