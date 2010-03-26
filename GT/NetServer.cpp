#include "StdAfx.h"
#include "NetServer.h"

// The function of the new thread
int initSvrUdp(void * p)
{
	CNetServer * ns = (CNetServer *)p;
	if(ns->InitNet() == 0)
	{
		return 0;
	}

	int port = ns->port;
	int fdmax;
	
	fd_set read_fds;
	fd_set master;	
	// Initializes the set to the null set
	FD_ZERO(&master);

	// The socket address which sends data to this server
	struct sockaddr_in from;
	int fromlen = sizeof(from);

	struct sockaddr_in local;
	
	// Establish a socket
	SOCKET socket1;
	local.sin_family=AF_INET;
	local.sin_port = htons(port);						// The port we monitoring
	local.sin_addr.s_addr = INADDR_ANY;         // Local host
	socket1 = socket(AF_INET, SOCK_DGRAM, 0);
	bind(socket1, (struct sockaddr*)&local, sizeof local);

	// Adds descriptor s to set.
	FD_SET(socket1, &master);
	
	fdmax = socket1;
	while(1)
	{
		// First backup the set
		read_fds = master;
		
		if(select(fdmax + 1, &read_fds, NULL, NULL, NULL)==-1) 
		{
			return -1;
		}
		// Nonzero if socket1 is a member of the set. Otherwise, zero.
		if (FD_ISSET(socket1, &read_fds))
		{
			
			ns->recvlen = recvfrom(socket1, (char *)ns->recvbuf, RECVBUFLEN, 0, (struct sockaddr*)&from, &fromlen);
			
			if (ns->recvlen != SOCKET_ERROR)
			{
				ns->OnDataRecv();
			}
		}
	}
}

CNetServer::CNetServer(void)
{
	recvlen = 0;
}

CNetServer::~CNetServer(void)
{
}

BOOL CNetServer::InitNet(void)
{
	WSADATA wsadata;	
	int err;
	// Request 1.1 version of Windows Sockets Specification
	err = WSAStartup (0x101, &wsadata);
	if (err != 0) {
		return FALSE;
	}

	if (LOBYTE(wsadata.wVersion) != 1 || HIBYTE(wsadata.wVersion) != 1) {
		WSACleanup();
		return FALSE;
	}
	return TRUE;
}

bool CNetServer::StartSvr(void)
{
	DWORD id;
	HANDLE  reth;
	void *para = this;
	reth = CreateThread(NULL, 0, (unsigned long (__stdcall *)(void *))initSvrUdp, para, 0, &id);
	return reth != NULL;
}

// When a datagram arrives, this method is invoked.
void CNetServer::OnDataRecv(void) 
{
	//if(this->recvlen == sizeof(FlyState))
	//{
	//	memcpy(&fs, this->recvbuf, sizeof(FlyState));
	//	// First we update instruments' data
	//	renderer->updateInstrumentsData(&fs);
	//	// Then we notify the view class to redraw
	//	POSITION pos = doc->GetFirstViewPosition();
	//	doc->GetNextView(pos)->Invalidate(FALSE);
	//}
}


