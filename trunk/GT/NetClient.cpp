#include "StdAfx.h"
#include "NetClient.h"

CNetClient::CNetClient(void)
{
}

CNetClient::~CNetClient(void)
{
	if(soc != 0)
	{
		closesocket(soc);
	}
}

BOOL CNetClient::InitNet()
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


BOOL CNetClient::SendSvr(void * p,int len)
{	
	if (sendto(soc, (char *)p, len, 0, (struct sockaddr*)&server_sockaddr_in,  sizeof server_sockaddr_in) == SOCKET_ERROR) {	
		return FALSE;
	} else {
		return TRUE;
	}
}


BOOL CNetClient::initCln(char * ip, int port)
{
	if(!InitNet())
		return FALSE;

	if(strlen(ip) <= 0 || strlen(ip) > 999 ) {	
		return FALSE;
	}
	
	// New a socket object
	{
		// Configuration
		server_sockaddr_in.sin_family = AF_INET;
		server_sockaddr_in.sin_port = htons(port);                      // The port the server listening
		server_sockaddr_in.sin_addr.s_addr = inet_addr(ip);         // The address of the server 
		soc = socket(AF_INET, SOCK_DGRAM, 0);
	}
	if (soc = INVALID_SOCKET)
		return FALSE;
	return TRUE;
};
