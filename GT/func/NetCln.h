
#ifndef AN_NETCLN_H_ 
#define AN_NETCLN_H_

/*/网络数据发送客户端/*/
#include <winsock.h>
#define socklen_t int

class CNetCln  
{
public:
	CNetCln();
	virtual ~CNetCln();

	//初始化网络环境
	int InitNet();

	//初始化客户端 （连接服务器）
	int initCln(char * ip,int Port);

	//发送数据到服务器
	int SendSvr(void * p,int len);

	//客户端socket
	int RunSocket;
private:
	/*int soc;*/
	struct sockaddr_in server_sockaddr_in;

};

#endif 
