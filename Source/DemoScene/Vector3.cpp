#include "Vector3.h"

//--------------------------------------//
//---------------Common Methods---------//
//--------------------------------------//


Vector3::Vector3(void)
{
	_vec.x = 0;
	_vec.y = 0;
	_vec.z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	_vec.x = x;
	_vec.y = y;
	_vec.z = z;
}

Vector3::~Vector3(void)
{
}

float& Vector3::X()
{
	return _vec.x;
}

float Vector3::X() const
{
	return _vec.x;
}

float& Vector3::Y()
{
	return _vec.y;
}

float Vector3::Y() const
{
	return _vec.y;
}

float& Vector3::Z()
{
	return _vec.z;
}

float Vector3::Z() const
{
	return _vec.z;
}

float Vector3::GetX() const
{
	return _vec.x;
}

float Vector3::GetY() const
{
	return _vec.y;
}

float Vector3::GetZ() const
{
	return _vec.z;
}

void Vector3::SetX(float x)
{
	_vec.x = x;
}

inline void Vector3::SetY(float y)
{
	_vec.y = y;
}

inline void Vector3::SetZ(float z)
{
	_vec.z = z;
}

void Vector3::Zero()
{
	_vec.x = 0;
	_vec.y = 0;
	_vec.z = 0;
}

void Vector3::Zero(Vector3 &out)
{
	out._vec.x = 0;
	out._vec.y = 0;
	out._vec.z = 0;
}
