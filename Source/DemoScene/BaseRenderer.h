#ifndef _BASE_RENDERER_H
#define _BASE_RENDERER_H

#if defined (_PSP_VER)
	#include <libgum.h>	
#else
	#include "DxUtil.h"	
	#include "Matrix4.h"
	#include <stack>
	#include <vector>
	//#include <d3d9.h>
	//#include <d3dx9.h>
#endif

class BaseRenderer
{
	// constructor and destrutor
	protected:
		BaseRenderer(void) {}
	public:
		~BaseRenderer(void) {}

	//platform specific members
	protected:
	
	#if defined (_PSP_VER)
		static char		_disp_list[0x10000];
		static ScePspFMatrix4	_matrix_stack[8+8+32+0];

		static const ScePspFVector3	sphere[];	//verts to draw spherer
	#else

		static IDirect3DDevice9*	_gd3dDevice;
		static IDirect3D9*			_d3dObject;
		static DWORD				_requestedVP;
		D3DDEVTYPE					_devType;
		D3DPRESENT_PARAMETERS		_d3dPP;
		HWND						_hWnd;
		bool						_isDrawing;

		Matrix4						_viewMatrix;
		Matrix4						_projectionMatrix;
		Matrix4						_worldTransform;
		Matrix4						_prevTransform;
		std::stack<Matrix4>			_transformStack;

		ID3DXMesh*					_sphere;
	#endif
};

#endif