#include "stdafx.h"
#include "NetSvrHeli.h"


CNetSvrHeli::CNetSvrHeli()
{
	parser = new CProtocolParser();
}

CNetSvrHeli::~CNetSvrHeli()
{
	if (parser != NULL) {
		delete parser;
	}
}

void CNetSvrHeli::OnDataRecv()
{
	if(parser != NULL)
	{
		parser->OnInsData(this->recvbuf, this->recvlen);
	}
}
