#pragma once
#include "func\protocolparser.h"

class CGSProtocolParser :
	public CProtocolParser
{
public:
	CGSProtocolParser(void);
	~CGSProtocolParser(void);

protected:
	/*
	 * Below functions need to be overridden
	 */
	void OnComTestTReply(void * Target, __int32 Len);
	void OnIMUTestData(void * Target, __int32 Len);
	void OnOPTTTestData(void * Target, __int32 Len);
	void OnLoadPathPointSerial(void *Target, __int32 Len);
	void OnPathPointState(void *Target, __int32 Len);
	void OnComTest(void * Target, __int32 Len);
	void OnStartTaskReply(void *Target, __int32 Len);
	void OnStopTaskReply(void *Target, __int32 Len);
	void OnFlyingState(void * Target, __int32 Len);

};
