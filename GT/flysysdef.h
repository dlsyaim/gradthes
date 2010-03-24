#ifndef _FLYSYSDEF_H_
#define _FLYSYSDEF_H_


#include  "compiledef.h" 

/*/本头文件对小型无人直升机飞行系统的数据结构作定义/*/

/*/
通信协议约定
本通信协议规定了地面站与飞机之间以及地面站与地面站之间的通信方式与数据结构
/*/

/*/通信类型定义/*/


enum NetDataType
{			
	NDT_EMERGENCY,						//应急数据
	NDT_NETTEST,						//网络测试数据类型
	NDT_NETTESTREPLY,					//网络测试应答数据类型
	NDT_EQUIPMENTTEST,					//设备测试数据类型
	NDT_EQUIPMENTTESTREPLY,				//设备测试应答数据类型
	NDT_OPERATIONCOMMAND,				//操控指令数据类型
	NDT_FLYINGSTATEDATA,				//飞行数据
	NDT_CAMERADATA,						//摄像数据
	NDT_NUMBER
};



/*/应急数据结构定义/*/
typedef struct EmergencyData
{
	int i_EmergencyState;				//应急状态
};


/***以下为网络测试封装**************************************************************/
/*/
网络测试数据封装
****************同时作为网络测试返回数据
/*/
typedef struct NetTestData
{
	unsigned long l_SendSerial;		//包数据序号
	unsigned long l_SendStamp;		//发送时间戳
	unsigned long l_RecvStamp;		//接收时间戳
	short int     i_SendPort;		//发起端号
};


/***以上为网络测试封装**************************************************************/



/***以下为测试相关封装**************************************************************/
/*/设备测试类型定义/*/


enum EquipmentTestType
{
	ETT_SERVOACTOR,						//舵机
	ETT_IMU,							//IMU
	ETT_GPS,							//gps
	ETT_OPTTRACE,						//光学追踪系统
	ETT_ALTIMETER,						//高度计
	ETT_THROTTLE,						//油门
	ETT_TILTDISC,						//倾斜盘
	ETT_NUMBER
};


enum ServoActorTestType
{
	STT_SERVOACTORTEST,
	STT_SERVOACTORTESTREPLY,
	STT_NUMBER
};

/*/舵机测试指令/*/ 
typedef struct ServoActorIns
{
	int i_ActorSerial;					//舵机编号
	double f_SetAngle;					//目标角度
};

/*/舵机测试应答数据/*/
typedef struct ServoActorData
{
	int i_ActorState;					//舵机状态  0 未设置舵机参数   1 已经执行目标指令
	int i_ActorSerial;					//舵机编号
	double f_SetAngle;					//目标角度
};


enum IMUTestType
{
	ITT_IMUTESTINS,
	ITT_IMUTESTDATA,
	ITT_NUMBER
};

/*/IMU测试指令封装/*/
typedef struct IMUTestIns
{
	int i_OnOrOff;						//IMU测试指令 0开始 1结束
};

/*/IMU测试应答数据封装/*/
typedef struct IMUTestData
{
	int i_IMUState;						//IMU状态 0 IMU错误 1 初始化  2数据
	double f_N_Speed;					//X北速度
	double f_E_Speed;					//Y东速度			
	double f_D_Speed;					//Z下速度
	double f_N_Acc;						//x加速度
	double f_E_Acc;						//y加速度
	double f_D_Acc;						//z加速度
	double f_phi;						//侧滚角
	double f_theta;						//俯仰角
	double f_psi;						//航向角
	double f_phi_Acc;					//侧滚角加速度
	double f_theta_Acc;					//俯仰角加速度
	double f_psi_Acc;					//航向角加速度
};

//
//
//GPS指令与结构暂缺
//
//



enum OptTraceTestType
{
	OTTT_IMUTESTINS,
	OTTT_IMUTESTDATA,
	OTTT_NUMBER
};


/*/光学追踪系统测试指令封装/*/
typedef struct OPTTRACETestIns
{
	int i_OnOrOff;						//IMU测试指令 0开始 1结束
};

/*/光学追踪系统测试应答数据封装/*/
typedef struct OPTTRACETestData
{
	int i_OptTraceState;				//光学追踪系统状态 0 IMU错误 1 数据
	double f_N_Pos;						//X北位置
	double f_E_Pos;						//Y东位置
	double f_D_Pos;						//Z下位置
	double f_N_Speed;					//X北速度
	double f_E_Speed;					//Y东速度			
	double f_D_Speed;					//Z下速度
	double f_N_Acc;						//x加速度
	double f_E_Acc;						//y加速度
	double f_D_Acc;						//z加速度
	double f_phi;						//侧滚角
	double f_theta;						//俯仰角
	double f_psi;						//航向角
	double f_phi_Acc;					//侧滚角加速度
	double f_theta_Acc;					//俯仰角加速度
	double f_psi_Acc;					//航向角加速度
};

//
//
//高度计指令与结构暂缺
//
//
//




enum ThrottleTestType
{
	THTT_THROTTLETESTINS,
	THTT_THROTTLETESTDATA,
	THTT_NUMBER
};

/*/油门测试指令封装/*/
typedef struct ThrottleIns
{
	double f_Value;						//目标油门大小			
};

/*/油门测试数据封装/*/
typedef struct ThrottleData
{
	int    i_ThrottleState;				//油门状态 0 油门参数未设置  1 已经执行目标指令
	double f_Value;						//目标油门大小
};




enum TiltDiscTestType
{
	TDTT_TILTDISCTESTINS,
	TDTT_TILTDISCTESTDATA,
	TDTT_NUMBER
};

/*/倾斜盘测试指令封装/*/
typedef struct TiltDiscIns
{
	double f_Collect;					//总距（弧度）
	double f_Roll;						//侧滚距（弧度）
	double f_Pitch;						//俯仰距（弧度）
};

/*/倾斜盘测试数据封装/*/
typedef struct TiltDiscData
{
	int    i_TiltDiscState;				//倾斜盘状态 0参数未设置    1 已经执行目标指令
	double f_Collect;					//总距（弧度）
	double f_Roll;						//侧滚距（弧度）
	double f_Pitch;						//俯仰距（弧度）
};


/***以上为测试相关封装**************************************************************/




/***以下为操控指令相关封装**********************************************************/

enum OperationCommandType
{
	OCT_FLYINGTASKINS,					//飞行任务指令
	OCT_PATHINS,						//路径指令
	OCT_HELICOPTERPARAMETER,			//直升机参数指令
	OCT_CONTROLLERPARAMETER,			//控制参数指令
	OCT_CAMERAINS,						//摄像机指令
	OCT_NUMBER
};

/***以下为飞行任务指令相关封装*********************/
enum FlyingTaskInsType
{
	FTT_CHECKALLSETTING,				//检测所有设置
	FTT_CHECKALLSETTINGREPLY,			//检测所有设置回复
	FTT_STARTTASK,						//开始任务
	FTT_STARTTASKREPLY,					//开始任务回复
	FTT_STARTSTOP,						//停止任务
	FTT_STARTSTOPREPLY,					//停止任务回复
	FTT_NUMBER
};


/*/
检测设置数据
FTT_CHECKALLSETTING  和FTT_CHECKALLSETTINGREPLY 均采用本结构
/*/
typedef struct CheckSettingData
{
	int i_SettingState;						//检测设置状态0全正常 其它值（未约定）异常
};

/*/
开始任务数据
FTT_STARTTASK  FTT_STARTTASKREPLY 均采用本结构
/*/
typedef struct StartTaskData
{
	int i_StartTaskData;					//0全正常 其它值（未约定）异常
};



/*/
结束任务数据
FTT_STARTSTOP  FTT_STARTSTOPREPLY 均采用本结构
/*/
typedef struct StopTaskData
{
	int i_StopTaskData;						//0全正常 其它值（未约定）异常
};

/***以上为飞行任务指令相关封装*********************/

/***以下为路径指令相关封装*********************/


enum PathInsType
{
	PIT_EMPTYPATHPOINTS,					//清空所有路径点
	PIT_EMPTYPATHPOINTSREPLY,				//清空所有路径点回复
	PIT_STARTLOADPATHPOINTS,				//开始加载路径点
	PIT_STARTLOADPATHPOINTSREPLY,			//开始加载路径点回复
	PIT_STOPLOADPATHPOINTS,					//结束加载路径点
	PIT_STOPLOADPATHPOINTSREPLY,			//结束加载路径点回复
	PIT_PATHPOINTDATA,						//路径点数据
	PIT_PATHPOINTDATAREPLY,					//路径点数据回复
	PIT_CHECKPATHPOINTS,					//检测路径点
	PIT_CHECKPATHPOINTSREPLY,				//检测路径点回复
	PIT_NUMBER

};

/*/清空路径点指令
PIT_EMPTYPATHPOINTS 与PIT_EMPTYPATHPOINTSREPLY 均采用本结构
/*/
typedef struct EmptyPathPointsIns
{
	int i_EmptyNumber;						//清空的路径点个数 -1 不可以进行清空
};


/*/开始导入路径点指令
PIT_STARTLOADPATHPOINTS PIT_STARTLOADPATHPOINTS 均采用本结构
/*/
typedef struct StartLoadPathPointsIns
{
	int i_StartLoadState;						//0可以进行路径点导入 1 不可以进行路径点导入
};


/*/结束导入路径点指令
PIT_STOPLOADPATHPOINTS PIT_STOPLOADPATHPOINTSREPLY 均采用本结构
/*/
typedef struct StopLoadPathPointsIns
{
	int i_StopLoadState;						//-1 不可以停止路径点导入 其它路径点导入个数
};


/*/
路径点数据结构
PIT_PATHPOINTDATA PIT_PATHPOINTDATAREPLY 均采用本结构
/*/
typedef struct PathPointData
{
	int		i_serial;								//路径点序号
	double	f_Coordinate_X;							//路径点坐标X
	double	f_Coordinate_Y;							//路径点坐标Y
	double	f_Coordinate_Z;							//路径点坐标Z
	double	f_StayTime;								//停留时间
	double	f_reserve1;								//保留1
	double	f_reserve2;								//保留2
	double	f_reserve3;								//保留3
};


/*/路径检测数据指令
PIT_CHECKPATHPOINTS PIT_CHECKPATHPOINTSREPLY 均采用本结构
/*/
typedef struct CheckPathPointsIns
{
	int i_CheckState;								//路径检测状态
};


/***以上为路径指令相关封装*********************/



//
//
//直升机参数指令暂缺
//
//


//
//
//控制参数指令暂缺
//
//



//
//
//摄像机控制指令暂缺
//
//

/***以上为操控指令相关封装**********************************************************/


/***以下为飞行封装**********************************************************/

/*/飞行数据封装/*/
typedef struct FlyingData
{
	long l_TimeStamp;					//数据时间标
	double f_Collective;				//总距
	double f_Roll;						//侧滚角度
	double f_Pitch;						//俯仰角度
	double f_Tail;						//尾桨距
	
	double f_N_Pos_Target;				//X控制目标北位置
	double f_E_Pos_Target;				//Y控制目标东位置
	double f_D_Pos_Target;				//Z控制目标下位置

	double f_N_Pos;						//X当前北位置
	double f_E_Pos;						//Y当前东位置
	double f_D_Pos;						//Z当前下位置

	double f_N_Speed_Target;			//X控制目标北速度
	double f_E_Speed_Target;			//Y控制目标东速度			
	double f_D_Speed_Target;			//Z控制目标下速度

	double f_N_Speed;					//X当前北速度
	double f_E_Speed;					//Y当前东速度			
	double f_D_Speed;					//Z当前下速度

	double f_N_Acc_Target;				//x控制目标加速度
	double f_E_Acc_Target;				//y控制目标加速度
	double f_D_Acc_Target;				//z控制目标加速度

	double f_N_Acc;						//x当前加速度
	double f_E_Acc;						//y当前加速度
	double f_D_Acc;						//z当前加速度

	double f_phi_Target;				//控制目标侧滚角
	double f_theta_Target;				//控制目标俯仰角
	double f_psi_Target;				//控制目标航向角

	double f_phi;						//当前侧滚角
	double f_theta;						//当前俯仰角
	double f_psi;						//当前航向角

	double f_phi_Acc_Target;			//控制目标侧滚角加速度
	double f_theta_Acc_Target;			//控制目标俯仰角加速度
	double f_psi_Acc_Target;			//控制目标航向角加速度

	double f_phi_Acc;					//当前侧滚角加速度
	double f_theta_Acc;					//当前俯仰角加速度
	double f_psi_Acc;					//当前航向角加速度
};


/***以上为飞行封装**********************************************************/



//
//
//摄像数据未定义
//
//

#endif