#ifndef _BASE_VECTOR_3
#define _BASE_VECTOR_3

#ifdef _PSP_VER
	#include <libgum.h>
#else
	#include <D3dx9math.h>
#endif 


class BaseVector3
{
	protected:
		BaseVector3(void) {}
	public:
		virtual ~BaseVector3(void) {}

	public:
		
	#ifdef _PSP_VER

		ScePspFVector3&			GetVector(void)			{ return _vec; }
		const ScePspFVector3&	GetVector(void) const	{ return _vec; }

	protected:
		ScePspFVector3 _vec;

	#else
		
		D3DXVECTOR3&		GetVector(void)			{ return _vec; }
		const D3DXVECTOR3&	GetVector(void) const	{ return _vec; }
	
	protected:
		D3DXVECTOR3 _vec;

	#endif 
};

#endif