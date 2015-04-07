#if defined(_PSP_VER)

#include "Vector2.h"
#include <libvfpu.h>

//--------------------Operators-----------------------//

Vector2& Vector2::operator =(const Vector2 &rhs)
{
	_vec.x = rhs.X();
	_vec.y = rhs.Y();

	return *this;
}

bool Vector2::operator ==(const Vector2 &rhs)
{
	return ( _vec.x == rhs.X() && _vec.y == rhs.Y() );
}

bool Vector2::operator !=(const Vector2 &rhs)
{
	return !( _vec.x == rhs.X() && _vec.y == rhs.Y() );
}

Vector2 Vector2::operator +(const Vector2 &rhs) const
{
	Vector2 ret;
	sceVfpuVector2Add( &ret._vec, &_vec, &rhs._vec );
	return ret;
}

Vector2& Vector2::operator +=(const Vector2 &rhs)
{
	sceVfpuVector2Add( &_vec, &_vec, &rhs._vec );
	return *this;
}

Vector2 Vector2::operator -(const Vector2 &rhs) const
{
	Vector2 ret;
	sceVfpuVector2Sub( &ret._vec, &_vec, &rhs._vec );
	return ret;
}

Vector2& Vector2::operator -=(const Vector2 &rhs)
{
	sceVfpuVector2Sub( &_vec, &_vec, &rhs._vec );
	return *this;
}

Vector2 Vector2::operator *(const float scalar) const
{
	Vector2 ret;
	sceVfpuVector2Scale( &ret._vec, &_vec, scalar );
	return ret;
}

Vector2& Vector2::operator *=(const float scalar)
{
	sceVfpuVector2Scale( &_vec, &_vec, scalar );
	return *this;
}

//---------------------End of Operators-----------------//

//--------------Start of Arthmetric Method--------------//
void Vector2::Add(const Vector2 &rhs)
{
	sceVfpuVector2Add( &_vec, &_vec, &rhs._vec );
}

void Vector2::Add(const Vector2 &vec1, const Vector2 &vec2, Vector2 &out)
{
	sceVfpuVector2Add( &out._vec, &vec1._vec, &vec2._vec );
}

void Vector2::Subtract(const Vector2 &rhs)
{
	sceVfpuVector2Sub( &_vec, &_vec, &rhs._vec );
}

void Vector2::Subtract(const Vector2 &vec1, const Vector2 &vec2, Vector2 &out)
{
	sceVfpuVector2Sub( &out._vec, &vec1._vec, &vec2._vec );
}

void Vector2::Multiply(const Vector2 &rhs)
{
	sceVfpuVector2Mul( &_vec, &_vec, &rhs._vec );
}

void Vector2::Multiply(const Vector2 &vec1, const Vector2 &vec2, Vector2 &out)
{
	sceVfpuVector2Mul( &out._vec, &vec1._vec, &vec2._vec );	
}

void Vector2::Multiply(float scalar)
{
	sceVfpuVector2Scale( &_vec, &_vec, scalar );
}

void Vector2::Multiply(float scalar, Vector2 &in, Vector2 &out)
{
	sceVfpuVector2Scale( &out._vec, &in._vec, scalar );
}

void Vector2::Divide(const Vector2 &rhs)
{
	sceVfpuVector2Div( &_vec, &_vec, &rhs._vec );
}

void Vector2::Divide(const Vector2 &vec1, const Vector2 &vec2, Vector2 &out)
{
	sceVfpuVector2Div( &out._vec, &vec1._vec, &vec2._vec );
}

//----------------End of Arthmetric Method--------------//

//----------------Start of Vector Operations--------------//

float Vector2::DotProduct(const Vector2 &rhs)
{
	return sceVfpuVector2InnerProduct( &_vec, &rhs._vec );
}

float Vector2::DotProduct(const Vector2 &vec1, const Vector2 &vec2)
{
	return sceVfpuVector2InnerProduct( &vec1._vec, &vec2._vec );
}

Vector2 Vector2::Lerp(Vector2 &start, Vector2 &end, float amount)
{
	Vector2 ret;
	sceVfpuVector2Lerp( &ret._vec, &start._vec, &end._vec, amount );
	return ret;
}

void Vector2::Lerp(Vector2 &start, Vector2 &end, float amount, Vector2 &out)
{
	sceVfpuVector2Lerp( &out._vec, &start._vec, &end._vec, amount );
}

float Vector2::MagnitudeSquare()
{
	return ( _vec.x * _vec.x ) + ( _vec.y * _vec.y );
}

float Vector2::MagnitudeSquare(const Vector2 &rhs)
{
	return ( rhs._vec.x * rhs._vec.x ) + ( rhs._vec.y * rhs._vec.y );
}

void Vector2::Normalize()
{
	sceVfpuVector2Normalize( &_vec, &_vec );
}

void Vector2::Normalize(const Vector2 &in, Vector2 &out)
{
	sceVfpuVector2Normalize( &out._vec, &in._vec );
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

//----------------end of Vector Operations--------------//

#endif