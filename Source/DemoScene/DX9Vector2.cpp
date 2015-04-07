#if !defined(_PSP_VER)

#include "Vector2.h"

Vector2& Vector2::operator =(const Vector2 &rhs)
{
	_vec = rhs._vec;
	return *this;
}

Vector2 Vector2::operator +(const Vector2& rhs) const
{
	Vector2 ret;
	D3DXVec2Add( &ret._vec, &_vec, &rhs._vec );
	return ret;
}

Vector2 Vector2::operator- (const Vector2& rhs) const
{
	Vector2 ret;
	D3DXVec2Subtract( &ret._vec, &_vec, &rhs._vec );
	return ret;
}

Vector2 Vector2::operator* (const float scalar) const
{
	Vector2 ret;
	D3DXVec2Scale( &ret._vec, &_vec, scalar );
	return ret;	
}

Vector2& Vector2::operator+= (const Vector2& rhs)
{
	D3DXVec2Add( &_vec, &_vec, &rhs._vec );
	return *this;
}

Vector2& Vector2::operator-= (const Vector2& rhs)
{
	D3DXVec2Subtract( &_vec, &_vec, &rhs._vec );
	return *this;
}

Vector2& Vector2::operator*= (const float scalar)
{
	D3DXVec2Scale( &_vec, &_vec, scalar );
	return *this;
}

bool Vector2::operator== (const Vector2& rhs)
{
	if ( _vec == rhs._vec )
		return true;
	else
		return false;
}

bool Vector2::operator!= (const Vector2& rhs)
{
	return !( *this == rhs );
}

void Vector2::Add(const Vector2& rhs)
{
	_vec += rhs._vec;
}

void Vector2::Add(const Vector2& vec1, const Vector2& vec2, Vector2& out)
{
	D3DXVec2Add( &out._vec, &vec1._vec, &vec2._vec );
}

void Vector2::Subtract(const Vector2& rhs)
{
	_vec = _vec - rhs._vec;
}

void Vector2::Subtract(const Vector2& vec1, const Vector2& vec2, Vector2& out)
{
	D3DXVec2Subtract( &out._vec, &vec1._vec, &vec2._vec );
}

void Vector2::Multiply(const Vector2& rhs)
{
	_vec.x *= rhs._vec.x;
	_vec.y *= rhs._vec.y;
}

void Vector2::Multiply(float scalar)
{
	_vec *= scalar;
}

void Vector2::Multiply(const Vector2& vec1, const Vector2& vec2, Vector2& out)
{
	out._vec.x = vec1._vec.x * vec2._vec.x;
	out._vec.y = vec1._vec.y * vec2._vec.y;
}

void Vector2::Multiply(float scalar, Vector2& in, Vector2& out)
{
	out._vec = in._vec * scalar;
}

void Vector2::Divide(const Vector2& rhs)
{
	_vec.x /= rhs._vec.x;
	_vec.y /= rhs._vec.y;
}

void Vector2::Divide(const Vector2& vec1, const Vector2& vec2, Vector2& out)
{
	out._vec.x = vec1._vec.x / vec2._vec.x;
	out._vec.y = vec1._vec.y / vec2._vec.y;
}

void Vector2::Normalize()
{
	D3DXVec2Normalize( &_vec, &_vec ); 
}

void Vector2::Normalize(const Vector2& in, Vector2& out)
{
	D3DXVec2Normalize( &out._vec, &in._vec );
}

float Vector2::MagnitudeSquare(void)
{
	return D3DXVec2LengthSq( &_vec );
}

float Vector2::MagnitudeSquare(const Vector2& rhs)
{
	return D3DXVec2LengthSq( &rhs._vec );
}

Vector2 Vector2::Lerp(Vector2 &start, Vector2 &end, float amount)
{
	Vector2 ret;
	D3DXVec2Lerp( &ret._vec, &start._vec, &end._vec, amount );
	return ret;
}

void Vector2::Lerp(Vector2 &start, Vector2 &end, float amount, Vector2 &out)
{
	D3DXVec2Lerp( &out._vec, &start._vec, &end._vec, amount );
}

float Vector2::DotProduct(const Vector2& rhs)
{
	return D3DXVec2Dot( &_vec, &rhs._vec );
}

float Vector2::DotProduct(const Vector2& vec1, const Vector2& vec2)
{
	return D3DXVec2Dot( &vec1._vec, &vec2._vec );
}

void Vector2::Zero()
{
	_vec.x = 0;
	_vec.y = 0;
}

void Vector2::Zero(Vector2 &out)
{
	out._vec.x = 0;
	out._vec.y = 0;
}

#endif