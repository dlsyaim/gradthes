#pragma once

class CGyro
{
public:
	CGyro(double _roll = 0.0, double _pitch = 0.0, double _heading = 0.0, double _rollVel = 0.0, double _pitchVel = 0.0, double _headingVel = 0.0):
	roll(_roll),
	pitch(_pitch),
	heading(_heading),
	rollVel(_rollVel),
	pitchVel(_pitchVel),
	headingVel(_headingVel)
	{}
	~CGyro(void);

	inline void setRoll(double roll) {this->roll = roll;}
	inline double getRoll(void) {return roll;}

	inline void setPitch(double pitch) {this->pitch = pitch;}
	inline double getPitch(void) {return pitch;}

	inline void setHeading(double heading) {this->heading = heading;}
	inline double getHeading(void) {return heading;}

	inline void setRollVel(double rollVel) {this->rollVel = rollVel;}
	inline double getRollVel(void) {return rollVel;}

	inline void setPitchVel(double rollVel) {this->pitchVel = pitchVel;}
	inline double getPitchVel(void) {return pitchVel;}

	inline void setHeadingVel(double headingVel) {this->headingVel = headingVel;}
	inline double getHeadingVel(void) {return headingVel;}

private:
	double roll, pitch, heading;
	double rollVel, pitchVel, headingVel;
};
