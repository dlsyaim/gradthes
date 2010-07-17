#pragma once

#include "TabCtrlSSL.h"
#include "TabPageSSL.h"
#include "afxcmn.h"
// RotorDiskDemarcateDialog 对话框
class CHelicopterChoosingController;

class RotorDiskDemarcateDialog : public CDialog
{
	DECLARE_DYNAMIC(RotorDiskDemarcateDialog)

public:
	RotorDiskDemarcateDialog(CWnd* pParent = NULL);   // 标准构造函数
	RotorDiskDemarcateDialog(pTiltDiscData pTDD, CWnd* pParent = NULL);
	virtual ~RotorDiskDemarcateDialog();

	CHelicopterChoosingController *controller;
	TiltDiscData copyTdd;

// 对话框数据
	enum { IDD = IDD_ROTORDISK_DEMARCATE_DIALOG };

	//CTabCtrlSSL	m_tabRotorDisk;
	//CTabPageSSL m_tabCollective;
	//CTabPageSSL m_tabPitch;
	//CTabPageSSL m_tabRoll;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	//afx_msg void OnPaint();
private:
	void drawCoordinateSystem(CPaintDC *dc, POINT origin, int length);

private:
	//int origin_x1, origin_y1;
	//int origin_x2, origin_y2;
	//int origin_x3, origin_y3;
	//int step;
	pTiltDiscData pTDD;
public:
	double dyPitch;
	double dyRoll;
	double dyCollective;
	double stPitch;
	double stRoll;
	double stCollective;
	CSpinButtonCtrl pitchSpin;
	CSpinButtonCtrl rollSpin;
	CSpinButtonCtrl collectiveSpin;
	afx_msg void OnDeltaposDyPitchSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposRollSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposCollectiveSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSendRotorButton();
	afx_msg void OnBnClickedDemarcatedSucBtn();
	CListCtrl demarcatedResult;
	int demarcatedIdx;
	int size;
	afx_msg void OnNMClickRotorResultList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
	float convertedPitch;
	float convertedRoll;
	float convertedCollective;
	afx_msg void OnEnChangeDyPitchEdit();
	afx_msg void OnEnChangeDyRollEdit();
	afx_msg void OnEnChangeDyCollectiveEdit();
//Operations
private:
	void updateConvertedValue(int channel);
	int  addListRow(int row);
	void addListRows(pTiltDiscData pTDD);
	void updateListRow(void);
public:
	afx_msg void OnBnClickedOk();
};
