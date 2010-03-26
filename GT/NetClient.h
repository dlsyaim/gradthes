#pragma once

class CNetClient
{
public:
	CNetClient(void);
	~CNetClient(void);

	// Initialize the networking environment
	BOOL InitNet();

	// Initialize the client
	int initCln(char * ip, int Port);

	// Send data to the server
	BOOL SendSvr(void * p, int len);
	
protected:
	int soc;
	struct sockaddr_in server_sockaddr_in;
};
