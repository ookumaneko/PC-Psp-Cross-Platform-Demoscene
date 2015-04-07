#ifdef _PSP_VER

#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include <libvfpu.h>

//--------------------------Operator Overloads------------------//

//float& Matrix4::operator () (unsigned int row, unsigned int col)
//{
//	return _mat( row, col );
//}

Matrix4& Matrix4::operator= (const Matrix4& rhs)
{
	sceVfpuMatrix4Copy( &_mat, &rhs._mat );
	return *this;
}

Matrix4  Matrix4::operator+ (const Matrix4& rhs) const
{
	Matrix4 ret;

	ret._mat.x.x = _mat.x.x + rhs._mat.x.x;
	ret._mat.x.y = _mat.x.y + rhs._mat.x.y;
	ret._mat.x.z = _mat.x.z + rhs._mat.x.z;
	ret._mat.x.w = _mat.x.w + rhs._mat.x.w;

	ret._mat.y.x = _mat.y.x + rhs._mat.y.x;
	ret._mat.y.y = _mat.y.y + rhs._mat.y.y;
	ret._mat.y.z = _mat.y.z + rhs._mat.y.z;
	ret._mat.y.w = _mat.y.w + rhs._mat.y.w;

	ret._mat.z.x = _mat.z.x + rhs._mat.z.x;
	ret._mat.z.y = _mat.z.y + rhs._mat.z.y;
	ret._mat.z.z = _mat.z.z + rhs._mat.z.z;
	ret._mat.z.w = _mat.z.w + rhs._mat.z.w;

	ret._mat.w.x = _mat.w.x + rhs._mat.w.x;
	ret._mat.w.y = _mat.w.y + rhs._mat.w.y;
	ret._mat.w.z = _mat.w.z + rhs._mat.w.z;
	ret._mat.w.w = _mat.w.w + rhs._mat.w.w;
	
	return ret;
}

Matrix4  Matrix4::operator- (const Matrix4& rhs) const
{
	Matrix4 ret;

	ret._mat.x.x = _mat.x.x - rhs._mat.x.x;
	ret._mat.x.y = _mat.x.y - rhs._mat.x.y;
	ret._mat.x.z = _mat.x.z - rhs._mat.x.z;
	ret._mat.x.w = _mat.x.w - rhs._mat.x.w;

	ret._mat.y.x = _mat.y.x - rhs._mat.y.x;
	ret._mat.y.y = _mat.y.y - rhs._mat.y.y;
	ret._mat.y.z = _mat.y.z - rhs._mat.y.z;
	ret._mat.y.w = _mat.y.w - rhs._mat.y.w;

	ret._mat.z.x = _mat.z.x - rhs._mat.z.x;
	ret._mat.z.y = _mat.z.y - rhs._mat.z.y;
	ret._mat.z.z = _mat.z.z - rhs._mat.z.z;
	ret._mat.z.w = _mat.z.w - rhs._mat.z.w;

	ret._mat.w.x = _mat.w.x - rhs._mat.w.x;
	ret._mat.w.y = _mat.w.y - rhs._mat.w.y;
	ret._mat.w.z = _mat.w.z - rhs._mat.w.z;
	ret._mat.w.w = _mat.w.w - rhs._mat.w.w;
	
	return ret;
}

Matrix4  Matrix4::operator* (const float scalar) const
{
	Matrix4 ret;
	sceVfpuMatrix4Scale( &ret._mat, &_mat, scalar );
	return ret;
}

Matrix4  Matrix4::operator* (const Matrix4& rhs) const
{
	Matrix4 ret;
	sceVfpuMatrix4Mul( &ret._mat, &_mat, &rhs._mat );
	return ret;
}

Matrix4& Matrix4::operator+= (const Matrix4& rhs)
{
	_mat.x.x = _mat.x.x + rhs._mat.x.x;
	_mat.x.y = _mat.x.y + rhs._mat.x.y;
	_mat.x.z = _mat.x.z + rhs._mat.x.z;
	_mat.x.w = _mat.x.w + rhs._mat.x.w;

	_mat.y.x = _mat.y.x + rhs._mat.y.x;
	_mat.y.y = _mat.y.y + rhs._mat.y.y;
	_mat.y.z = _mat.y.z + rhs._mat.y.z;
	_mat.y.w = _mat.y.w + rhs._mat.y.w;

	_mat.z.x = _mat.z.x + rhs._mat.z.x;
	_mat.z.y = _mat.z.y + rhs._mat.z.y;
	_mat.z.z = _mat.z.z + rhs._mat.z.z;
	_mat.z.w = _mat.z.w + rhs._mat.z.w;

	_mat.w.x = _mat.w.x + rhs._mat.w.x;
	_mat.w.y = _mat.w.y + rhs._mat.w.y;
	_mat.w.z = _mat.w.z + rhs._mat.w.z;
	_mat.w.w = _mat.w.w + rhs._mat.w.w;
	
	return *this;
}

Matrix4& Matrix4::operator-= (const Matrix4& rhs)
{
	_mat.x.x = _mat.x.x - rhs._mat.x.x;
	_mat.x.y = _mat.x.y - rhs._mat.x.y;
	_mat.x.z = _mat.x.z - rhs._mat.x.z;
	_mat.x.w = _mat.x.w - rhs._mat.x.w;

	_mat.y.x = _mat.y.x - rhs._mat.y.x;
	_mat.y.y = _mat.y.y - rhs._mat.y.y;
	_mat.y.z = _mat.y.z - rhs._mat.y.z;
	_mat.y.w = _mat.y.w - rhs._mat.y.w;

	_mat.z.x = _mat.z.x - rhs._mat.z.x;
	_mat.z.y = _mat.z.y - rhs._mat.z.y;
	_mat.z.z = _mat.z.z - rhs._mat.z.z;
	_mat.z.w = _mat.z.w - rhs._mat.z.w;

	_mat.w.x = _mat.w.x - rhs._mat.w.x;
	_mat.w.y = _mat.w.y - rhs._mat.w.y;
	_mat.w.z = _mat.w.z - rhs._mat.w.z;
	_mat.w.w = _mat.w.w - rhs._mat.w.w;
	
	return *this;
}

Matrix4& Matrix4::operator*= (const float scalar)
{
	sceVfpuMatrix4Scale( &_mat, &_mat, scalar );
	return *this;
}

Matrix4& Matrix4::operator*= (const Matrix4& rhs)
{
	sceVfpuMatrix4Mul( &_mat, &_mat, &rhs._mat );
	return *this;
}

//bool Matrix4::operator== (const Matrix4& rhs)
//{
//	if ( _mat.x != rhs._mat.x ) return false;
//	if ( _mat.y != rhs._mat.y ) return false;
//	if ( _mat.z != rhs._mat.z ) return false;
//	if ( _mat.w != rhs._mat.w ) return false;
//	return true;
//}
//
//bool Matrix4::operator!= (const Matrix4& rhs)
//{
//	return ( _mat != rhs._mat );
//}

//-------------------End of Operator Overloads---------------//

//----------------Start of Matrix Calculation Methods--------------//

void Matrix4::Identity(void)
{
	sceVfpuMatrix4Zero( &_mat );
	_mat.x.x = 1;
	_mat.y.y = 1;
	_mat.z.z = 1;
	_mat.w.w = 1;
}

void Matrix4::Inverse(void)
{
	sceVfpuMatrix4Inverse( &_mat, &_mat );
}

//void Matrix4::BuildPerspectiveFOV(float fov, float aspectRatio, float farZ, float nearZ)
//{
//	sceVfpuViewScreenMatrix( &_mat, fov, aspectRatio, nearZ, farZ );
//}

void Matrix4::BuildLookAt(const Vector4 &eye, const Vector4 &lookAt, const Vector4 &up)
{
	sceVfpuLookAtMatrix( &_mat, &eye.GetVector(), &lookAt.GetVector(), &up.GetVector() ); 
}

void Matrix4::Multiply(const Matrix4& rhs)
{
	sceVfpuMatrix4Mul( &_mat, &_mat, &rhs._mat );
}

void Matrix4::RotateX(float angle)
{
	sceVfpuMatrix4RotX( &_mat, &_mat, angle );
}

void Matrix4::RotateY(float angle)
{
	sceVfpuMatrix4RotY( &_mat, &_mat, angle );
}

void Matrix4::RotateZ(float angle)
{
	sceVfpuMatrix4RotZ( &_mat, &_mat, angle );
}

void Matrix4::RotateXYZ(const Vector4& rot)
{
	sceVfpuMatrix4Rot( &_mat, &_mat, &rot.GetVector() );
}

void Matrix4::Scale(float sx, float sy, float sz)
{
	_mat.x.x = sx;
	_mat.y.y = sy;
	_mat.z.z = sz;
	_mat.w.w = 1;
}

void Matrix4::Scale(const Vector4& scale)
{
	_mat.x.x = scale.X();
	_mat.y.y = scale.Y();
	_mat.z.z = scale.Z();
	_mat.w.w = 1;
}

void Matrix4::Translate(float tx, float ty, float tz)
{
	ScePspFVector4 vec;
	vec.x = tx;
	vec.y = ty;
	vec.z = tz;
	vec.w = 1;
	sceVfpuMatrix4Transfer( &_mat, &_mat, &vec );
}

void Matrix4::Translate(const Vector4& trans)
{
	sceVfpuMatrix4Transfer( &_mat, &_mat, &trans.GetVector() );
}

void Matrix4::SetTranslate(const Vector4& trans)
{
	_mat.z.x = trans.X();
	_mat.z.y = trans.Y();
	_mat.z.z = trans.Z();
	_mat.z.w = trans.W();
}

void Matrix4::Transpose(void)
{
	sceVfpuMatrix4Transpose( &_mat, &_mat );
}


//----------------End of Matrix Calculation Methods--------------//


//----------------Start of static Matrix Methods--------------//

void Matrix4::Inverse(const Matrix4& in, Matrix4& out)
{
	sceVfpuMatrix4Inverse ( &out._mat, &in._mat );
}

void Matrix4::Identity(Matrix4& out)
{
	sceVfpuMatrix4Zero( &out._mat );
	out._mat.x.x = 1;
	out._mat.y.y = 1;
	out._mat.z.z = 1;
	out._mat.w.w = 1;
}

void Matrix4::Multiply( const Matrix4& m1, const Matrix4& m2, Matrix4& out)
{
	sceVfpuMatrix4Mul( &out._mat, &m1._mat, &m2._mat );
}

//void Matrix4::BuildPerspectiveFOV( float fov, float aspectRatio, float farZ, float nearZ, Matrix4& out)
//{
//	D3Matrix4PerspectiveFovLH( &out._mat, fov, aspectRatio, nearZ, farZ );
//}

void Matrix4::BuildLookAt(const Vector4& eye, const Vector4& lookAt, const Vector4& up, Matrix4& out)
{
	sceVfpuLookAtMatrix ( &out._mat, &eye.GetVector(), &lookAt.GetVector(), &up.GetVector() ); 
}

void Matrix4::BuildRotationX( float angle, Matrix4& out)
{
	sceVfpuMatrix4RotX( &out._mat, &out._mat, angle );
}

void Matrix4::BuildRotationY( float angle, Matrix4& out)
{
	sceVfpuMatrix4RotY( &out._mat, &out._mat, angle );
}

void Matrix4::BuildRotationZ( float angle, Matrix4& out)
{
	sceVfpuMatrix4RotZ( &out._mat, &out._mat, angle );
}

void Matrix4::BuildRotationXYZ( float yaw, float pitch, float roll, Matrix4& out)
{
	Vector4 rot( yaw, pitch, roll, 1 );
	sceVfpuMatrix4Rot( &out._mat, &out._mat, &rot.GetVector() );
}

void Matrix4::BuildRotationXYZ(Vector4& rot, Matrix4& out)
{
	sceVfpuMatrix4Rot( &out._mat, &out._mat, &rot.GetVector() );
}

void Matrix4::BuildScale( float sx, float sy, float sz, Matrix4& out)
{
	out.Scale( sx, sy,sz );
}

void Matrix4::BuildScale(const Vector4& scale, Matrix4& out)
{
	out.Scale( scale.X(), scale.Y(), scale.Z() ); 
}

void Matrix4::BuildTranslate(float tx, float ty, float tz, Matrix4& out)
{
	ScePspFVector4 vec;
	vec.x = tx;
	vec.y = ty;
	vec.z = tz;
	vec.w = 1;
	sceVfpuMatrix4Transfer( &out._mat, &out._mat, &vec );
}

void Matrix4::BuildTranslate(const Vector4 &trans, Matrix4 &out)
{
	sceVfpuMatrix4Transfer( &out._mat, &out._mat, &trans.GetVector() );
}

void Matrix4::Transpose(Matrix4& matrix)
{
	sceVfpuMatrix4Transpose( &matrix._mat, &matrix._mat );
}

//----------------End of static Matrix Methods--------------//

#endif