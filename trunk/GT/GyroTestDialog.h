#pragma once


// CGyroTestDialog �Ի���

class CGyroTestDialog : public CDialog
{
	DECLARE_DYNAMIC(CGyroTestDialog)

public:
	CGyroTestDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGyroTestDialog();

// �Ի�������
	enum { IDD = IDD_GYROTEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
