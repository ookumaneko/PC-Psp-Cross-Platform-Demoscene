#include "Vector2.h"

//--------------------------------------//
//---------------Common Methods---------//
//--------------------------------------//


Vector2::Vector2(void)
{
	_vec.x = 0;
	_vec.y = 0;
}

Vector2::Vector2(float x, float y)
{
	_vec.x = x;
	_vec.y = y;
}

Vector2::~Vector2(void)
{
}

float& Vector2::X()
{
	return _vec.x;
}

float Vector2::X() const
{
	return _vec.x;
}

float& Vector2::Y()
{
	return _vec.y;
}

float Vector2::Y() const
{
	return _vec.y;
}

float Vector2::GetX() const
{
	return _vec.x;
}

float Vector2::GetY() const
{
	return _vec.y;
}

void Vector2::SetX(float x)
{
	_vec.x = x;
}

inline void Vector2::SetY(float y)
{
	_vec.y = y;
}


