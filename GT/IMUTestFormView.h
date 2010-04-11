#pragma once



// CIMUTestFormView 窗体视图
class CGTDoc;
class CIMUTestFormView : public CFormView
{
	DECLARE_DYNCREATE(CIMUTestFormView)

protected:
	CIMUTestFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CIMUTestFormView();

public:
	enum { IDD = IDD_IMU_TEST_FORMVIEW };
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
};

#ifndef _DEBUG  // debug version in GTView.cpp
inline CGTDoc* CIMUTestFormView::GetDocument() const
   { return reinterpret_cast<CGTDoc*>(m_pDocument); }
#endif

