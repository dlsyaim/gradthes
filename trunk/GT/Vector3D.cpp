#include "stdafx.h"
#include "Vector3D.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Set the vector's three attributes.
void CVector3::Set(float newX, float newY, float newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

// Calculate the cross product.
CVector3 CVector3::CrossProduct(const CVector3 &rhs) const
{
	return CVector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

// Calculate the dot product.
float CVector3::DotProduct(const CVector3 &rhs) const
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

// Unitization
void CVector3::Normalize()
{
	float length = GetLength();

	if(length == 1 || length == 0)
		return;

	float scaleFactor = 1.0f / length;
	x *= scaleFactor;
	y *= scaleFactor;
	z *= scaleFactor;
}

// Unitization
CVector3 CVector3::GetNormalized() const
{
	CVector3 result(*this);

	result.Normalize();

	return result;
}

// Calculate the length of the vector.
float CVector3::GetLength() const
{
	return (float)sqrt(( x * x) + (y * y) + (z * z));
}

// Calculate the square of the length of the vector.
float CVector3::GetSquaredLength() const
{
	return (x * x) + (y * y) + (z * z);
}

// Rotate the vector around the X axis and return the rotated vector.
CVector3 CVector3::GetRotatedX(double angle) const
{
	if(angle == 0.0)
		return (*this);

	float sinAngle = (float)sin(M_PI * angle / 180);
	float cosAngle = (float)cos(M_PI * angle / 180);

	return CVector3(x, y * cosAngle - z * sinAngle, y * sinAngle + z * cosAngle);
}

// Rotate the vector around the X axis.
void CVector3::RotateX(double angle)
{
	(*this) = GetRotatedX(angle);
}

// Rotate the vector around the Y axis and return the rotated vector.
CVector3 CVector3::GetRotatedY(double angle) const
{
	if(angle == 0.0)
		return (*this);

	float sinAngle = (float)sin(M_PI * angle / 180);
	float cosAngle = (float)cos(M_PI * angle / 180);

	return CVector3(x * cosAngle + z * sinAngle, y, -x * sinAngle + z * cosAngle);
}

/// Rotate the vector around the Y axis.
void CVector3::RotateY(double angle)
{
	(*this) = GetRotatedY(angle);
}

// Rotate the vector around the Z axis and return the rotated vector.
CVector3 CVector3::GetRotatedZ(double angle) const
{
	if(angle == 0.0)
		return (*this);

	float sinAngle = (float)sin(M_PI * angle / 180);
	float cosAngle = (float)cos(M_PI * angle / 180);
	
	return CVector3(x * cosAngle - y * sinAngle, x * sinAngle + y * cosAngle, z);
}

// Rotate the vector around the Z axis 
void CVector3::RotateZ(double angle)
{
	(*this) = GetRotatedZ(angle);
}

// Rotate the vector around the specified axis and return the rotated vector.
CVector3 CVector3::GetRotatedAxis(double angle, const CVector3 & axis) const
{
	if(angle == 0.0)
		return (*this);

	// Normalize the axis.
	CVector3 u = axis.GetNormalized();

	CVector3 result;

	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	result.x  = (float)(cosTheta + (1 - cosTheta) * u.x * u.x) * x;
	result.x += (float)((1 - cosTheta) * u.x * u.y - u.z * sinTheta) * y;
	result.x += (float)((1 - cosTheta) * u.x * u.z + u.y * sinTheta) * z;

	result.y  = (float)((1 - cosTheta) * u.x * u.y + u.z * sinTheta) * x;
	result.y += (float)(cosTheta + (1 - cosTheta) * u.y * u.y) * y;
	result.y += (float)((1 - cosTheta) * u.y * u.z - u.x * sinTheta) * z;

	result.z  = (float)((1 - cosTheta) * u.x * u.z - u.y * sinTheta) * x;
	result.z += (float)((1 - cosTheta) * u.y * u.z + u.x * sinTheta) * y;
	result.z += (float)(cosTheta + (1 - cosTheta) * u.z * u.z) * z;

	return result;
}

// Rotate the vector around the specified axis.
void CVector3::RotateAxis(double angle, const CVector3 & axis)
{
	(*this) = GetRotatedAxis(angle, axis);
}

// Override operator +
CVector3 CVector3::operator+(const CVector3 &rhs) const
{
	return CVector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

// Override operator -
CVector3 CVector3::operator-(const CVector3 &rhs) const
{
	return CVector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

// Override operator *
CVector3 CVector3::operator*(const float rhs) const
{
	return CVector3(x * rhs, y * rhs, z * rhs);
}

// Override operator /
CVector3 CVector3::operator/(const float rhs) const
{
	return (rhs == 0.0f) ? CVector3(0.0f, 0.0f, 0.0f) : CVector3(x / rhs, y / rhs, z / rhs);
}

// Whether two vectors are the same.
bool CVector3::operator==(const CVector3 & rhs) const
{
	if(x == rhs.x && y == rhs.y && z == rhs.z)
		return true;

	return false;
}

// Whether two vectors are different.
bool CVector3::operator!=(const CVector3 & rhs) const
{
	return !((*this) == rhs);
}
