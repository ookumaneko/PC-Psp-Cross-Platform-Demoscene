#ifndef _BASE_VECTOR_2
#define _BASE_VECTOR_2

#ifdef _PSP_VER
	#include <libgum.h>
#else
	#include <D3dx9math.h>
#endif 


class BaseVector2
{
	protected:
		BaseVector2(void) {}
	public:
		virtual ~BaseVector2(void) {}

	public:
		
	#ifdef _PSP_VER

		ScePspFVector2&			GetVector(void)			{ return _vec; }
		const ScePspFVector2&	GetVector(void) const	{ return _vec; }

	protected:
		ScePspFVector2 _vec;

	#else
		
		D3DXVECTOR2&		GetVector(void)			{ return _vec; }
		const D3DXVECTOR2&	GetVector(void) const	{ return _vec; }
	
	protected:
		D3DXVECTOR2 _vec;

	#endif 
};

#endif