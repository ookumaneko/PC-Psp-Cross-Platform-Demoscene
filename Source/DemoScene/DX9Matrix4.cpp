#if !defined(_PSP_VER)

#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"

//--------------------------Operator Overloads------------------//

//float& Matrix4::operator () (unsigned int row, unsigned int col)
//{
//	return _mat( row, col );
//}

Matrix4& Matrix4::operator= (const Matrix4& rhs)
{
	_mat = rhs._mat;
	return *this;
}

Matrix4  Matrix4::operator+ (const Matrix4& rhs) const
{
	Matrix4 ret;
	for ( int y = 0; y < 4; ++y )
	{
		for (int x = 0; x < 4; ++x )
		{
			ret._mat( y, x ) = _mat( y, x ) + rhs._mat( y, x );
		}
	}
	return ret;
}

Matrix4  Matrix4::operator- (const Matrix4& rhs) const
{
	Matrix4 ret;
	for ( int y = 0; y < 4; ++y )
	{
		for (int x = 0; x < 4; ++x )
		{
			ret._mat( y, x ) = _mat( y, x ) - rhs._mat( y, x );
		}
	}

	return ret;
}

Matrix4  Matrix4::operator* (const float scalar) const
{
	Matrix4 ret;
	for ( int y = 0; y < 4; ++y )
	{
		for (int x = 0; x < 4; ++x )
		{
			ret._mat( y, x ) = _mat( y, x ) * scalar;
		}
	}

	return ret;
}

Matrix4  Matrix4::operator* (const Matrix4& rhs) const
{
	Matrix4 ret;
	Multiply( *this, rhs, ret );
	return ret;
}

Matrix4& Matrix4::operator+= (const Matrix4& rhs)
{
	for ( int y = 0; y < 4; ++y )
	{
		for (int x = 0; x < 4; ++x )
		{
			_mat( y, x ) += rhs._mat( y, x );
		}
	}

	return *this;
}

Matrix4& Matrix4::operator-= (const Matrix4& rhs)
{
	for ( int y = 0; y < 4; ++y )
	{
		for (int x = 0; x < 4; ++x )
		{
			_mat( y, x ) -= rhs._mat( y, x );
		}
	}

	return *this;
}

Matrix4& Matrix4::operator*= (const float scalar)
{
	for ( int y = 0; y < 4; ++y )
	{
		for (int x = 0; x < 4; ++x )
		{
			_mat( y, x ) *= scalar;
		}
	}

	return *this;
}

Matrix4& Matrix4::operator*= (const Matrix4& rhs)
{
	for ( int y = 0; y < 4; ++y )
	{
		for (int x = 0; x < 4; ++x )
		{
			_mat( y, x ) *= rhs._mat( y, x );
		}
	}

	return *this;
}

//bool Matrix4::operator== (const Matrix4& rhs)
//{
	//return ( _mat == rhs._mat );
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
	D3DXMatrixIdentity( &_mat );
}

void Matrix4::Inverse(void)
{
	D3DXMatrixInverse( &_mat, NULL, &_mat );
}

//void Matrix4::BuildPerspectiveFOV(float fov, float aspectRatio, float farZ, float nearZ)
//{
//	sceVfpuViewScreenMatrix( &_mat, fov, aspectRatio, nearZ, farZ );
//}

void Matrix4::BuildLookAt(const Vector4 &eye, const Vector4 &lookAt, const Vector4 &up)
{
	D3DXVECTOR3 e = D3DXVECTOR3( eye.X(), eye.Y(), eye.Z() );
	D3DXVECTOR3 l = D3DXVECTOR3( lookAt.X(), lookAt.Y(), lookAt.Z() );
	D3DXVECTOR3 u = D3DXVECTOR3( up.X(), up.Y(), up.Z() );

	D3DXMatrixLookAtLH( &_mat, &e, &l, &u ); 
}

void Matrix4::Multiply(const Matrix4& rhs)
{
	D3DXMatrixMultiply( &_mat, &_mat, &rhs._mat );
}

void Matrix4::RotateX(float angle)
{
	Matrix4 m = Matrix4();
	D3DXMatrixRotationX( &m._mat, angle );
	_mat *= m._mat;
}

void Matrix4::RotateY(float angle)
{
	Matrix4 m = Matrix4();
	D3DXMatrixRotationY( &m._mat, angle );
	_mat *= m._mat;
}

void Matrix4::RotateZ(float angle)
{
	Matrix4 m = Matrix4();
	D3DXMatrixRotationZ( &m._mat, angle );
	_mat *= m._mat;
}

void Matrix4::RotateXYZ(const Vector4& rot)
{
	Matrix4 m = Matrix4();
	D3DXMatrixRotationYawPitchRoll( &m._mat, rot.X(), rot.Y(), rot.Z() );
	_mat *= m._mat;
}

void Matrix4::Scale(float sx, float sy, float sz)
{
	Matrix4 m = Matrix4();
	D3DXMatrixScaling( &m._mat, sx, sy, sz ); 
	_mat = m._mat * _mat;
}

void Matrix4::Scale(const Vector4& scale)
{
	Matrix4 m = Matrix4();
	D3DXMatrixScaling( &m._mat, scale.X(), scale.Y(), scale.Z() ); 
	_mat = m._mat * _mat;
}

void Matrix4::Translate(float tx, float ty, float tz)
{
	Matrix4 m = Matrix4();
	D3DXMatrixTranslation( &m._mat, tx, ty, tz );
	_mat *= m._mat;
}

void Matrix4::Translate(const Vector4& trans)
{
	Matrix4 m = Matrix4();
	D3DXMatrixTranslation( &m._mat, trans.X(), trans.Y(), trans.Z() );
	_mat *= m._mat;
}

void Matrix4::SetTranslate(const Vector4& trans)
{
	//_mat(0,2) = trans.X();
	//_mat(1,2) = trans.Y();
	//_mat(2,2) = trans.Z();
	//_mat(3,2) = trans.W();
}

void Matrix4::Transpose(void)
{
	D3DXMatrixTranspose( &_mat, &_mat );
}


//----------------End of Matrix Calculation Methods--------------//


//----------------Start of static Matrix Methods--------------//

void Matrix4::Inverse(const Matrix4& in, Matrix4& out)
{
	D3DXMatrixInverse( &out._mat, NULL, &in._mat );
}

void Matrix4::Identity(Matrix4& out)
{
	D3DXMatrixIdentity( &out._mat );
}

void Matrix4::Multiply( const Matrix4& m1, const Matrix4& m2, Matrix4& out)
{
	D3DXMatrixMultiply( &out._mat, &m1._mat, &m2._mat );
}

//void Matrix4::BuildPerspectiveFOV( float fov, float aspectRatio, float farZ, float nearZ, Matrix4& out)
//{
//	D3Matrix4PerspectiveFovLH( &out._mat, fov, aspectRatio, nearZ, farZ );
//}

void Matrix4::BuildLookAt(const Vector4& eye, const Vector4& lookAt, const Vector4& up, Matrix4& out)
{
	D3DXVECTOR3 e = D3DXVECTOR3( eye.X(), eye.Y(), eye.Z() );
	D3DXVECTOR3 l = D3DXVECTOR3( lookAt.X(), lookAt.Y(), lookAt.Z() );
	D3DXVECTOR3 u = D3DXVECTOR3( up.X(), up.Y(), up.Z() );
	D3DXMatrixLookAtLH( &out._mat, &e, &l, &u );
}

void Matrix4::BuildRotationX( float angle, Matrix4& out)
{
	D3DXMatrixRotationX( &out._mat, angle );
}

void Matrix4::BuildRotationY( float angle, Matrix4& out)
{
	D3DXMatrixRotationY( &out._mat, angle );
}

void Matrix4::BuildRotationZ( float angle, Matrix4& out)
{
	D3DXMatrixRotationZ( &out._mat, angle );
}

void Matrix4::BuildRotationXYZ( float yaw, float pitch, float roll, Matrix4& out)
{
	D3DXMatrixRotationYawPitchRoll( &out._mat, yaw, pitch, roll );
}

void Matrix4::BuildRotationXYZ(Vector4& rot, Matrix4& out)
{
	D3DXMatrixRotationYawPitchRoll( &out._mat, rot.X(), rot.Y(), rot.Z() );
}

void Matrix4::BuildScale( float sx, float sy, float sz, Matrix4& out)
{
	D3DXMatrixScaling( &out._mat, sx, sy, sz ); 
}

void Matrix4::BuildScale(const Vector4& scale, Matrix4& out)
{
	D3DXMatrixScaling( &out._mat, scale.X(), scale.Y(), scale.Z() ); 
}

void Matrix4::BuildTranslate(float tx, float ty, float tz, Matrix4& out)
{
	D3DXMatrixTranslation( &out._mat, tx, ty, tz );
}

void Matrix4::BuildTranslate(const Vector4 &trans, Matrix4 &out)
{
	D3DXMatrixTranslation( &out._mat, trans.X(), trans.Y(), trans.Z() );
}

void Matrix4::Transpose(Matrix4& matrix)
{
	D3DXMatrixTranspose( &matrix._mat, &matrix._mat );
}

//----------------End of static Matrix Methods--------------//


#endif