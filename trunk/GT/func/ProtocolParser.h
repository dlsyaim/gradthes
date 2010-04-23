#ifndef _HELI_PROTOCOLPARSER_H_
#define _HELI_PROTOCOLPARSER_H_


class CProtocolParser  
{
public:
	CProtocolParser();
	virtual ~CProtocolParser();
	
	void ParseError(INSHEAD V);

// Virtual functions

	/*
	 * Because the recvbuf may be not pure any more, so we must split it according to the command header
	 */
	virtual void PreProcess(void * Target, __int32 Len);

	virtual bool OnInsData(void * Target, __int32 Len);

	virtual void OnEmergency(void * Target, __int32 Len);
	virtual void OnErrorInsHead(void * Target, __int32 Len);
	virtual void OnComTestT(void * Target, __int32 Len);
	virtual void OnComTestTReply(void * Target, __int32 Len);
	virtual void OnComTest(void * Target, __int32 Len);
	virtual void OnComTestReply(void * Target, __int32 Len);
	virtual void OnServoActorTest(void * Target, __int32 Len);
	virtual void OnThrottleTest(void * Target, __int32 Len);
	virtual void OnTiltDiscTest(void * Target, __int32 Len);
	virtual void OnIMUTestStart(void * Target, __int32 Len);
	virtual void OnIMUTestStop(void * Target, __int32 Len);
	virtual void OnIMUTestData(void * Target, __int32 Len);
	virtual void OnGPSTestStart(void * Target, __int32 Len);
	virtual void OnGPSTestStop(void * Target, __int32 Len);
	virtual void OnGPSTestData(void * Target, __int32 Len);
	virtual void OnOPTTTestStart(void * Target, __int32 Len);
	virtual void OnOPTTTestStop(void * Target, __int32 Len);
	virtual void OnOPTTTestData(void * Target, __int32 Len);
	virtual void OnAltiTestStart(void * Target, __int32 Len);
	virtual void OnAltiTestStop(void * Target, __int32 Len);
	virtual void OnAltiTestData(void * Target, __int32 Len);
	virtual void OnStartTask(void * Target, __int32 Len);
	virtual void OnStartTaskReply(void * Target, __int32 Len);
	virtual void OnStopTask(void * Target, __int32 Len);
	virtual void OnStopTaskReply(void * Target, __int32 Len);
	virtual void OnServoActorSet(void * Target, __int32 Len);
	virtual void OnTileDiscSet(void * Target, __int32 Len);
	virtual void OnLoadPathPointStart(void * Target, __int32 Len);
	virtual void OnLoadPathPointStop(void * Target, __int32 Len);
	virtual void OnLoadPathPoint(void * Target, __int32 Len);
	virtual void OnLoadPathPointSerial(void * Target, __int32 Len);
	virtual void OnPathPointState(void * Target, __int32 Len);
	virtual void OnFlyingState(void * Target, __int32 Len);
	virtual void OnLoadHeliPara(void * Target, __int32 Len);
	virtual void OnLoadCtlPara(void * Target, __int32 Len);
	virtual void OnFlyingStateAct(void * Target, __int32 Len);
};

#endif 
