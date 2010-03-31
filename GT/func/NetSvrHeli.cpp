
#include "NetSvrHeli.h"


CNetSvrHeli::CNetSvrHeli()
{
	parser = NULL;
}

CNetSvrHeli::~CNetSvrHeli()
{

}

void CNetSvrHeli::OnDataRecv()
{
	if(parser!=NULL)
	{
		parser->OnInsData(this->recvbuf,this->recvlen);
	}
}
