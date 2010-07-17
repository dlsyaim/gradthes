#pragma once

#include "TabCtrlSSL.h"
#include "TabPageSSL.h"
#include "func\NetCln.h"
#include "PitchTab.h"
#include "CollectiveTab.h"
#include "RollTab.h"
#include "TailTab.h"

class CHelicopterChoosingController;

// CServoActorDemarcateDialog 对话框

class CServoActorDemarcateDialog : public CDialog
{
	DECLARE_DYNAMIC(CServoActorDemarcateDialog)

public:
	CServoActorDemarcateDialog(CWnd* pParent = NULL);   // 标准构造函数
	// Constructor with the demarcated data
	CServoActorDemarcateDialog(pServoActorData pSAD, CWnd* pParent = NULL);
	virtual ~CServoActorDemarcateDialog();

// 对话框数据
	enum { IDD = IDD_SERVOACTORDEMARCATE_DIALOG};
	CTabCtrlSSL	m_tabServoActor;	
	CCollectiveTab m_tabCollective;
	CPitchTab m_tabPitch;
	CRollTab m_tabRoll;
	CTailTab m_tabTail;

	CHelicopterChoosingController *controller;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedServoActorTestFailure();
	afx_msg void OnBnClickedServoActorTestPass();
	afx_msg void OnClickedCancel();
private:
	// The client point of the socket
	CNetCln netcln;
	// The pointer of the demarcated data
	pServoActorData pSAD;
};
