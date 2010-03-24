#ifndef _FLYSYSDEF_H_
#define _FLYSYSDEF_H_


#include  "compiledef.h" 

/*/��ͷ�ļ���С������ֱ��������ϵͳ�����ݽṹ������/*/

/*/
ͨ��Э��Լ��
��ͨ��Э��涨�˵���վ��ɻ�֮���Լ�����վ�����վ֮���ͨ�ŷ�ʽ�����ݽṹ
/*/

/*/ͨ�����Ͷ���/*/


enum NetDataType
{			
	NDT_EMERGENCY,						//Ӧ������
	NDT_NETTEST,						//���������������
	NDT_NETTESTREPLY,					//�������Ӧ����������
	NDT_EQUIPMENTTEST,					//�豸������������
	NDT_EQUIPMENTTESTREPLY,				//�豸����Ӧ����������
	NDT_OPERATIONCOMMAND,				//�ٿ�ָ����������
	NDT_FLYINGSTATEDATA,				//��������
	NDT_CAMERADATA,						//��������
	NDT_NUMBER
};



/*/Ӧ�����ݽṹ����/*/
typedef struct EmergencyData
{
	int i_EmergencyState;				//Ӧ��״̬
};


/***����Ϊ������Է�װ**************************************************************/
/*/
����������ݷ�װ
****************ͬʱ��Ϊ������Է�������
/*/
typedef struct NetTestData
{
	unsigned long l_SendSerial;		//���������
	unsigned long l_SendStamp;		//����ʱ���
	unsigned long l_RecvStamp;		//����ʱ���
	short int     i_SendPort;		//����˺�
};


/***����Ϊ������Է�װ**************************************************************/



/***����Ϊ������ط�װ**************************************************************/
/*/�豸�������Ͷ���/*/


enum EquipmentTestType
{
	ETT_SERVOACTOR,						//���
	ETT_IMU,							//IMU
	ETT_GPS,							//gps
	ETT_OPTTRACE,						//��ѧ׷��ϵͳ
	ETT_ALTIMETER,						//�߶ȼ�
	ETT_THROTTLE,						//����
	ETT_TILTDISC,						//��б��
	ETT_NUMBER
};


enum ServoActorTestType
{
	STT_SERVOACTORTEST,
	STT_SERVOACTORTESTREPLY,
	STT_NUMBER
};

/*/�������ָ��/*/ 
typedef struct ServoActorIns
{
	int i_ActorSerial;					//������
	double f_SetAngle;					//Ŀ��Ƕ�
};

/*/�������Ӧ������/*/
typedef struct ServoActorData
{
	int i_ActorState;					//���״̬  0 δ���ö������   1 �Ѿ�ִ��Ŀ��ָ��
	int i_ActorSerial;					//������
	double f_SetAngle;					//Ŀ��Ƕ�
};


enum IMUTestType
{
	ITT_IMUTESTINS,
	ITT_IMUTESTDATA,
	ITT_NUMBER
};

/*/IMU����ָ���װ/*/
typedef struct IMUTestIns
{
	int i_OnOrOff;						//IMU����ָ�� 0��ʼ 1����
};

/*/IMU����Ӧ�����ݷ�װ/*/
typedef struct IMUTestData
{
	int i_IMUState;						//IMU״̬ 0 IMU���� 1 ��ʼ��  2����
	double f_N_Speed;					//X���ٶ�
	double f_E_Speed;					//Y���ٶ�			
	double f_D_Speed;					//Z���ٶ�
	double f_N_Acc;						//x���ٶ�
	double f_E_Acc;						//y���ٶ�
	double f_D_Acc;						//z���ٶ�
	double f_phi;						//�����
	double f_theta;						//������
	double f_psi;						//�����
	double f_phi_Acc;					//����Ǽ��ٶ�
	double f_theta_Acc;					//�����Ǽ��ٶ�
	double f_psi_Acc;					//����Ǽ��ٶ�
};

//
//
//GPSָ����ṹ��ȱ
//
//



enum OptTraceTestType
{
	OTTT_IMUTESTINS,
	OTTT_IMUTESTDATA,
	OTTT_NUMBER
};


/*/��ѧ׷��ϵͳ����ָ���װ/*/
typedef struct OPTTRACETestIns
{
	int i_OnOrOff;						//IMU����ָ�� 0��ʼ 1����
};

/*/��ѧ׷��ϵͳ����Ӧ�����ݷ�װ/*/
typedef struct OPTTRACETestData
{
	int i_OptTraceState;				//��ѧ׷��ϵͳ״̬ 0 IMU���� 1 ����
	double f_N_Pos;						//X��λ��
	double f_E_Pos;						//Y��λ��
	double f_D_Pos;						//Z��λ��
	double f_N_Speed;					//X���ٶ�
	double f_E_Speed;					//Y���ٶ�			
	double f_D_Speed;					//Z���ٶ�
	double f_N_Acc;						//x���ٶ�
	double f_E_Acc;						//y���ٶ�
	double f_D_Acc;						//z���ٶ�
	double f_phi;						//�����
	double f_theta;						//������
	double f_psi;						//�����
	double f_phi_Acc;					//����Ǽ��ٶ�
	double f_theta_Acc;					//�����Ǽ��ٶ�
	double f_psi_Acc;					//����Ǽ��ٶ�
};

//
//
//�߶ȼ�ָ����ṹ��ȱ
//
//
//




enum ThrottleTestType
{
	THTT_THROTTLETESTINS,
	THTT_THROTTLETESTDATA,
	THTT_NUMBER
};

/*/���Ų���ָ���װ/*/
typedef struct ThrottleIns
{
	double f_Value;						//Ŀ�����Ŵ�С			
};

/*/���Ų������ݷ�װ/*/
typedef struct ThrottleData
{
	int    i_ThrottleState;				//����״̬ 0 ���Ų���δ����  1 �Ѿ�ִ��Ŀ��ָ��
	double f_Value;						//Ŀ�����Ŵ�С
};




enum TiltDiscTestType
{
	TDTT_TILTDISCTESTINS,
	TDTT_TILTDISCTESTDATA,
	TDTT_NUMBER
};

/*/��б�̲���ָ���װ/*/
typedef struct TiltDiscIns
{
	double f_Collect;					//�ܾࣨ���ȣ�
	double f_Roll;						//����ࣨ���ȣ�
	double f_Pitch;						//�����ࣨ���ȣ�
};

/*/��б�̲������ݷ�װ/*/
typedef struct TiltDiscData
{
	int    i_TiltDiscState;				//��б��״̬ 0����δ����    1 �Ѿ�ִ��Ŀ��ָ��
	double f_Collect;					//�ܾࣨ���ȣ�
	double f_Roll;						//����ࣨ���ȣ�
	double f_Pitch;						//�����ࣨ���ȣ�
};


/***����Ϊ������ط�װ**************************************************************/




/***����Ϊ�ٿ�ָ����ط�װ**********************************************************/

enum OperationCommandType
{
	OCT_FLYINGTASKINS,					//��������ָ��
	OCT_PATHINS,						//·��ָ��
	OCT_HELICOPTERPARAMETER,			//ֱ��������ָ��
	OCT_CONTROLLERPARAMETER,			//���Ʋ���ָ��
	OCT_CAMERAINS,						//�����ָ��
	OCT_NUMBER
};

/***����Ϊ��������ָ����ط�װ*********************/
enum FlyingTaskInsType
{
	FTT_CHECKALLSETTING,				//�����������
	FTT_CHECKALLSETTINGREPLY,			//����������ûظ�
	FTT_STARTTASK,						//��ʼ����
	FTT_STARTTASKREPLY,					//��ʼ����ظ�
	FTT_STARTSTOP,						//ֹͣ����
	FTT_STARTSTOPREPLY,					//ֹͣ����ظ�
	FTT_NUMBER
};


/*/
�����������
FTT_CHECKALLSETTING  ��FTT_CHECKALLSETTINGREPLY �����ñ��ṹ
/*/
typedef struct CheckSettingData
{
	int i_SettingState;						//�������״̬0ȫ���� ����ֵ��δԼ�����쳣
};

/*/
��ʼ��������
FTT_STARTTASK  FTT_STARTTASKREPLY �����ñ��ṹ
/*/
typedef struct StartTaskData
{
	int i_StartTaskData;					//0ȫ���� ����ֵ��δԼ�����쳣
};



/*/
������������
FTT_STARTSTOP  FTT_STARTSTOPREPLY �����ñ��ṹ
/*/
typedef struct StopTaskData
{
	int i_StopTaskData;						//0ȫ���� ����ֵ��δԼ�����쳣
};

/***����Ϊ��������ָ����ط�װ*********************/

/***����Ϊ·��ָ����ط�װ*********************/


enum PathInsType
{
	PIT_EMPTYPATHPOINTS,					//�������·����
	PIT_EMPTYPATHPOINTSREPLY,				//�������·����ظ�
	PIT_STARTLOADPATHPOINTS,				//��ʼ����·����
	PIT_STARTLOADPATHPOINTSREPLY,			//��ʼ����·����ظ�
	PIT_STOPLOADPATHPOINTS,					//��������·����
	PIT_STOPLOADPATHPOINTSREPLY,			//��������·����ظ�
	PIT_PATHPOINTDATA,						//·��������
	PIT_PATHPOINTDATAREPLY,					//·�������ݻظ�
	PIT_CHECKPATHPOINTS,					//���·����
	PIT_CHECKPATHPOINTSREPLY,				//���·����ظ�
	PIT_NUMBER

};

/*/���·����ָ��
PIT_EMPTYPATHPOINTS ��PIT_EMPTYPATHPOINTSREPLY �����ñ��ṹ
/*/
typedef struct EmptyPathPointsIns
{
	int i_EmptyNumber;						//��յ�·������� -1 �����Խ������
};


/*/��ʼ����·����ָ��
PIT_STARTLOADPATHPOINTS PIT_STARTLOADPATHPOINTS �����ñ��ṹ
/*/
typedef struct StartLoadPathPointsIns
{
	int i_StartLoadState;						//0���Խ���·���㵼�� 1 �����Խ���·���㵼��
};


/*/��������·����ָ��
PIT_STOPLOADPATHPOINTS PIT_STOPLOADPATHPOINTSREPLY �����ñ��ṹ
/*/
typedef struct StopLoadPathPointsIns
{
	int i_StopLoadState;						//-1 ������ֹͣ·���㵼�� ����·���㵼�����
};


/*/
·�������ݽṹ
PIT_PATHPOINTDATA PIT_PATHPOINTDATAREPLY �����ñ��ṹ
/*/
typedef struct PathPointData
{
	int		i_serial;								//·�������
	double	f_Coordinate_X;							//·��������X
	double	f_Coordinate_Y;							//·��������Y
	double	f_Coordinate_Z;							//·��������Z
	double	f_StayTime;								//ͣ��ʱ��
	double	f_reserve1;								//����1
	double	f_reserve2;								//����2
	double	f_reserve3;								//����3
};


/*/·���������ָ��
PIT_CHECKPATHPOINTS PIT_CHECKPATHPOINTSREPLY �����ñ��ṹ
/*/
typedef struct CheckPathPointsIns
{
	int i_CheckState;								//·�����״̬
};


/***����Ϊ·��ָ����ط�װ*********************/



//
//
//ֱ��������ָ����ȱ
//
//


//
//
//���Ʋ���ָ����ȱ
//
//



//
//
//���������ָ����ȱ
//
//

/***����Ϊ�ٿ�ָ����ط�װ**********************************************************/


/***����Ϊ���з�װ**********************************************************/

/*/�������ݷ�װ/*/
typedef struct FlyingData
{
	long l_TimeStamp;					//����ʱ���
	double f_Collective;				//�ܾ�
	double f_Roll;						//����Ƕ�
	double f_Pitch;						//�����Ƕ�
	double f_Tail;						//β����
	
	double f_N_Pos_Target;				//X����Ŀ�걱λ��
	double f_E_Pos_Target;				//Y����Ŀ�궫λ��
	double f_D_Pos_Target;				//Z����Ŀ����λ��

	double f_N_Pos;						//X��ǰ��λ��
	double f_E_Pos;						//Y��ǰ��λ��
	double f_D_Pos;						//Z��ǰ��λ��

	double f_N_Speed_Target;			//X����Ŀ�걱�ٶ�
	double f_E_Speed_Target;			//Y����Ŀ�궫�ٶ�			
	double f_D_Speed_Target;			//Z����Ŀ�����ٶ�

	double f_N_Speed;					//X��ǰ���ٶ�
	double f_E_Speed;					//Y��ǰ���ٶ�			
	double f_D_Speed;					//Z��ǰ���ٶ�

	double f_N_Acc_Target;				//x����Ŀ����ٶ�
	double f_E_Acc_Target;				//y����Ŀ����ٶ�
	double f_D_Acc_Target;				//z����Ŀ����ٶ�

	double f_N_Acc;						//x��ǰ���ٶ�
	double f_E_Acc;						//y��ǰ���ٶ�
	double f_D_Acc;						//z��ǰ���ٶ�

	double f_phi_Target;				//����Ŀ������
	double f_theta_Target;				//����Ŀ�긩����
	double f_psi_Target;				//����Ŀ�꺽���

	double f_phi;						//��ǰ�����
	double f_theta;						//��ǰ������
	double f_psi;						//��ǰ�����

	double f_phi_Acc_Target;			//����Ŀ�����Ǽ��ٶ�
	double f_theta_Acc_Target;			//����Ŀ�긩���Ǽ��ٶ�
	double f_psi_Acc_Target;			//����Ŀ�꺽��Ǽ��ٶ�

	double f_phi_Acc;					//��ǰ����Ǽ��ٶ�
	double f_theta_Acc;					//��ǰ�����Ǽ��ٶ�
	double f_psi_Acc;					//��ǰ����Ǽ��ٶ�
};


/***����Ϊ���з�װ**********************************************************/



//
//
//��������δ����
//
//

#endif