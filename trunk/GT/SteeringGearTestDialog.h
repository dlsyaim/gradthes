#pragma once


// CSteeringGearTestDialog �Ի���

class CSteeringGearTestDialog : public CDialog
{
	DECLARE_DYNAMIC(CSteeringGearTestDialog)

public:
	CSteeringGearTestDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSteeringGearTestDialog();

// �Ի�������
	enum { IDD = IDD_STEERINGGEARTEST_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
