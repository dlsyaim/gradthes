#pragma once
#include "TabPageSSL.h"

// CTotalTab �Ի���

class CTotalTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(CTotalTab)

public:
	CTotalTab(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTotalTab();

// �Ի�������
	enum { IDD = IDD_COLLECTIVE_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
