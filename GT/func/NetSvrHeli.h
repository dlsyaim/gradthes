
#ifndef _HELI_NETSVRHELI_H_ 
#define _HELI_NETSVRHELI_H_


#include "NetSvr.h"
#include "ProtocolParser.h"

class CNetSvrHeli : public CNetSvr  
{
public:
	CNetSvrHeli();
	virtual ~CNetSvrHeli();
	virtual void OnDataRecv();
	CProtocolParser  *parser;

};

#endif 
