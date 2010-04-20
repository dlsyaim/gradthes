#ifndef _HELI_NETSVRHELI_H_ 
#define _HELI_NETSVRHELI_H_


#include "NetSvr.h"
class CProtocolParser;

class CNetSvrHeli : public CNetSvr  
{
public:
// Operations
	CNetSvrHeli();
	virtual ~CNetSvrHeli();
	virtual void OnDataRecv();
// Attributest
	CProtocolParser  *parser;

};

#endif 
