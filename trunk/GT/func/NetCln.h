
#ifndef AN_NETCLN_H_ 
#define AN_NETCLN_H_

/*/�������ݷ��Ϳͻ���/*/
#include <winsock.h>
#define socklen_t int

class CNetCln  
{
public:
	CNetCln();
	virtual ~CNetCln();

	//��ʼ�����绷��
	int InitNet();

	//��ʼ���ͻ��� �����ӷ�������
	int initCln(char * ip,int Port);

	//�������ݵ�������
	int SendSvr(void * p,int len);

	//�ͻ���socket
	int RunSocket;

};

#endif 
