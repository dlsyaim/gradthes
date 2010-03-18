#pragma once


// CGyroTestDialog 对话框

class CGyroTestDialog : public CDialog
{
	DECLARE_DYNAMIC(CGyroTestDialog)

public:
	CGyroTestDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGyroTestDialog();

// 对话框数据
	enum { IDD = IDD_GYROTEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
