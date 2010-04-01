#pragma once
#include "TabPageSSL.h"

// CTotalTab 对话框

class CTotalTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(CTotalTab)

public:
	CTotalTab(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTotalTab();

// 对话框数据
	enum { IDD = IDD_COLLECTIVE_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
