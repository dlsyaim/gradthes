#pragma once


// CSteeringGearTestDialog 对话框

class CSteeringGearTestDialog : public CDialog
{
	DECLARE_DYNAMIC(CSteeringGearTestDialog)

public:
	CSteeringGearTestDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSteeringGearTestDialog();

// 对话框数据
	enum { IDD = IDD_STEERINGGEARTEST_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
