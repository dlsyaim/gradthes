#pragma once


// CCommunicationTestDialog �Ի���

class CCommunicationTestDialog : public CDialog
{
	DECLARE_DYNAMIC(CCommunicationTestDialog)

public:
	CCommunicationTestDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCommunicationTestDialog();

// �Ի�������
	enum { IDD = IDD_COMMUNICATIONTEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
