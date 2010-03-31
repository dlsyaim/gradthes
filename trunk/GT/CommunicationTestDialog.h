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
	afx_msg void OnBnClickedCommunicationTestFailure();
	afx_msg void OnBnClickedCommunicationTestPass();
	afx_msg void OnBnClickedDefaultTestButton();
	afx_msg void OnBnClickedCommunicationTestButton();
};
