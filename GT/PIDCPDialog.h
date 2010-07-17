#pragma once
#include <vector>
#include "GridCtrl_src/GridCtrl.h"

// CPIDCPDialog �Ի���
class CPIDCPDialogController;

class CPIDCPDialog : public CDialog
{
	DECLARE_DYNAMIC(CPIDCPDialog)

public:
	CPIDCPDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPIDCPDialog();

	CGridCtrl m_Grid;
	CPIDCPDialogController *controller;
// �Ի�������
	enum { IDD = IDD_PID_CP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOpenCPBtn();
private:
	void updateGrid(void);
};

#pragma once


// CPIDNamePrefixDialog dialog

class CPIDNamePrefixDialog : public CDialog
{
	DECLARE_DYNAMIC(CPIDNamePrefixDialog)

public:
	CPIDNamePrefixDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPIDNamePrefixDialog();

// Dialog Data
	enum { IDD = IDD_CP_NAME_PREFIX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString namePrefix;
	afx_msg void OnBnClickedOk();
};
