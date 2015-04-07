#ifndef _BASE_GAME_H
#define _BASE_GAME_H

#if defined (_PSP_VER)

#else

#include <windows.h>

#endif

class BaseGame
{
	// constructor and destrutor
	protected:
		BaseGame(void);
	public:
		~BaseGame(void) {}

	//platform specific members
	
	#if defined (_PSP_VER)

	#else // PC version

	protected:
		void InitWindow			(void);

	public:
		LRESULT msgProc			(UINT msg, WPARAM wParam, LPARAM lParam);

		HINSTANCE             _hInstance;
		HWND                  _hWnd;
	#endif
};

#endif