#ifndef _VECTOR_2_H
#define _VECTOR_2_H
#include "BaseVector2.h"

class Vector2 : public BaseVector2
{
	// constructor and destructor
	public:
		Vector2(void);
		Vector2(float x, float y);
		~Vector2(void);

	// Operator Overloads
	public:
		Vector2& operator=	(const Vector2& rhs);
		Vector2	 operator+	(const Vector2& rhs) const;
		Vector2  operator-	(const Vector2& rhs) const;
		Vector2  operator*	(const float scalar) const;
		Vector2& operator+=	(const Vector2& rhs);
		Vector2& operator-=	(const Vector2& rhs);
		Vector2& operator*=	(const float scalar);
		bool	 operator==	(const Vector2& rhs);	
		bool	 operator!=	(const Vector2& rhs);

	//Accessors
	public:
		float X			(void)		const;
		float Y			(void)		const;
		float& X		(void);	
		float& Y		(void);
		float GetX		(void)		const;
		float GetY		(void)		const;
		float GetZ		(void)		const;
		void  SetX		(float x);
		void  SetY		(float y);
		void  SetValues	(float x, float y);

	//Arthemetic method
	public:
		void	Add				(const Vector2& rhs);
		void	Subtract		(const Vector2& rhs);
		void	Multiply		(const Vector2& rhs);
		void	Multiply		(float scalar);
		void	Divide			(const Vector2& rhs);
		float	DotProduct		(const Vector2& rhs);
		void	Normalize		(void);
		float	MagnitudeSquare	(void);
		void	Zero			(void);

	//static arthemetic methods
	public:
		static void		Add				(const Vector2& vec1, const Vector2& vec2, Vector2& out);
		static void		Subtract		(const Vector2& vec1, const Vector2& vec2, Vector2& out);
		static void		Multiply		(const Vector2& vec1, const Vector2& vec2, Vector2& out);
		static void		Multiply		(float scalar, Vector2& in, Vector2& out);
		static void		Divide			(const Vector2& vec1, const Vector2& vec2, Vector2& out);
		static float	DotProduct		(const Vector2& vec1, const Vector2& vec2);
		static void		Normalize		(const Vector2& in, Vector2& out);
		static float	MagnitudeSquare	(const Vector2& rhs);
		static void		Zero			(Vector2& out);

		static Vector2	Lerp			(Vector2& start, Vector2& end, float amount);
		static void		Lerp			(Vector2& start, Vector2& end, float amount, Vector2& out);
};

#endif