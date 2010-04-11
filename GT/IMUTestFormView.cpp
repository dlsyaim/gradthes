// IMUTestFormView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GT.h"
#include "IMUTestFormView.h"
#include "GTDoc.h"


// CIMUTestFormView

IMPLEMENT_DYNCREATE(CIMUTestFormView, CFormView)

CIMUTestFormView::CIMUTestFormView()
	: CFormView(CIMUTestFormView::IDD)
{

}

CIMUTestFormView::~CIMUTestFormView()
{
}

void CIMUTestFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIMUTestFormView, CFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CIMUTestFormView ���

#ifdef _DEBUG
void CIMUTestFormView::AssertValid() const
{
	CFormView::AssertValid();
}

CGTDoc* CIMUTestFormView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGTDoc)));
	return (CGTDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CIMUTestFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIMUTestFormView ��Ϣ�������

int CIMUTestFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	GetDocument()->IMUView = this;
	return 0;
}
