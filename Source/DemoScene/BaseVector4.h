#ifndef _BASE_VECTOR_4
#define _BASE_VECTOR_4

#ifdef _PSP_VER
	#include <libgum.h>
#else
	#include <D3dx9math.h>
#endif 


class BaseVector4
{
	protected:
		BaseVector4(void) {}
	public:
		virtual ~BaseVector4(void) {}

	public:
		
	#ifdef _PSP_VER

		ScePspFVector4&			GetVector(void)			{ return _vec; }
		const ScePspFVector4&	GetVector(void) const	{ return _vec; }

	protected:
		ScePspFVector4 _vec;

	#else
		
		D3DXVECTOR4&		GetVector(void)			{ return _vec; }
		const D3DXVECTOR4&	GetVector(void) const	{ return _vec; }
	
	protected:
		D3DXVECTOR4 _vec;

	#endif 
};

#endif