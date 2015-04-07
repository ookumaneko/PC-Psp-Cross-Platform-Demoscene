#ifndef _VECTOR_3_H
#define _VECTOR_3_H
#include "BaseVector3.h"

class Vector3 : public BaseVector3
{
	// constructor and destructor
	public:
		Vector3(void);
		Vector3(float x, float y, float z);
		~Vector3(void);

	// Operator Overloads
	public:
		Vector3& operator=	(const Vector3& rhs);
		Vector3	 operator+	(const Vector3& rhs) const;
		Vector3  operator-	(const Vector3& rhs) const;
		Vector3  operator*	(const float scalar) const;
		Vector3& operator+=	(const Vector3& rhs);
		Vector3& operator-=	(const Vector3& rhs);
		Vector3& operator*=	(const float scalar);
		bool	 operator==	(const Vector3& rhs);	
		bool	 operator!=	(const Vector3& rhs);

	//Accessors
	public:
		float X			(void)		const;
		float Y			(void)		const;
		float Z			(void)		const;
		float& X		(void);	
		float& Y		(void);
		float& Z		(void);
		float GetX		(void)		const;
		float GetY		(void)		const;
		float GetZ		(void)		const;
		void  SetX		(float x);
		void  SetY		(float y);
		void  SetZ		(float z);
		void  SetValues	(float x, float y, float z);

	//Arthemetic method
	public:
		void	Add				(const Vector3& rhs);
		void	Subtract		(const Vector3& rhs);
		void	Multiply		(const Vector3& rhs);
		void	Multiply		(float scalar);
		void	Divide			(const Vector3& rhs);
		float	DotProduct		(const Vector3& rhs);
		Vector3 CrossProduct	(const Vector3& rhs, const Vector3& rhs2);
		void	Normalize		(void);
		float	MagnitudeSquare	(void);
		void	Zero			(void);

	//static arthemetic methods
	public:
		static void		Add				(const Vector3& vec1, const Vector3& vec2, Vector3& out);
		static void		Subtract		(const Vector3& vec1, const Vector3& vec2, Vector3& out);
		static void		Multiply		(const Vector3& vec1, const Vector3& vec2, Vector3& out);
		static void		Multiply		(float scalar, Vector3& in, Vector3& out);
		static void		Divide			(const Vector3& vec1, const Vector3& vec2, Vector3& out);
		static float	DotProduct		(const Vector3& vec1, const Vector3& vec2);
		static void		CrossProduct	(const Vector3& vec1, const Vector3& vec2, Vector3& out);
		static void		Normalize		(const Vector3& in, Vector3& out);
		static float	MagnitudeSquare	(const Vector3& rhs);
		static void		Zero			(Vector3& out);

		static Vector3	Lerp			(Vector3& start, Vector3& end, float amount);
		static void		Lerp			(Vector3& start, Vector3& end, float amount, Vector3& out);

};

#endif