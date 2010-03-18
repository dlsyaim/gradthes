#pragma once


// CGPSTestDialog 对话框

class CGPSTestDialog : public CDialog
{
	DECLARE_DYNAMIC(CGPSTestDialog)

public:
	CGPSTestDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGPSTestDialog();

// 对话框数据
	enum { IDD = IDD_GPSTEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
