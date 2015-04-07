#ifdef _PSP_VER
#include "Vector3.h"
#include <libvfpu.h>


//--------------------Operators-----------------------//

Vector3& Vector3::operator =(const Vector3 &rhs)
{
	_vec.x = rhs.X();
	_vec.y = rhs.Y();
	_vec.z = rhs.Z();

	return *this;
}

bool Vector3::operator ==(const Vector3 &rhs)
{
	return ( _vec.x == rhs.X() && _vec.y == rhs.Y() && _vec.z == rhs.Z() );
}

bool Vector3::operator !=(const Vector3 &rhs)
{
	return !( _vec.x == rhs.X() && _vec.y == rhs.Y() && _vec.z == rhs.Z() );
}

Vector3 Vector3::operator +(const Vector3 &rhs) const
{
	Vector3 ret;
	sceVfpuVector3Add( &ret._vec, &_vec, &rhs._vec );
	return ret;
}

Vector3& Vector3::operator +=(const Vector3 &rhs)
{
	sceVfpuVector3Add( &_vec, &_vec, &rhs._vec );
	return *this;
}

Vector3 Vector3::operator -(const Vector3 &rhs) const
{
	Vector3 ret;
	sceVfpuVector3Sub( &ret._vec, &_vec, &rhs._vec );
	return ret;
}

Vector3& Vector3::operator -=(const Vector3 &rhs)
{
	sceVfpuVector3Sub( &_vec, &_vec, &rhs._vec );
	return *this;
}

Vector3 Vector3::operator *(const float scalar) const
{
	Vector3 ret;
	sceVfpuVector3Scale( &ret._vec, &_vec, scalar );
	return ret;
}

Vector3& Vector3::operator *=(const float scalar)
{
	sceVfpuVector3Scale( &_vec, &_vec, scalar );
	return *this;
}

//---------------------End of Operators-----------------//

//--------------Start of Arthmetric Method--------------//
void Vector3::Add(const Vector3 &rhs)
{
	sceVfpuVector3Add( &_vec, &_vec, &rhs._vec );
}

void Vector3::Add(const Vector3 &vec1, const Vector3 &vec2, Vector3 &out)
{
	sceVfpuVector3Add( &out._vec, &vec1._vec, &vec2._vec );
}

void Vector3::Subtract(const Vector3 &rhs)
{
	sceVfpuVector3Sub( &_vec, &_vec, &rhs._vec );
}

void Vector3::Subtract(const Vector3 &vec1, const Vector3 &vec2, Vector3 &out)
{
	sceVfpuVector3Sub( &out._vec, &vec1._vec, &vec2._vec );
}

void Vector3::Multiply(const Vector3 &rhs)
{
	sceVfpuVector3Mul( &_vec, &_vec, &rhs._vec );
}

void Vector3::Multiply(const Vector3 &vec1, const Vector3 &vec2, Vector3 &out)
{
	sceVfpuVector3Mul( &out._vec, &vec1._vec, &vec2._vec );	
}

void Vector3::Multiply(float scalar)
{
	sceVfpuVector3Scale( &_vec, &_vec, scalar );
}

void Vector3::Multiply(float scalar, Vector3 &in, Vector3 &out)
{
	sceVfpuVector3Scale( &out._vec, &in._vec, scalar );
}

void Vector3::Divide(const Vector3 &rhs)
{
	sceVfpuVector3Div( &_vec, &_vec, &rhs._vec );
}

void Vector3::Divide(const Vector3 &vec1, const Vector3 &vec2, Vector3 &out)
{
	sceVfpuVector3Div( &out._vec, &vec1._vec, &vec2._vec );
}

//----------------End of Arthmetric Method--------------//

//----------------Start of Vector Operations--------------//

float Vector3::DotProduct(const Vector3 &rhs)
{
	return sceVfpuVector3InnerProduct( &_vec, &rhs._vec );
}

float Vector3::DotProduct(const Vector3 &vec1, const Vector3 &vec2)
{
	return sceVfpuVector3InnerProduct( &vec1._vec, &vec2._vec );
}

Vector3 Vector3::CrossProduct(const Vector3 &rhs, const Vector3 &rhs2)
{
	Vector3 ret;
	sceVfpuVector3OuterProduct( &ret._vec, &rhs._vec, &rhs2._vec );
	return ret;
}

void Vector3::CrossProduct(const Vector3 &vec1, const Vector3 &vec2, Vector3 &out)
{
	sceVfpuVector3OuterProduct( &out._vec, &vec1._vec, &vec2._vec );
}

Vector3 Vector3::Lerp(Vector3 &start, Vector3 &end, float amount)
{
	Vector3 ret;
	sceVfpuVector3Lerp( &ret._vec, &start._vec, &end._vec, amount );
	return ret;
}

void Vector3::Lerp(Vector3 &start, Vector3 &end, float amount, Vector3 &out)
{
	sceVfpuVector3Lerp( &out._vec, &start._vec, &end._vec, amount );
}

float Vector3::MagnitudeSquare()
{
	return ( _vec.x * _vec.x ) + ( _vec.y * _vec.y ) + ( _vec.z * _vec.z );
}

float Vector3::MagnitudeSquare(const Vector3 &rhs)
{
	return ( rhs._vec.x * rhs._vec.x ) + ( rhs._vec.y * rhs._vec.y ) + ( rhs._vec.z * rhs._vec.z );
}

void Vector3::Normalize()
{
	sceVfpuVector3Normalize( &_vec, &_vec );
}

void Vector3::Normalize(const Vector3 &in, Vector3 &out)
{
	sceVfpuVector3Normalize( &out._vec, &in._vec );
}

//----------------end of Vector Operations--------------//

#endif