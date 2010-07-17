#pragma once


// CHelicopterChoosingDialog 对话框
#include "AbstractLogWriter.h"
#include "HeliBodyTab.h"
#include "TailRotorTab.h"
#include "MainRotorTab.h"
#include "TabCtrlSSL.h"
#include "TabPageSSL.h"
#include "GSDefinition.h"
#include "HelicopterChoosingController.h"

class CHelicopterChoosingDialog : public CDialog
{
	DECLARE_DYNAMIC(CHelicopterChoosingDialog)

public:
	CHelicopterChoosingDialog(CWnd* pParent = NULL, BOOL isNew = TRUE, PHelicopterModel pHM = NULL);   // 标准构造函数
	virtual ~CHelicopterChoosingDialog();

// 对话框数据
	enum { IDD = IDD_HELICOPTERCHOOSING_DIALOG };
	CTabCtrlSSL	m_heliChosTab;
	CHeliBodyTab m_bodyTab;
	CMainRotorTab m_mainRotorTab;
	CTailRotorTab m_tailRotorTab;

	CHelicopterChoosingController *controller;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	// A flag variable indicates whether the helicopter model is new or not
	BOOL isNew;
	// A helicopter model pointer
	PHelicopterModel tempHelicopterModel;

	// Operations
	void updateTabs(void);
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	//afx_msg void OnEnChangeAircraftnameEdit();
	//afx_msg void OnEnChangeAircraftmassEdit();
	//afx_msg void OnEnChangeAircraftlenghtEdit();
	//afx_msg void OnEnChangeMainbladelenghtEdit();
	//afx_msg void OnEnChangeMainbladerpmEdit();
	//afx_msg void OnEnChangeXinertiaEdit();
	virtual BOOL OnInitDialog();
};
