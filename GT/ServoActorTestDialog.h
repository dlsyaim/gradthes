#pragma once
#include "TabCtrlSSL.h"
#include "TabPageSSL.h"

// CServoActorTestDialog 对话框

class CServoActorTestDialog : public CDialog
{
	DECLARE_DYNAMIC(CServoActorTestDialog)

public:
	CServoActorTestDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CServoActorTestDialog();

// 对话框数据
	enum { IDD = IDD_STEERINGGEARTEST_DIALOG};
	CTabCtrlSSL	m_tabServoActor;
	CTabPageSSL m_tabCollective;
	CTabPageSSL m_tabPitch;
	CTabPageSSL m_tabRoll;
	CTabPageSSL m_tabTail;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
