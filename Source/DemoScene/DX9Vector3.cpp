#ifndef _PSP_VER
#include "Vector3.h"


Vector3& Vector3::operator =(const Vector3 &rhs)
{
	_vec = rhs._vec;
	return *this;
}

Vector3 Vector3::operator +(const Vector3& rhs) const
{
	Vector3 ret;
	D3DXVec3Add( &ret._vec, &_vec, &rhs._vec );
	return ret;
}

Vector3 Vector3::operator- (const Vector3& rhs) const
{
	Vector3 ret;
	D3DXVec3Subtract( &ret._vec, &_vec, &rhs._vec );
	return ret;
}

Vector3 Vector3::operator* (const float scalar) const
{
	Vector3 ret;
	D3DXVec3Scale( &ret._vec, &_vec, scalar );
	return ret;	
}

Vector3& Vector3::operator+= (const Vector3& rhs)
{
	D3DXVec3Add( &_vec, &_vec, &rhs._vec );
	return *this;
}

Vector3& Vector3::operator-= (const Vector3& rhs)
{
	D3DXVec3Subtract( &_vec, &_vec, &rhs._vec );
	return *this;
}

Vector3& Vector3::operator*= (const float scalar)
{
	D3DXVec3Scale( &_vec, &_vec, scalar );
	return *this;
}

bool Vector3::operator== (const Vector3& rhs)
{
	if ( _vec == rhs._vec )
		return true;
	else
		return false;
}

bool Vector3::operator!= (const Vector3& rhs)
{
	return !( *this == rhs );
}

void Vector3::Add(const Vector3& rhs)
{
	_vec += rhs._vec;
}

void Vector3::Add(const Vector3& vec1, const Vector3& vec2, Vector3& out)
{
	D3DXVec3Add( &out._vec, &vec1._vec, &vec2._vec );
}

void Vector3::Subtract(const Vector3& rhs)
{
	_vec = _vec - rhs._vec;
}

void Vector3::Subtract(const Vector3& vec1, const Vector3& vec2, Vector3& out)
{
	D3DXVec3Subtract( &out._vec, &vec1._vec, &vec2._vec );
}

void Vector3::Multiply(const Vector3& rhs)
{
	_vec.x *= rhs._vec.x;
	_vec.y *= rhs._vec.y;
	_vec.z *= rhs._vec.z;
}

void Vector3::Multiply(float scalar)
{
	_vec *= scalar;
}

void Vector3::Multiply(const Vector3& vec1, const Vector3& vec2, Vector3& out)
{
	out._vec.x = vec1._vec.x * vec2._vec.x;
	out._vec.y = vec1._vec.y * vec2._vec.y;
	out._vec.z = vec1._vec.z * vec2._vec.z;
}

void Vector3::Multiply(float scalar, Vector3& in, Vector3& out)
{
	out._vec = in._vec * scalar;
}

void Vector3::Divide(const Vector3& rhs)
{
	_vec.x /= rhs._vec.x;
	_vec.y /= rhs._vec.y;
	_vec.z /= rhs._vec.z;
}

void Vector3::Divide(const Vector3& vec1, const Vector3& vec2, Vector3& out)
{
	out._vec.x = vec1._vec.x / vec2._vec.x;
	out._vec.y = vec1._vec.y / vec2._vec.y;
	out._vec.z = vec1._vec.z / vec2._vec.z;
}

void Vector3::Normalize()
{
	D3DXVec3Normalize( &_vec, &_vec ); 
}

void Vector3::Normalize(const Vector3& in, Vector3& out)
{
	D3DXVec3Normalize( &out._vec, &in._vec );
}

float Vector3::MagnitudeSquare(void)
{
	return D3DXVec3LengthSq( &_vec );
}

float Vector3::MagnitudeSquare(const Vector3& rhs)
{
	return D3DXVec3LengthSq( &rhs._vec );
}

Vector3 Vector3::Lerp(Vector3 &start, Vector3 &end, float amount)
{
	Vector3 ret;
	D3DXVec3Lerp( &ret._vec, &start._vec, &end._vec, amount );
	return ret;
}

void Vector3::Lerp(Vector3 &start, Vector3 &end, float amount, Vector3 &out)
{
	D3DXVec3Lerp( &out._vec, &start._vec, &end._vec, amount );
}

float Vector3::DotProduct(const Vector3& rhs)
{
	return D3DXVec3Dot( &_vec, &rhs._vec );
}

float Vector3::DotProduct(const Vector3& vec1, const Vector3& vec2)
{
	return D3DXVec3Dot( &vec1._vec, &vec2._vec );
}

Vector3 Vector3::CrossProduct(const Vector3& rhs, const Vector3& rhs2)
{
	D3DXVec3Cross( &_vec, &rhs._vec, &rhs2._vec );
	return *this;
}

void Vector3::CrossProduct(const Vector3& vec1, const Vector3& vec2, Vector3& out)
{
	D3DXVec3Cross( &out._vec, &vec1._vec, &vec2._vec );
}



#endif