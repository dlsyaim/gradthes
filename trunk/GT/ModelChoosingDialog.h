#pragma once


// CModelChoosingDialog 对话框

class CModelChoosingDialog : public CDialog
{
	DECLARE_DYNAMIC(CModelChoosingDialog)

public:
	CModelChoosingDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModelChoosingDialog();

// 对话框数据
	enum { IDD = IDD_MODELCHOOSING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
