#pragma once

class CNetClient
{
public:
	CNetClient(void);
	~CNetClient(void);

	//��ʼ�����绷��
	BOOL InitNet();

	//��ʼ���ͻ��� �����ӷ�������
	int initCln(char * ip,int Port);

	//�������ݵ�������
	int SendSvr(void * p,int len);
	
protected:
	char svrip[1000];
	int iplen;
	int RunSocket;
	struct sockaddr_in server_sockaddr_in;
	int svlen;
	int port;
};
