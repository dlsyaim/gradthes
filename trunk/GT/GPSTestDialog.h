#pragma once


// CGPSTestDialog �Ի���

class CGPSTestDialog : public CDialog
{
	DECLARE_DYNAMIC(CGPSTestDialog)

public:
	CGPSTestDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGPSTestDialog();

// �Ի�������
	enum { IDD = IDD_GPSTEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
