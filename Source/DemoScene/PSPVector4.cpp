#if defined (_PSP_VER)

#include "Vector4.h"
#include "Vector3.h"
#include <libvfpu.h>


//--------------------Operators-----------------------//

Vector4& Vector4::operator =(const Vector4 &rhs)
{
	_vec.x = rhs.X();
	_vec.y = rhs.Y();
	_vec.z = rhs.Z();

	return *this;
}

Vector4 Vector4::operator +(const Vector4 &rhs) const
{
	Vector4 ret;
	sceVfpuVector4Add( &ret._vec, &_vec, &rhs._vec );
	return ret;
}

Vector4& Vector4::operator +=(const Vector4 &rhs)
{
	sceVfpuVector4Add( &_vec, &_vec, &rhs._vec );
	return *this;
}

Vector4 Vector4::operator -(const Vector4 &rhs) const
{
	Vector4 ret;
	sceVfpuVector4Sub( &ret._vec, &_vec, &rhs._vec );
	return ret;
}

Vector4& Vector4::operator -=(const Vector4 &rhs)
{
	sceVfpuVector4Sub( &_vec, &_vec, &rhs._vec );
	return *this;
}

Vector4 Vector4::operator *(const float scalar) const
{
	Vector4 ret;
	sceVfpuVector4Scale( &ret._vec, &_vec, scalar );
	return ret;
}

Vector4& Vector4::operator *=(const float scalar)
{
	sceVfpuVector4Scale( &_vec, &_vec, scalar );
	return *this;
}

bool Vector4::operator ==(const Vector4 &rhs)
{
	return ( _vec.x == rhs.X() && _vec.y == rhs.Y() && _vec.z == rhs.Z() );
}

bool Vector4::operator !=(const Vector4 &rhs)
{
	return !( _vec.x == rhs.X() && _vec.y == rhs.Y() && _vec.z == rhs.Z() );
}


//---------------------End of Operators-----------------//

//--------------Start of Arthmetric Method--------------//

void Vector4::Add(const Vector4 &rhs)
{
	sceVfpuVector4Add( &_vec, &_vec, &rhs._vec );
}

void Vector4::Add(const Vector4 &vec1, const Vector4 &vec2, Vector4 &out)
{
	sceVfpuVector4Add( &out._vec, &vec1._vec, &vec2._vec );
}

void Vector4::Subtract(const Vector4 &rhs)
{
	sceVfpuVector4Sub( &_vec, &_vec, &rhs._vec );
}

void Vector4::Subtract(const Vector4 &vec1, const Vector4 &vec2, Vector4 &out)
{
	sceVfpuVector4Sub( &out._vec, &vec1._vec, &vec2._vec );
}

void Vector4::Multiply(const Vector4 &rhs)
{
	sceVfpuVector4Mul( &_vec, &_vec, &rhs._vec );
}

void Vector4::Multiply(const Vector4 &vec1, const Vector4 &vec2, Vector4 &out)
{
	sceVfpuVector4Mul( &out._vec, &vec1._vec, &vec2._vec );	
}

void Vector4::Multiply(float scalar)
{
	sceVfpuVector4Scale( &_vec, &_vec, scalar );
}

void Vector4::Multiply(float scalar, Vector4 &in, Vector4 &out)
{
	sceVfpuVector4Scale( &out._vec, &in._vec, scalar );
}

void Vector4::Divide(const Vector4 &rhs)
{
	sceVfpuVector4Div( &_vec, &_vec, &rhs._vec );
}

void Vector4::Divide(const Vector4 &vec1, const Vector4 &vec2, Vector4 &out)
{
	sceVfpuVector4Div( &out._vec, &vec1._vec, &vec2._vec );
}

//----------------End of Arthmetric Method--------------//

//----------------Start of Vector Operations--------------//

float Vector4::DotProduct(const Vector4 &rhs)
{
	return sceVfpuVector4InnerProduct( &_vec, &rhs._vec );
}

float Vector4::DotProduct(const Vector4 &vec1, const Vector4 &vec2)
{
	return sceVfpuVector4InnerProduct( &vec1._vec, &vec2._vec );
}

Vector4 Vector4::CrossProduct(const Vector4 &rhs, const Vector4 &rhs2)
{
	ScePspFVector3 temp;
	Vector3 vec1( rhs.X(), rhs.Y(), rhs.Z() );
	Vector3 vec2( rhs2.X(), rhs2.Y(), rhs2.Z() );
	sceVfpuVector3OuterProduct( &temp, &vec1.GetVector(), &vec2.GetVector() );
	Vector4 ret( temp.x, temp.y, temp.z, 1 );
	return ret;
}

void Vector4::CrossProduct(const Vector4 &vec1, const Vector4 &vec2, Vector4 &out)
{
	ScePspFVector3 temp;
	Vector3 v1( vec1.X(), vec1.Y(), vec1.Z() );
	Vector3 v2( vec2.X(), vec2.Y(), vec2.Z() );

	sceVfpuVector3OuterProduct( &temp, &v1.GetVector(), &v2.GetVector());

	out.X() = temp.x;
	out.Y() = temp.y;
	out.Z() = temp.z;
	out.W() = 1;
}

Vector4 Vector4::Lerp(Vector4 &start, Vector4 &end, float amount)
{
	Vector4 ret;
	sceVfpuVector4Lerp( &ret._vec, &start._vec, &end._vec, amount );
	return ret;
}

void Vector4::Lerp(Vector4 &start, Vector4 &end, float amount, Vector4 &out)
{
	sceVfpuVector4Lerp( &out._vec, &start._vec, &end._vec, amount );
}

float Vector4::MagnitudeSquare()
{
	return ( _vec.x * _vec.x ) + ( _vec.y * _vec.y ) + ( _vec.z * _vec.z );
}

float Vector4::MagnitudeSquare(const Vector4 &rhs)
{
	return ( rhs._vec.x * rhs._vec.x ) + ( rhs._vec.y * rhs._vec.y ) + ( rhs._vec.z * rhs._vec.z );
}

void Vector4::Normalize()
{
	sceVfpuVector4Normalize( &_vec, &_vec );
}

void Vector4::Normalize(const Vector4 &in, Vector4 &out)
{
	sceVfpuVector4Normalize( &out._vec, &in._vec );
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


//----------------end of Vector Operations--------------//


#endif