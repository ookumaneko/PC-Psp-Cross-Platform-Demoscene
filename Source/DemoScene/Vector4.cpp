#include "Vector4.h"
#include "Vector3.h"

//--------------------------------------//
//---------------Common Methods---------//
//--------------------------------------//


Vector4::Vector4(void)
{
	_vec.x = 0;
	_vec.y = 0;
	_vec.z = 0;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	_vec.x = x;
	_vec.y = y;
	_vec.z = z;
	_vec.w = w;
}

Vector4::~Vector4(void)
{
}

float& Vector4::X()
{
	return _vec.x;
}

float Vector4::X() const
{
	return _vec.x;
}

float& Vector4::Y()
{
	return _vec.y;
}

float Vector4::Y() const
{
	return _vec.y;
}

float& Vector4::Z()
{
	return _vec.z;
}

float Vector4::Z() const
{
	return _vec.z;
}

float& Vector4::W()
{
	return _vec.w;
}

float Vector4::W() const
{
	return _vec.w;
}

float Vector4::GetX() const
{
	return _vec.x;
}

float Vector4::GetY() const
{
	return _vec.y;
}

float Vector4::GetZ() const
{
	return _vec.z;
}

void Vector4::SetX(float x)
{
	_vec.x = x;
}

inline void Vector4::SetY(float y)
{
	_vec.y = y;
}

inline void Vector4::SetZ(float z)
{
	_vec.z = z;
}

