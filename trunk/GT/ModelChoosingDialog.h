#pragma once


// CModelChoosingDialog �Ի���

class CModelChoosingDialog : public CDialog
{
	DECLARE_DYNAMIC(CModelChoosingDialog)

public:
	CModelChoosingDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CModelChoosingDialog();

// �Ի�������
	enum { IDD = IDD_MODELCHOOSING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString aircraftName;
	double aircraftMass;
	double mainBladeLength;
	double aircraftLength;
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
