#pragma once



// CDPUpperRightView 窗体视图
class CGTDoc;
class CDPUpperRightView : public CFormView
{
	DECLARE_DYNCREATE(CDPUpperRightView)

protected:
	CDPUpperRightView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDPUpperRightView();

public:
	enum { IDD = IDD_DP_UPPERRIGHT_FORMVIEW };
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
	double dpXCoor;
	double dpYCoor;
	afx_msg void OnBnClickedDPZoomIn();
	afx_msg void OnBnClickedDPZoomOut();
};

#ifndef _DEBUG  // debug version in DPUpperRightView.cpp
inline CGTDoc* CDPUpperRightView::GetDocument() const
   { return reinterpret_cast<CGTDoc*>(m_pDocument); }
#endif

