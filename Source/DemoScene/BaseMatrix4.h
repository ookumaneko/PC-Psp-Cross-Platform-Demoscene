#ifndef _BASE_MATRIX_4
#define _BASE_MATRIX_4

#ifdef _PSP_VER
	#include <libgum.h>
#else
	#include <D3dx9math.h>
#endif 

class BaseMatrix4
{
	// constructor and destructor
	protected:
		BaseMatrix4(void) {}
	public:
		virtual ~BaseMatrix4(void) {}

	public:

	#ifdef _PSP_VER
	
		ScePspFMatrix4&			GetMatrix(void)			{ return _mat; }
		const ScePspFMatrix4&	GetMatrix(void) const	{ return _mat; }

	protected:
		ScePspFMatrix4 _mat;

	#else	//PC Version

		D3DXMATRIX&			GetMatrix(void)			{ return _mat; }
		const D3DXMATRIX&	GetMatrix(void) const	{ return _mat; }

	protected:
		//D3DXMATRIXA16 _mat;
		D3DXMATRIX _mat;
	#endif

};

#endif