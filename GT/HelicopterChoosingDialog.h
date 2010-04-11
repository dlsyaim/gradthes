#pragma once


// CHelicopterChoosingDialog 对话框
#include "AbstractLogWriter.h"
class CHelicopterChoosingDialog : public CDialog, public AbstractLogWriter
{
	DECLARE_DYNAMIC(CHelicopterChoosingDialog)

public:
	CHelicopterChoosingDialog(CWnd* pParent = NULL);   // 标准构造函数
	CHelicopterChoosingDialog(CString helicopterName, double helicopterMass, double helicopterLength, 
		double mainBladeLength, double mainBladeRPM, double xInertia,
		CWnd* pParent = NULL);
	virtual ~CHelicopterChoosingDialog();

	CString constructLogString(void);
// 对话框数据
	enum { IDD = IDD_HELICOPTERCHOOSING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString helicopterName;
	double helicopterMass;	
	double helicopterLength;
	double mainBladeLength;
	double mainBladeRPM;
	double xInertia;

	// Flag indicates if the helicopter model is new or not
	BOOL isNew;
public:
	inline CString getHelicopterName(void) {return helicopterName;}
public:
	afx_msg void OnBnClickedOk();
	//afx_msg void OnEnChangeAircraftnameEdit();
	//afx_msg void OnEnChangeAircraftmassEdit();
	//afx_msg void OnEnChangeAircraftlenghtEdit();
	//afx_msg void OnEnChangeMainbladelenghtEdit();
	//afx_msg void OnEnChangeMainbladerpmEdit();
	//afx_msg void OnEnChangeXinertiaEdit();
	virtual BOOL OnInitDialog();
};
