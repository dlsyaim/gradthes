#ifndef VECTOR3D_H
#define VECTOR3D_H

class CVector3
{
public:
	// Initialize
	CVector3(void) : x(0.0f), y(0.0f), z(0.0f) {}
	CVector3(float newX, float newY, float newZ) : x(newX), y(newY), z(newZ) {}
	CVector3(const float * rhs)	: x(*rhs), y(*(rhs+1)), z(*(rhs+2)) {}
	CVector3(const CVector3 & rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}

	// The destructor.
	~CVector3() {}

	// Set the vector's three attributes.
	void Set(float newX, float newY, float newZ);

	// Calculate the cross product.
	CVector3 CrossProduct(const CVector3 &rhs) const;

	// Calculate the dot product.
	float DotProduct(const CVector3 &rhs) const;

	// Unitization
	void Normalize();
	CVector3 GetNormalized() const;

	// Calculate the length of the vector.
	float GetLength() const;

	// Calculate the square of the length of the vector.
	float GetSquaredLength() const;

	// Vector's rotation
	void RotateX(double angle);
	CVector3 GetRotatedX(double angle) const;
	void RotateY(double angle);
	CVector3 GetRotatedY(double angle) const;
	void RotateZ(double angle);
	CVector3 GetRotatedZ(double angle) const;
	void RotateAxis(double angle, const CVector3 &axis);
	CVector3 GetRotatedAxis(double angle, const CVector3 &axis) const;

	// Operator override.
	CVector3 operator+(const CVector3 &rhs) const;
	CVector3 operator-(const CVector3 &rhs) const;
	CVector3 operator*(const float rhs) const;
	CVector3 operator/(const float rhs) const;

	bool operator==(const CVector3 &rhs) const;
	bool operator!=(const CVector3 &rhs) const;

	// Members
	float x;
	float y;
	float z;
};

#endif			// CVector3_H