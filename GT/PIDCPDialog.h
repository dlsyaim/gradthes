#pragma once
#include "GridCtrl_src/GridCtrl.h"

// CPIDCPDialog �Ի���

class CPIDCPDialog : public CDialog
{
	DECLARE_DYNAMIC(CPIDCPDialog)

public:
	CPIDCPDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPIDCPDialog();

	CGridCtrl m_Grid;
// �Ի�������
	enum { IDD = IDD_PID_CP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
