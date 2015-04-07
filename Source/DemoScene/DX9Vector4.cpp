#ifndef _PSP_VER

#include "Vector4.h"
#include "Vector3.h"


//--------------------Operators-----------------------//


Vector4& Vector4::operator =(const Vector4 &rhs)
{
	_vec = rhs._vec;
	return *this;
}

Vector4 Vector4::operator +(const Vector4& rhs) const
{
	Vector4 ret;
	D3DXVec4Add( &ret._vec, &_vec, &rhs._vec );
	return ret;
}

Vector4 Vector4::operator- (const Vector4& rhs) const
{
	Vector4 ret;
	D3DXVec4Subtract( &ret._vec, &_vec, &rhs._vec );
	return ret;
}

Vector4 Vector4::operator* (const float scalar) const
{
	Vector4 ret;
	D3DXVec4Scale( &ret._vec, &_vec, scalar );
	return ret;	
}

Vector4& Vector4::operator+= (const Vector4& rhs)
{
	D3DXVec4Add( &_vec, &_vec, &rhs._vec );
	return *this;
}

Vector4& Vector4::operator-= (const Vector4& rhs)
{
	D3DXVec4Subtract( &_vec, &_vec, &rhs._vec );
	return *this;
}

Vector4& Vector4::operator*= (const float scalar)
{
	D3DXVec4Scale( &_vec, &_vec, scalar );
	return *this;
}

bool Vector4::operator== (const Vector4& rhs)
{
	if ( _vec == rhs._vec )
		return true;
	else
		return false;
}

bool Vector4::operator!= (const Vector4& rhs)
{
	return !( *this == rhs );
}


//---------------------End of Operators-----------------//

//--------------Start of Arthmetric Method--------------//


void Vector4::Add(const Vector4& rhs)
{
	_vec += rhs._vec;
}

void Vector4::Add(const Vector4& vec1, const Vector4& vec2, Vector4& out)
{
	D3DXVec4Add( &out._vec, &vec1._vec, &vec2._vec );
}

void Vector4::Subtract(const Vector4& rhs)
{
	_vec = _vec - rhs._vec;
}

void Vector4::Subtract(const Vector4& vec1, const Vector4& vec2, Vector4& out)
{
	D3DXVec4Subtract( &out._vec, &vec1._vec, &vec2._vec );
}

void Vector4::Multiply(const Vector4& rhs)
{
	_vec.x *= rhs._vec.x;
	_vec.y *= rhs._vec.y;
	_vec.z *= rhs._vec.z;
}

void Vector4::Multiply(float scalar)
{
	_vec *= scalar;
}

void Vector4::Multiply(const Vector4& vec1, const Vector4& vec2, Vector4& out)
{
	out._vec.x = vec1._vec.x * vec2._vec.x;
	out._vec.y = vec1._vec.y * vec2._vec.y;
	out._vec.z = vec1._vec.z * vec2._vec.z;
}

void Vector4::Multiply(float scalar, Vector4& in, Vector4& out)
{
	out._vec = in._vec * scalar;
}

void Vector4::Divide(const Vector4& rhs)
{
	_vec.x /= rhs._vec.x;
	_vec.y /= rhs._vec.y;
	_vec.z /= rhs._vec.z;
}

void Vector4::Divide(const Vector4& vec1, const Vector4& vec2, Vector4& out)
{
	out._vec.x = vec1._vec.x / vec2._vec.x;
	out._vec.y = vec1._vec.y / vec2._vec.y;
	out._vec.z = vec1._vec.z / vec2._vec.z;
}

void Vector4::Normalize()
{
	D3DXVec4Normalize( &_vec, &_vec ); 
}

void Vector4::Normalize(const Vector4& in, Vector4& out)
{
	D3DXVec4Normalize( &out._vec, &in._vec );
}

float Vector4::MagnitudeSquare(void)
{
	return D3DXVec4LengthSq( &_vec );
}

float Vector4::MagnitudeSquare(const Vector4& rhs)
{
	return D3DXVec4LengthSq( &rhs._vec );
}

Vector4 Vector4::Lerp(Vector4 &start, Vector4 &end, float amount)
{
	Vector4 ret;
	D3DXVec4Lerp( &ret._vec, &start._vec, &end._vec, amount );
	return ret;
}

void Vector4::Lerp(Vector4 &start, Vector4 &end, float amount, Vector4 &out)
{
	D3DXVec4Lerp( &out._vec, &start._vec, &end._vec, amount );
}

float Vector4::DotProduct(const Vector4& rhs)
{
	return D3DXVec4Dot( &_vec, &rhs._vec );
}

float Vector4::DotProduct(const Vector4& vec1, const Vector4& vec2)
{
	return D3DXVec4Dot( &vec1._vec, &vec2._vec );
}

Vector4 Vector4::CrossProduct(const Vector4& rhs, const Vector4& rhs2)
{
	D3DXVec4Cross( &_vec, &_vec, &rhs._vec, &rhs2._vec );
	return *this;
}

void Vector4::CrossProduct(const Vector4& vec1, const Vector4& vec2, Vector4& out)
{
	D3DXVec4Cross( &out._vec, &out._vec, &vec1._vec, &vec2._vec );
}

void Vector4::Zero()
{
	_vec.x = 0;
	_vec.y = 0;
	_vec.z = 0;
}

void Vector4::Zero(Vector4 &out)
{
	out._vec.x = 0;
	out._vec.y = 0;
	out._vec.z = 0;
}



#endif