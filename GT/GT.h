
// GT.h : main header file for the GT application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "func\NetSvrHeli.h"

class CCommunicationTestDialog;

// CGTApp:
// See GT.cpp for the implementation of this class
//

class CGTApp : public CWinAppEx
{
public:
	CGTApp();

private:
	CNetSvrHeli svr;
	CCommunicationTestDialog *ctd;
// Setter and getter
public:
	inline const CNetSvrHeli* getSvr(void) {return &svr;}
	inline CCommunicationTestDialog* getCtd(void) {return ctd;}
	inline void setCtd(CCommunicationTestDialog* ctd) {this->ctd = ctd;}
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGTApp theApp;
