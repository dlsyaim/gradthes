#ifndef AN_NETSVR_H_ 
#define AN_NETSVR_H_

#include <winsock.h>

#define socklen_t int
#define RECVBUFLEN  10240

class CNetSvr  
{
public:
	CNetSvr();
	virtual ~CNetSvr();
	unsigned char recvbuf[RECVBUFLEN];
	int recvlen;
	int port;
	bool StartSvr();
	int InitNet();
	virtual void OnDataRecv() = 0;
};

/*
 * A UDP socket server
 */
class CNetSvrUdp  
{
public:
	CNetSvrUdp();
	virtual ~CNetSvrUdp();
	unsigned char recvbuf[RECVBUFLEN];

	int recvlen;
	int port;
	
	bool StartSvr();	
	// When a diagram arrives, this method is invoked.
	virtual void OnDataRecv(void) = 0;
	int InitNet();
};


#endif 
