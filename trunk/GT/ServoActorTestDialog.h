#pragma once
#include "TabCtrlSSL.h"
#include "TabPageSSL.h"

// CServoActorTestDialog �Ի���

class CServoActorTestDialog : public CDialog
{
	DECLARE_DYNAMIC(CServoActorTestDialog)

public:
	CServoActorTestDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CServoActorTestDialog();

// �Ի�������
	enum { IDD = IDD_STEERINGGEARTEST_DIALOG};
	CTabCtrlSSL	m_tabServoActor;
	CTabPageSSL m_tabCollective;
	CTabPageSSL m_tabPitch;
	CTabPageSSL m_tabRoll;
	CTabPageSSL m_tabTail;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
