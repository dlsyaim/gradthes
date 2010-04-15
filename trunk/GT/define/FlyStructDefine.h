#ifndef _HELISYS_FLYSTRUCTDEFINE_H_
#define _HELISYS_FLYSTRUCTDEFINE_H_

#define FLYSTATEGROUPNUMBER		50

typedef struct ServoActorTstInsData
{
	char	ActorSerial;
	float	SetPWM;
}*pServoActorTstInsData;


typedef struct ThrottleTstInsData
{
	float	SetPWM;
}*pThrottleTstInsData;


typedef struct TiltDiscTstInsData
{
	float	CollectSetAngle;
	float	RollSetAngle;
	float	PitchetAngle;
}*pTiltDiscTstInsData;


typedef struct IMUTestData
{
	char	IMUState;					 
	float	N_Speed;				 
	float	E_Speed;				 
	float	D_Speed;				 
	float	N_Acc;					 
	float	E_Acc;					 
	float	D_Acc;					 
	float	phi;					 
	float	theta;					 
	float	psi;					 
}*pIMUTestData;


typedef struct GPSTestData
{
	char	GPSState;					 
	float	N_Pos;				 
	float	E_Pos;				 
	float	D_Pos;
}*pGPSTestData;


typedef struct OPTTRACETestData
{
	char	OPTState;					 
	float	N_Pos;				 
	float	E_Pos;				 
	float	D_Pos;					 
	float	N_Speed;				 
	float	E_Speed;				 
	float	D_Speed;				 
	float	N_Acc;					 
	float	E_Acc;					 
	float	D_Acc;					 
	float	phi;					 
	float	theta;					 
	float	psi;						 
	float	phi_Acc;				 
	float	theta_Acc;				 
	float	psi_Acc;				 
}*pOPTTRACETestData;


typedef struct  ServoActorData
{
	float	a1MeansureAng[5];		
	float	a1PWMValue[5];
	float	a2MeansureAng[5];		
	float	a2PWMValue[5];
	float	a3MeansureAng[5];		
	float	a3PWMValue[5];
	float	a4MeansureAng[5];	
	float	a4PWMValue[5];
}*pServoActorData;


typedef struct TiltDiscData
{
	float	CommandAngs[10][3];
	float   MeansureAngs[10][3];
}*pTiltDiscData;


typedef struct  PathPointData
{
	int	serial;							 
	float	Coordinate_X;
	float	Coordinate_Y;
	float	Coordinate_Z;
	float	StayTime;
	float	reserve1;
	float	reserve2;
	float	reserve3;
}*pPathPointData;

typedef struct FlyState
{	
	float	N_Pos;				 
	float	E_Pos;				 
	float	D_Pos;
	
	float	N_Speed;				 
	float	E_Speed;				 
	float	D_Speed;
		
	float	N_Speed_ACC;				 
	float	E_Speed_ACC;				 
	float	D_Speed_ACC;
				 				 
	short	phi;					 
	short	theta;					 
	short	psi;

	short	actor1ang;
	short	actor2ang;
	short	actor3ang;
	short	actor4ang;
}*pFlyState;


typedef struct FlyStateGroup
{	
	unsigned short	serial;
	struct FlyState states[FLYSTATEGROUPNUMBER];
}*pFlyStateGroup;



typedef struct HeliBodyPara
{
	double mass;      //质量(kg)
	double Ixx;    //转动惯量(kg * m^2)
	double Iyy;
	double Izz;
	double S_frontal; // 从机头前方投影面积
	double S_side;    //  侧面投影面积
	double S_vert;    //  垂直投影面积
}*pHeliBodyPara;

typedef struct  HeliMainrotorPara
{
	// MR radius (m)
	double	radius_mr;
	// blade lift curve slope (Clalpha */rad) 升力曲线斜率
	double	lift_curve_slope_mr;
	// number of MR blades
	double	blades_mr;
	// chord of MR blade (m)
	double	chord_mr;
	// MR equivelent hinge offset ()
	double	hinge_offset_mr;
	// MR blade flapping inertial (kg * m^2)
	double	I_b_mr;
	// MR blade zero lift drag coefficent 
	double	zero_lift_drag_coeff_mr;
	// MR max thrust coeficent
	double	max_thrust_coeff_mr;
	// flapping stiffness
	double	kc_mr;
	// MR total thrust (N)
	double	thrust_mr;
	// MR induced velocity (m/s)
	double	v_induced_mr;
	// MR vertical distance of hub to aircraft CG (m)
	double	h_hub_to_cg_mr;
	// MR horizontal distance of hub to aircraft CG (m)
	double	d_hub_to_cg_mr;
	// tip speed (m/s)
	double	v_tip_mr;
	// MR power (W)
	double	power_mr;
	// total MR torque (N*m)
	double	torque_mr;
	// MR revolutions per minute
	double	rpm_mr;
	// MR lock number
	double lock_number_mr;
	// angular velocity of rotor (rad/s)
	double	omega_mr;
	// TPP time constant (sec)
	double tau_mr;
	// solidity of rotor disk
	double sigma_mr;
}*pHeliMainrotorPara;


/*
 * Tail Rotor Parameters
 */
typedef struct  HeliTailrotorPara
{
	// TR blade lift curve slope (Clalpha */rad)
	double	lift_curve_slope_tr;
	// number of TR blades
	double	blades_tr;
	// TR blade chord (m)
	double	chord_tr;
	// TR radius (m)
	double	radius_tr;	
	// TR blade zero lift drag coefficient
	double	zero_lift_drag_coeff_tr;	
	// TR max thrust coefficient
	double	max_trust_coeff_tr;
	// horizontal distance of hub to aircraft CG (m)
	double	d_hub_to_cg_tr;
	// vertical distance of hub to aircraft CG (m)
	double	h_hub_to_cg_tr;
	// angular velocity of rotor (rad/s)
	double	omega_tr;
	// TR thrust (N)
	double	thrust_tr;
	// TR induced velocity
	double	v_induced_tr;
	// TR power (W)
	double	power_tr; 
	// TR revolutions per minute
	double	rpm_tr;

}*pHeliTailrotorPara;


typedef struct HelicopterPara
{
	struct HeliBodyPara				BodyPara;
	struct HeliMainrotorPara		MainrotorPara;
	struct HeliTailrotorPara		TailrotorPara;
}*pHelicopterPara;


typedef struct ControlPara
{
	char	paraname[20];
	char	type;
	bool	vb;
	long	vl;
	float	vf;
}*pControlPara;







#endif