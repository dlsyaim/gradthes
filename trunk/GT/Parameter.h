#pragma once

//class CControlParameter
//{
//public:
//	CControlParameter(void);
//	~CControlParameter(void);
//};

// Control parameters
typedef struct _ControlParameter {
	char controlAlgorithm[50];
	char description[200];
	bool bol[100];
	long log[100];
	double dbl[100];
} ControlParameter, PControlParamter;

// helicopter model
typedef struct _HelicopterModel {
	char model[50];
	char description[50];
	bool bol[100];
	long log[100];
	double dbl[100];
} HelicopterModel, *PHelicopterModel;

// helicopter status(data)
typedef struct _FlightData {
	//ʱ�����
	
	// �ܾ�
	double collectivePitch;
	// ������
	double angleOfPitch;
	// �����
	double angleOfRoll;
	// β��
	double backAngle;
	// ����
	double throttle;
	// ����X��Y��Z�ٶ�
	double x, y, z;
	// X��Y��Z�ٶ�
	double vel_x, vel_y, vel_z;
	// X��Y��Z���ٶ�
	double acc_x, acc_y, acc_z;
	// PHI��THETA��PSI
	double phi, theta, psi;
	// PHI��THETA��PSI���ٶ�
	double acc_phi, acc_theta, acc_psi;
} FlightData, PFlightData;

// ����·���еĵ�
typedef struct _Node {
	int id;
	double x;
	double y;
	double z;
	// ��ͣʱ��
	double hoveringEndurance;
	double reserved[3];
} Node, PNode;

