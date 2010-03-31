#pragma once


// CHelicopterChoosingDialog �Ի���
#include "AbstractLogWriter.h"
class CHelicopterChoosingDialog : public CDialog, public AbstractLogWriter
{
	DECLARE_DYNAMIC(CHelicopterChoosingDialog)

public:
	CHelicopterChoosingDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHelicopterChoosingDialog();

	CString constructLogString(void);
// �Ի�������
	enum { IDD = IDD_HELICOPTERCHOOSING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString helicopterName;
	double helicopterMass;
	double mainBladeLength;
	double helicopterLength;
	double mainBladeRPM;
	double xInertia;
	afx_msg void OnBnClickedOk();
	//afx_msg void OnEnChangeAircraftnameEdit();
	//afx_msg void OnEnChangeAircraftmassEdit();
	//afx_msg void OnEnChangeAircraftlenghtEdit();
	//afx_msg void OnEnChangeMainbladelenghtEdit();
	//afx_msg void OnEnChangeMainbladerpmEdit();
	//afx_msg void OnEnChangeXinertiaEdit();
	virtual BOOL OnInitDialog();
};
