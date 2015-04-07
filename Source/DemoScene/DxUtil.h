//=============================================================================
// DxUtil.h by Frank Luna (C) 2005 All Rights Reserved.
// Edited by Kenji Shimojima
//
// Contains various utility code for DirectX applications, such as, clean up
// and debugging code.
//=============================================================================

#ifndef _DXDUTIL_H
#define _DXDUTIL_H

// Enable extra D3D debugging in debug builds if using the debug DirectX runtime.  
// This makes D3D objects work well in the debugger watch window, but slows down 
// performance slightly.
#if defined(DEBUG) | defined(_DEBUG)
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9d.lib")
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "dxguid.lib")

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <string>
#include <sstream>

//===============================================================

// Clean up

#define ReleaseCOM(x) { if(x){ x->Release();x = 0; } }

//===============================================================
// Debug

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                      \
	{                                                  \
		HRESULT hr = x;                                \
		if( FAILED(hr) )                               \
		{                                              \
			DXTrace(__FILE__, __LINE__, hr, #x, TRUE); \
		}                                              \
	}
	#endif

#else
	#ifndef HR
	#define HR(x) x;
	#endif
#endif 

#endif // D3DUTIL_H