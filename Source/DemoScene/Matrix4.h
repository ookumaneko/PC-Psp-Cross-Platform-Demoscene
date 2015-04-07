#ifndef _MATRIX_4
#define _MATRIX_4
#include "BaseMatrix4.h"

class Vector4;

class Matrix4 : public BaseMatrix4
{
	// constructor and destructor
	public:
		Matrix4(void);
		~Matrix4(void);

	// Operators 
	public:
		Matrix4& operator=	(const Matrix4& rhs);
		Matrix4  operator+	(const Matrix4& rhs) const;
		Matrix4  operator-	(const Matrix4& rhs) const;
		Matrix4  operator*	(const float scalar) const;
		Matrix4  operator*	(const Matrix4& rhs) const;
		Matrix4& operator+=	(const Matrix4& rhs);
		Matrix4& operator-=	(const Matrix4& rhs);
		Matrix4& operator*=	(const float scalar);
		Matrix4& operator*=	(const Matrix4& rhs);
		//bool	 operator==	(const Matrix4& rhs);	
		//bool	 operator!=	(const Matrix4& rhs);

		//float&	operator ()	(unsigned int row, unsigned int col);

	// matrix calculation methods
	public:
		void Identity			(void);
		void Inverse			(void);

		//void BuildPerspectiveFOV(float fov, float aspectRatio, float farZ, float nearZ);
		void BuildLookAt		(const Vector4& eye, const Vector4& lookAt, const Vector4& up);

		void Multiply			(const Matrix4& rhs);
		
		void RotateX			(float angle);
		void RotateY			(float angle);
		void RotateZ			(float angle);
		void RotateXYZ			(const Vector4& rot);
		
		void Scale				(float sx, float sy, float sz);
		void Scale				(const Vector4& scale);

		void Translate			(float tx, float ty, float tz);
		void Translate			(const Vector4& trans);
		void SetTranslate		(const Vector4& trans);

		void Transpose			(void);

	//static Matrix4 calculation methods
	public:

		static void Inverse					(const Matrix4& in, Matrix4& out);
		static void Identity				(Matrix4& out);
		
		static void Multiply				( const Matrix4& m1, const Matrix4& m2, Matrix4& out);

		//static void BuildPerspectiveFOV	( float fov, float aspectRatio, float farZ, float nearZ, Matrix4& out);
		static void BuildLookAt				( const Vector4& eye, const Vector4& lookAt, const Vector4& up, Matrix4& out);
		static void BuildRotationX			( float angle, Matrix4& out);
		static void BuildRotationY			( float angle, Matrix4& out);
		static void BuildRotationZ			( float angle, Matrix4& out);
		static void BuildRotationXYZ		( float yaw, float pitch, float roll, Matrix4& out);
		static void BuildRotationXYZ		( Vector4& rot, Matrix4& out);

		static void BuildScale				( float sx, float sy, float sz, Matrix4& out);
		static void BuildScale				( const Vector4& scale, Matrix4& out );

		static void BuildTranslate			( float tx, float ty, float tz, Matrix4& out);
		static void BuildTranslate			( const Vector4& trans, Matrix4& out );
		static void Transpose				( Matrix4& matrix);
};

#endif