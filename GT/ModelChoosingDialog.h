#pragma once


// CModelChoosingDialog �Ի���

class CModelChoosingDialog : public CDialog
{
	DECLARE_DYNAMIC(CModelChoosingDialog)

public:
	CModelChoosingDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModelChoosingDialog();

// �Ի�������
	enum { IDD = IDD_MODELCHOOSING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
