#pragma once


// CCommunicationTestDialog 对话框

class CCommunicationTestDialog : public CDialog
{
	DECLARE_DYNAMIC(CCommunicationTestDialog)

public:
	CCommunicationTestDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCommunicationTestDialog();

// 对话框数据
	enum { IDD = IDD_COMMUNICATIONTEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString commandDisplayer;
	CString returnMessageDisplayer;
	CString commandEdit;
	afx_msg void OnBnClickedCommunicationtestFailure();
	afx_msg void OnBnClickedCommunicationtestPass();
	afx_msg void OnBnClickedDefaulttestButton();
	afx_msg void OnBnClickedCommunicationtestButton();
};
