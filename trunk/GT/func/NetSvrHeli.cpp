#include "stdafx.h"
#include "NetSvrHeli.h"
#include "ProtocolParser.h"
#include "..\GSProtocolParser.h"

CNetSvrHeli::CNetSvrHeli()
{
	parser = new CGSProtocolParser();
}

CNetSvrHeli::~CNetSvrHeli()
{
	if (parser) {
		delete parser;
	}
}

void CNetSvrHeli::OnDataRecv()
{
	if(parser)
	{
		parser->OnInsData(this->recvbuf, this->recvlen);
	}
}
