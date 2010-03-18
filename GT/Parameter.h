#pragma once

//class CControlParameter
//{
//public:
//	CControlParameter(void);
//	~CControlParameter(void);
//};

// 控制参数
typedef _ControlParameter {
	char controlAlgorithm[50];
	char description[200];
	bool bol[100];
	long log[100];
	double dbl[100];
} Parameter;

// 飞机模型
typedef _FlightModel {
	char model[50];
	char description[50];
	bool bol[100];
	long log[100];
	double dbl[100];
} FlightModel;

// 飞机状态
typedef _FlightData {
	//时间序号
	
	// 总距
	double collectivePitch;
	// 俯仰角
	double angleOfPitch;
	// 侧滚角
	double angleOfRoll;
	// 尾距
	double backAngle;
	// 油门
	double throttle;
	// 世界X、Y、Z速度
	double x, y, z;
	// X、Y、Z速度
	double vel_x, vel_y, vel_z;
	// X、Y、Z加速度
	double acc_x, acc_y, acc_z;
	// PHI、THETA、PSI
	double phi, theta, psi;
	// PHI、THETA、PSI角速度
	double acc_phi, acc_theta, acc_psi;
} FlightData;

// 飞行路径中的点
typedef _Node {
	int id;
	double x;
	double y;
	double z;
	// 悬停时间
	double hoveringEndurance;
	double reserved[3];
} Node;

