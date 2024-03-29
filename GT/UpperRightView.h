#pragma once
#include <vector>


// CUpperRightView 窗体视图
class CGTDoc;
class CCurveCtrl;

typedef std::pair<float, float> FPOINT;

class CUpperRightView : public CFormView
{
	DECLARE_DYNCREATE(CUpperRightView)

protected:
	CUpperRightView();           // 动态创建所使用的受保护的构造函数
	virtual ~CUpperRightView();

public:
	enum { IDD = IDD_UPPERRIGHT_FORMVIEW };
public:
	CGTDoc* GetDocument() const;
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedFEZoomIn();
	afx_msg void OnBnClickedFEZoomOut();
	float feXCoor;
	float feYCoor;
	// The curve of the helicopter model's spatial position
	CCurveCtrl *m_pSpatialCurveCtrl;

	// Update the data
	void updateFS(pFlyState fs);

private:
// Attributes
	std::vector<FPOINT> mapData;
// Operations
	// Update the curve
	void updateCurve(void);
	void updateEdits(pFlyState fs);

};

#ifndef _DEBUG  // debug version in UpperRightView.cpp
inline CGTDoc* CUpperRightView::GetDocument() const
   { return reinterpret_cast<CGTDoc*>(m_pDocument); }
#endif
