#pragma once


// CCommunicationTestDialog �Ի���

class CCommunicationTestDialog : public CDialog
{
	DECLARE_DYNAMIC(CCommunicationTestDialog)

public:
	CCommunicationTestDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCommunicationTestDialog();

// �Ի�������
	enum { IDD = IDD_COMMUNICATIONTEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
