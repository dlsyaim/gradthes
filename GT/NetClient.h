#pragma once

class CNetClient
{
public:
	CNetClient(void);
	~CNetClient(void);

	//初始化网络环境
	BOOL InitNet();

	//初始化客户端 （连接服务器）
	int initCln(char * ip,int Port);

	//发送数据到服务器
	int SendSvr(void * p,int len);
	
protected:
	char svrip[1000];
	int iplen;
	int RunSocket;
	struct sockaddr_in server_sockaddr_in;
	int svlen;
	int port;
};
