#pragma once
#define RECVBUFLEN  5000

class CNetServer
{
	// Operations
public:
	CNetServer(void);
	virtual ~CNetServer(void);
	virtual void OnDataRecv();
	bool StartSvr();	
	// Initialize the networking environment
	BOOL InitNet();
	
	// Attributes
public:
	// Receiving buffer
	unsigned char recvbuf[RECVBUFLEN];
	// Receiving length
	int recvlen;
	// The port the server monitor
	int port;
};
