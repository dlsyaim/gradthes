#pragma once

#include "TabCtrlSSL.h"
#include "TabPageSSL.h"
#include "func\NetCln.h"
#include "PitchTab.h"
#include "CollectiveTab.h"
#include "RollTab.h"
#include "TailTab.h"

// CServoActorDemarcateDialog �Ի���

class CServoActorDemarcateDialog : public CDialog
{
	DECLARE_DYNAMIC(CServoActorDemarcateDialog)

public:
	CServoActorDemarcateDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CServoActorDemarcateDialog();

// �Ի�������
	enum { IDD = IDD_SERVOACTORDEMARCATE_DIALOG};
	CTabCtrlSSL	m_tabServoActor;
	CCollectiveTab m_tabCollective;
	CPitchTab m_tabPitch;
	CRollTab m_tabRoll;
	CTailTab m_tabTail;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedServoActorTestFailure();
	afx_msg void OnBnClickedServoActorTestPass();
private:
	// The client point of the socket
	CNetCln netcln;

};
