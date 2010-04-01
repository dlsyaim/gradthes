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
// Attributest
private:
	CString commandDisplayer;
	CString returnMessageDisplayer;
	CString commandEdit;
	
// Operations
public:
	afx_msg void OnBnClickedCommunicationTestFailure();
	afx_msg void OnBnClickedCommunicationTestPass();
	afx_msg void OnBnClickedDefaultTestButton();
	afx_msg void OnBnClickedCommunicationTestButton();
	afx_msg LRESULT OnReplyMsgArrived(WPARAM w, LPARAM l);
private:
	// Send the communication test command to the server
	void sendCommunicationTestCommand(CString content);
};
