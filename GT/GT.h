
// GT.h : main header file for the GT application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "func\NetSvrHeli.h"
#include "func\NetCln.h"
class CCommunicationTestDialog;
class CGTDoc;
// CGTApp:
// See GT.cpp for the implementation of this class
//

class CGTApp : public CWinAppEx
{
public:
	CGTApp();

private:
	CNetSvrHeli svr;
	CNetCln cln;
	CCommunicationTestDialog *ctd;
// Setter and getter
public:
	inline const CNetSvrHeli* getSvr(void) {return &svr;}
	inline CNetCln* getCln(void) {return &cln;}
	inline CCommunicationTestDialog* getCtd(void) {return ctd;}
	inline void setCommunicationTestDialog(CCommunicationTestDialog* ctd) {this->ctd = ctd;}
	CGTDoc* getDoc(void);
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
