#pragma once

#include "TabCtrlSSL.h"
#include "TabPageSSL.h"
// RotorDiskDemarcateDialog 对话框

class RotorDiskDemarcateDialog : public CDialog
{
	DECLARE_DYNAMIC(RotorDiskDemarcateDialog)

public:
	RotorDiskDemarcateDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RotorDiskDemarcateDialog();

// 对话框数据
	enum { IDD = IDD_ROTORDISK_DEMARCATE_DIALOG };

	CTabCtrlSSL	m_tabRotorDisk;
	CTabPageSSL m_tabCollective;
	CTabPageSSL m_tabPitch;
	CTabPageSSL m_tabRoll;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
private:
	void drawCoordinateSystem(CPaintDC *dc, POINT origin, int length);

private:
	int origin_x1, origin_y1;
	int origin_x2, origin_y2;
	int origin_x3, origin_y3;
	int step;
};
