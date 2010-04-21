#include "stdafx.h"

#include <windows.h>
#include <GL/glut.h>
#include <vector>
#include "GTDoc.h"
#include "Renderer.h"
#include "NetSvrUdp.h"


CNetSvrUdp::CNetSvrUdp()
{
	recvlen = 0;
}

CNetSvrUdp::CNetSvrUdp(Renderer* renderer, CGTDoc *doc)
{
	recvlen = 0;
	this->renderer = renderer;
	this->doc = doc;
}

CNetSvrUdp::~CNetSvrUdp()
{

}



int initAsSvrUdp(void * p)
{
	CNetSvrUdp * ns;
	ns = (CNetSvrUdp *)p;
	if(ns->InitNet()==0)
	{
		return 0;
	}

	int port = ns->port;
	int fdmax;
	fd_set read_fds;
	fd_set master;
	//////////////////////////////////////////
	FD_ZERO(&master);

	SOCKET socket1;
	struct sockaddr_in from;

	struct sockaddr_in local;
	int fromlen =sizeof(from);
	local.sin_family=AF_INET;
	local.sin_port=htons(port);             ///¼àÌý¶Ë¿Ú
	local.sin_addr.s_addr=INADDR_ANY;       ///±¾»ú

	socket1=socket(AF_INET,SOCK_DGRAM,0);
	bind(socket1,(struct sockaddr*)&local,sizeof local);



	FD_SET(socket1,&master);
	fdmax=socket1;
	while(1)
	{
		read_fds=master;
		if(select(fdmax+1,&read_fds,NULL,NULL,NULL)==-1) 
		{
			char errMsg[255];
			sprintf(errMsg, "Error code: %d\n", WSAGetLastError());
			AfxMessageBox((LPTSTR)errMsg, MB_OK | MB_ICONSTOP);
			return -1;
		}
		
		if (FD_ISSET(socket1,&read_fds))
		{
			
			ns->recvlen = recvfrom(socket1,(char *)ns->recvbuf,RECVBUFLEN,0,(struct sockaddr*)&from,&fromlen);
			
			if (ns->recvlen!=SOCKET_ERROR)
			{
				ns->OnDataRecv();
			}
		}
	}
}


int CNetSvrUdp::InitNet()
{
	WSADATA wsadata;
	int ret;
	ret = WSAStartup ( 0x101, &wsadata );
	if(ret==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool CNetSvrUdp::StartSvr()
{
	DWORD id;
	HANDLE  reth;
	void * para = this;
	reth = CreateThread(NULL,0,(unsigned long (__stdcall *)(void *))initAsSvrUdp,para,0,&id);
	if(reth != NULL)
	{
		return true;
	}
	return false;
}

// When a datagram arrives, this method is invoked.
void CNetSvrUdp::OnDataRecv(void) 
{
	if(this->recvlen == sizeof(FlyState))
	{
		memcpy(&fs, this->recvbuf, sizeof(FlyState));
		// First we update instruments' data
		//renderer->updateInstrumentsData(&fs);
		// Then we notify the view class to redraw
		POSITION pos = doc->GetFirstViewPosition();
		doc->GetNextView(pos)->Invalidate(FALSE);
	}
}
