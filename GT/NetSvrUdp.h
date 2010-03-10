#ifndef AN_NETSVR_UDP_H_ 
#define AN_NETSVR_UDP_H_

#include <winsock.h>
#include "Tools.h"

#define socklen_t int
#define RECVBUFLEN  5000
class CGTDoc;
class Renderer;

/*
 * Although this end acts as a client end, we still name the class with 'svr', for the two ends between UDP communication are equivalent.
 */
class CNetSvrUdp  
{
public:
	CNetSvrUdp();
	CNetSvrUdp(Renderer* renderer, CGTDoc *doc);
	virtual ~CNetSvrUdp();
	unsigned char recvbuf[RECVBUFLEN];
	int recvlen;
	int port;
	bool StartSvr();

	inline void setRenderer(Renderer* renderer) {this->renderer = renderer;}
	inline Renderer* getRenderer(void) {return renderer;}
	
	// When a diagram arrives, this method is invoked.
	void OnDataRecv(void);
	int InitNet();

	// The flying state of the helicopter
	FlyState  fs;

	// The renderer pointer and the document pointer
	Renderer* renderer;
	CGTDoc *doc;
};

#endif 
