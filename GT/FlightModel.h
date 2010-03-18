#pragma once

class CFlightModel
{
public:
	CFlightModel(std::string _name = NULL, double _mass = 0.0, double _length = 0.0, double _lengthOfMainBlade = 0.0, double _rpmOfMainBlade = 0.0) : 
	name(_name),
	mass(_mass),
	length(_length),
	lengthOfMainBlade(_lengthOfMainBlade),
	rpmOfMainBlade(_rpmOfMainBlade)
	{}
	~CFlightModel(void);

	inline void setName(std::string name) {this->name = name;}
	inline std::string getName(void) {return name;}

	inline void setMass(double mass) {this->mass = mass;}
	inline double getMass(void) {return mass;}

	inline void setLength(double length) {this->length = length;}
	inline double getLength(void) {return length;}

	inline void setLengthOfMainBlade(double lengthOfMainBlade) {this->lengthOfMainBlade = lengthOfMainBlade;}
	inline double getLengthOfMainBlade(void) {return lengthOfMainBlade;}

	inline void setRpmOfMainBlade(double rpmOfMainBlade) {this->rpmOfMainBlade = rpmOfMainBlade;}
	inline double getRpmOfMainBlade(void) {return rpmOfMainBlade;}

private:
	std::string name;
	double mass;
	double length;
	// 
	double lengthOfMainBlade;
	double rpmOfMainBlade;


};
