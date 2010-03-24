#ifndef _COMPLIE_H_
#define _COMPLIE_H_

#define _WINDOWS_C99_




#ifdef _WINDOWS_C99_

#define my64int  __int64

#endif




#ifdef _LINUX_C89_

#define my64int  long long

#endif


typedef struct test
{
	int a;
};


#endif