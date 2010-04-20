#pragma once
#include "GridCtrl_src/GridCtrl.h"

// CPIDCPDialog 对话框

class CPIDCPDialog : public CDialog
{
	DECLARE_DYNAMIC(CPIDCPDialog)

public:
	CPIDCPDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPIDCPDialog();

	CGridCtrl m_Grid;
// 对话框数据
	enum { IDD = IDD_PID_CP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
