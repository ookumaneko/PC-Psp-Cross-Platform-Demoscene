#ifndef _VECTOR_4_H
#define _VECTOR_4_H
#include "BaseVector4.h"

class Vector4 : public BaseVector4
{
	// constructor and destructor
	public:
		Vector4(void);
		Vector4(float x, float y, float z, float w);
		~Vector4(void);

	// Operator Overloads
	public:
		Vector4& operator=	(const Vector4& rhs);
		Vector4	 operator+	(const Vector4& rhs) const;
		Vector4  operator-	(const Vector4& rhs) const;
		Vector4  operator*	(const float scalar) const;
		Vector4& operator+=	(const Vector4& rhs);
		Vector4& operator-=	(const Vector4& rhs);
		Vector4& operator*=	(const float scalar);
		bool	 operator==	(const Vector4& rhs);	
		bool	 operator!=	(const Vector4& rhs);

	//Accessors
	public:
		float X			(void)		const;
		float Y			(void)		const;
		float Z			(void)		const;
		float W			(void)		const;
		float& X		(void);	
		float& Y		(void);
		float& Z		(void);
		float& W		(void);
		float GetX		(void)		const;
		float GetY		(void)		const;
		float GetZ		(void)		const;
		float GetW		(void)		const;
		void  SetX		(float x);
		void  SetY		(float y);
		void  SetZ		(float z);
		void  SetW		(float w);
		void  SetValues	(float x, float y, float z);

	//Arthemetic method
	public:
		void	Add				(const Vector4& rhs);
		void	Subtract		(const Vector4& rhs);
		void	Multiply		(const Vector4& rhs);
		void	Multiply		(float scalar);
		void	Divide			(const Vector4& rhs);
		float	DotProduct		(const Vector4& rhs);
		Vector4 CrossProduct	(const Vector4& rhs, const Vector4& rhs2);
		void	Normalize		(void);
		float	MagnitudeSquare	(void);
		void	Zero			(void);

	//static arthemetic methods
	public:
		static void		Add				(const Vector4& vec1, const Vector4& vec2, Vector4& out);
		static void		Subtract		(const Vector4& vec1, const Vector4& vec2, Vector4& out);
		static void		Multiply		(const Vector4& vec1, const Vector4& vec2, Vector4& out);
		static void		Multiply		(float scalar, Vector4& in, Vector4& out);
		static void		Divide			(const Vector4& vec1, const Vector4& vec2, Vector4& out);
		static float	DotProduct		(const Vector4& vec1, const Vector4& vec2);
		static void		CrossProduct	(const Vector4& vec1, const Vector4& vec2, Vector4& out);
		static void		Normalize		(const Vector4& in, Vector4& out);
		static float	MagnitudeSquare	(const Vector4& rhs);
		static void		Zero			(Vector4& out);

		static Vector4	Lerp			(Vector4& start, Vector4& end, float amount);
		static void		Lerp			(Vector4& start, Vector4& end, float amount, Vector4& out);

};

#endif