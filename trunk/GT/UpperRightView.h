#pragma once



// CUpperRightView ������ͼ
class CGTDoc;
class CUpperRightView : public CFormView
{
	DECLARE_DYNCREATE(CUpperRightView)

protected:
	CUpperRightView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CGTDoc* CGTView::GetDocument() const
   { return reinterpret_cast<CGTDoc*>(m_pDocument); }
#endif
