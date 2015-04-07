#if !defined(_PSP_VER)
#include "Game.h"
#include "Renderer.h"
#include <string>

//-------------Start of Windows Methods---------//

BaseGame::BaseGame()
{
	_hWnd = 0;
	_hInstance = 0;
}

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Game* demo = Game::GetInstance();

	// Don't start processing messages until the application has been created.
	if( demo->_hWnd )
		return demo->msgProc( msg, wParam, lParam );
	else
		return DefWindowProc( hwnd, msg, wParam, lParam );
}


void BaseGame::InitWindow()
{
	WNDCLASS wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = MainWndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = _hInstance;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = "D3DWndClassName";

	if( !RegisterClass(&wc) )
	{
		MessageBox(0, "RegisterClass FAILED", 0, 0);
		PostQuitMessage(0);
	}

	// Default to a window with a client area rectangle of 800x600.
	//RECT R = { 0, 0, _screenWidth, _screenHeight };
	RECT R = { 0, 0, 480, 272 };
	//RECT R = { 0, 0, 800, 600 };

	AdjustWindowRect( &R, WS_OVERLAPPEDWINDOW, false );

	std::string _title = "Demo";
	_hWnd = CreateWindow( "D3DWndClassName", _title.c_str(), 
		WS_OVERLAPPEDWINDOW, 100, 100, R.right, R.bottom, 
		0, 0, _hInstance, 0); 

	if( !_hWnd )
	{
		MessageBox(0, "CreateWindow FAILED", 0, 0);
		PostQuitMessage(0);
	}

	ShowWindow( _hWnd, SW_SHOW );
	UpdateWindow( _hWnd );
}

LRESULT BaseGame::msgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Is the application in a minimized or maximized state?
	static bool minOrMaxed = false;

	RECT clientRect = {0, 0, 0, 0};
	switch( msg )
	{
	case WM_ACTIVATE:
		//if( LOWORD(wParam) == WA_INACTIVE )
		//	//_isPaused = true;
		//else
		//	//_isPaused = false;
		//return 0;

	case WM_SIZE:
		//if( _graphics )
		//{
		//	_renderer->SetBackBufferSize( LOWORD(lParam), HIWORD(lParam) );

		//	if( wParam == SIZE_MINIMIZED )
		//	{
		//		_isPaused = true;
		//		minOrMaxed = true;
		//	}
		//	else if( wParam == SIZE_MAXIMIZED )
		//	{
		//		_isPaused = false;
		//		minOrMaxed = true;
		//		OnLostDevice();
		//		//_renderer->ResetDevice();
		//		OnResetDevice();
		//	}
		//	// Restored is any resize that is not a minimize or maximize.
		//	else if( wParam == SIZE_RESTORED )
		//	{
		//		_isPaused = false;

		//		// Are we restoring from a mimimized or maximized state, 
		//		// and are in windowed mode?  Do not execute this code if 
		//		// we are restoring to full screen mode.
		//		if( minOrMaxed && _renderer->GetPP().Windowed )
		//		{
		//			OnLostDevice();
		//			//_renderer->ResetDevice();
		//			OnResetDevice();
		//		}
		//		else
		//		{
		//			// No, which implies the user is resizing by dragging
		//			// the resize bars.
		//		}
		//		minOrMaxed = false;
		//	}
		//}
		return 0;


	// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
	// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:
		GetClientRect(_hWnd, &clientRect);
		//_renderer->SetBackBufferSize( clientRect.right, clientRect.bottom );
		//OnLostDevice();
		////_renderer->ResetDevice();
		//OnResetDevice();

		return 0;

	// WM_CLOSE is sent when the user presses the 'X' button in the
	// caption bar menu.
	case WM_CLOSE:
		DestroyWindow( _hWnd );
		PostQuitMessage(0);
		return 0;

	// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(_hWnd, msg, wParam, lParam);
}


//---------------End of Windows Methods---------//



//-------------Start of Frawework Methods---------//

int Game::Run()
{
	Initialize();

	MSG  msg;
	msg.message = WM_NULL;

	DWORD frames = 0;
	DWORD prevTime = timeGetTime();
	float fps = 60.0f;	// frame rate of the app

	while( true )
	{
		// If there are Window messages then process them.
		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
		{
			if ( msg.message == WM_QUIT )
				break;

			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		// Otherwise, do animation/game stuff.
		else
		{	
			DWORD curTime, elapsed, idealTime;

			// get the current time 
			curTime = timeGetTime();
			elapsed = curTime - prevTime;

			// calculate the ideal time to limit frame rate
			// idealTime = numFrames * 1000 / desiredFPS
			idealTime = (DWORD)( frames * ( 1000.0f / fps ) );

			// if the app is moving too fast, pause it
			if ( idealTime > elapsed )
			{
				Sleep( idealTime - elapsed );
			}

			// if 1 second has pased 
			if ( elapsed >= 1000 )
			{
				// reset time and frame count
				prevTime = curTime;
				frames = 0;
			}
			frames++;

			Update( 0.0f );
			Draw( 0.0f );
		}
	}

	Shutdown();

	return (int)msg.wParam;
}

void Game::Initialize()
{
	//set up window
	InitWindow();

	_renderer = Renderer::GetInstance();
	//_renderer->Initialize();
}

void Game::Shutdown()
{
	_renderer->Shutdown();
	delete _renderer;
	_renderer = 0;
}

void Game::Update(float delta)
{

}

void Game::Draw(float delta)
{

}

//---------------End of Frawework Methods---------//

#endif