
#if !defined AN_TOOLS_H_ 
#define AN_TOOLS_H_ 


#include <winsock.h>

#define  uint32_t    unsigned int
#define int32_t      int   

#define RESERVED_SPACE 25
#define FG_NET_CTRLS_VERSION 27
class FGNetCtrls {

public:

    enum {
        FG_MAX_ENGINES = 4,
        FG_MAX_WHEELS = 16,
        FG_MAX_TANKS = 8
    };

    uint32_t version;		         // increment when data values change

    // Aero controls
    double aileron;		         // -1 ... 1
    double elevator;		         // -1 ... 1
    double rudder;		         // -1 ... 1
    double aileron_trim;	         // -1 ... 1
    double elevator_trim;	         // -1 ... 1
    double rudder_trim;		         // -1 ... 1
    double flaps;		         //  0 ... 1
    double spoilers;
    double speedbrake;

    // Aero control faults
    uint32_t flaps_power;                 // true = power available
    uint32_t flap_motor_ok;

    // Engine controls
    uint32_t num_engines;		 // number of valid engines
    uint32_t master_bat[FG_MAX_ENGINES];
    uint32_t master_alt[FG_MAX_ENGINES];
    uint32_t magnetos[FG_MAX_ENGINES];
    uint32_t starter_power[FG_MAX_ENGINES];// true = starter power
    double throttle[FG_MAX_ENGINES];     //  0 ... 1
    double mixture[FG_MAX_ENGINES];      //  0 ... 1
    double condition[FG_MAX_ENGINES];    //  0 ... 1
    uint32_t fuel_pump_power[FG_MAX_ENGINES];// true = on
    double prop_advance[FG_MAX_ENGINES]; //  0 ... 1
    uint32_t feed_tank_to[4];
    uint32_t reverse[4];


    // Engine faults
    uint32_t engine_ok[FG_MAX_ENGINES];
    uint32_t mag_left_ok[FG_MAX_ENGINES];
    uint32_t mag_right_ok[FG_MAX_ENGINES];
    uint32_t spark_plugs_ok[FG_MAX_ENGINES];  // false = fouled plugs
    uint32_t oil_press_status[FG_MAX_ENGINES];// 0 = normal, 1 = low, 2 = full fail
    uint32_t fuel_pump_ok[FG_MAX_ENGINES];

    // Fuel management
    uint32_t num_tanks;                      // number of valid tanks
    uint32_t fuel_selector[FG_MAX_TANKS];    // false = off, true = on
    uint32_t xfer_pump[5];                   // specifies transfer from array
                                             // value tank to tank specified by
                                             // int value
    uint32_t cross_feed;                     // false = off, true = on

    // Brake controls
    double brake_left;
    double brake_right;
    double copilot_brake_left;
    double copilot_brake_right;
    double brake_parking;
    
    // Landing Gear
    uint32_t gear_handle; // true=gear handle down; false= gear handle up

    // Switches
    uint32_t master_avionics;
    
        // nav and Comm
    double	comm_1;
    double	comm_2;
    double	nav_1;
    double	nav_2;

    // wind and turbulance
    double wind_speed_kt;
    double wind_dir_deg;
    double turbulence_norm;

    // temp and pressure
    double temp_c;
    double press_inhg;

    // other information about environment
    double hground;		         // ground elevation (meters)
    double magvar;		         // local magnetic variation in degs.

    // hazards
    uint32_t icing;                      // icing status could me much
                                         // more complex but I'm
                                         // starting simple here.

    // simulation control
    uint32_t speedup;		         // integer speedup multiplier
    uint32_t freeze;		         // 0=normal
				         // 0x01=master
				         // 0x02=position
				         // 0x04=fuel

    // --- New since FlightGear 0.9.10 (FG_NET_CTRLS_VERSION = 27)

    // --- Add new variables just before this line.

    uint32_t reserved[RESERVED_SPACE];	 // 100 bytes reserved for future use.
};


   
class  FGNetFDM {
	
public:
	
    enum {
        FG_MAX_ENGINES = 4,
			FG_MAX_WHEELS = 3,
			FG_MAX_TANKS = 4
    };
	
    uint32_t version;		// increment when data values change
    uint32_t padding;		// padding
	
    // Positions
    double longitude;		// geodetic (radians)
    double latitude;		// geodetic (radians)
    double altitude;		// above sea level (meters)
    float agl;			// above ground level (meters)
    float phi;			// roll (radians)
    float theta;		// pitch (radians)
    float psi;			// yaw or true heading (radians)
    float alpha;                // angle of attack (radians)
    float beta;                 // side slip angle (radians)
	
    // Velocities
    float phidot;		// roll rate (radians/sec)
    float thetadot;		// pitch rate (radians/sec)
    float psidot;		// yaw rate (radians/sec)
    float vcas;		        // calibrated airspeed
    float climb_rate;		// feet per second
    float v_north;              // north velocity in local/body frame, fps
    float v_east;               // east velocity in local/body frame, fps
    float v_down;               // down/vertical velocity in local/body frame, fps
    float v_wind_body_north;    // north velocity in local/body frame
	// relative to local airmass, fps
    float v_wind_body_east;     // east velocity in local/body frame
	// relative to local airmass, fps
    float v_wind_body_down;     // down/vertical velocity in local/body
	// frame relative to local airmass, fps
	
    // Accelerations
    float A_X_pilot;		// X accel in body frame ft/sec^2
    float A_Y_pilot;		// Y accel in body frame ft/sec^2
    float A_Z_pilot;		// Z accel in body frame ft/sec^2
	
    // Stall
    float stall_warning;        // 0.0 - 1.0 indicating the amount of stall
    float slip_deg;		// slip ball deflection
	
    // Pressure
    
    // Engine status
    uint32_t num_engines;	     // Number of valid engines
    uint32_t eng_state[FG_MAX_ENGINES];// Engine state (off, cranking, running)
    float rpm[FG_MAX_ENGINES];	     // Engine RPM rev/min
    float fuel_flow[FG_MAX_ENGINES]; // Fuel flow gallons/hr
    float fuel_px[FG_MAX_ENGINES];   // Fuel pressure psi
    float egt[FG_MAX_ENGINES];	     // Exhuast gas temp deg F
    float cht[FG_MAX_ENGINES];	     // Cylinder head temp deg F
    float mp_osi[FG_MAX_ENGINES];    // Manifold pressure
    float tit[FG_MAX_ENGINES];	     // Turbine Inlet Temperature
    float oil_temp[FG_MAX_ENGINES];  // Oil temp deg F
    float oil_px[FG_MAX_ENGINES];    // Oil pressure psi
	
    // Consumables
    uint32_t num_tanks;		// Max number of fuel tanks
    float fuel_quantity[FG_MAX_TANKS];
	
    // Gear status
    uint32_t num_wheels;
    uint32_t wow[FG_MAX_WHEELS];
    float gear_pos[FG_MAX_WHEELS];
    float gear_steer[FG_MAX_WHEELS];
    float gear_compression[FG_MAX_WHEELS];
	
    // Environment
    uint32_t cur_time;           // current unix time
	// FIXME: make this uint64_t before 2038
    int32_t warp;                // offset in seconds to unix time
    float visibility;            // visibility in meters (for env. effects)
	
    // Control surface positions (normalized values)
    float elevator;
    float elevator_trim_tab;
    float left_flap;
    float right_flap;
    float left_aileron;
    float right_aileron;
    float rudder;
    float nose_wheel;
    float speedbrake;
    float spoilers;
};


typedef struct FlyState			/*/飞行状态值/*/
{
	/*/地理坐标系位置/*/
	double NED_POS_X;
	double NED_POS_Y;
	double NED_POS_Z;
	/*/机体坐标线系线速度/*/
	double BODY_VEL_X;
	double BODY_VEL_Y;
	double BODY_VEL_Z;
	/*/机体坐标线系线加速度/*/
	double BODY_ACC_X;
	double BODY_ACC_Y;
	double BODY_ACC_Z;
	/*/机体坐标系-地理坐标系角度/*/
	double BODY_ANG_PHI;
	double BODY_ANG_THETA;
	double BODY_ANG_PSI;
	/*/角速度/*/
	double BODY_ANG_P;
	double BODY_ANG_Q;
	double BODY_ANG_R;
} *p_FlyState;


typedef struct FlyActorValue	/*/舵机输出量/*/
{
	double col;		/*/总距量/*/
	double lat;		/*/横向变距量/*/
	double lon;		/*/纵向变距量/*/
	double ped;		/*/尾距量/*/
} * p_FlyActorValue;


class CTools  
{
public:
	CTools();
	virtual ~CTools();
	static double htond(double d);
	static double ntohd(double d);
	static float htonf(float f);
	static float ntohf(float f);
};

#endif 
