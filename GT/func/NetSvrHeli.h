#ifndef _HELI_NETSVRHELI_H_ 
#define _HELI_NETSVRHELI_H_

#include "NetSvr.h"

class CProtocolParser;

class CNetSvrHeli : public CNetSvrUdp 
{
public:
// Operations
	CNetSvrHeli();
	virtual ~CNetSvrHeli();
	virtual void OnDataRecv();
// Attributes
	CProtocolParser  *parser;
};

#endif 
