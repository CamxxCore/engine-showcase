#include "Win32PlatformManager.h"

#include "../Events/Event.h"
#include "../Management/Management.h"

#include <windows.h>
#include <mmsystem.h>

#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

LRESULT CALLBACK WindowProcedure( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{

	case WM_DESTROY:

		PostQuitMessage( 0 );
		return 0;

	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

namespace Platform
{
	void Win32PlatformManager::CreateInteractiveWindow( const std::string& title, const int& width, const int& height, const bool& fullScreen )
	{
		WNDCLASSEX wnd;

		wnd.cbSize = sizeof( WNDCLASSEX );
		wnd.style = CS_HREDRAW | CS_VREDRAW;

		wnd.lpfnWndProc = WindowProcedure;
		wnd.cbClsExtra = 0;
		wnd.cbWndExtra = 0;
		wnd.hInstance = GetModuleHandle( NULL );
		wnd.hIcon = NULL;
		wnd.hCursor = NULL;
		wnd.hbrBackground = GetSysColorBrush( COLOR_BTNFACE );
		wnd.lpszMenuName = NULL;
		wnd.lpszClassName = "WindowClassName";
		wnd.hIconSm = LoadIcon( NULL,IDI_APPLICATION );

		RegisterClassEx(&wnd);

		int screenWidth = GetSystemMetrics( SM_CXSCREEN ) ;
		int screenHeight = GetSystemMetrics( SM_CYSCREEN ) ;

		_hWnd = ( size_t ) CreateWindowExA( WS_EX_CONTROLPARENT, "WindowClassName", title.c_str( ),
			( fullScreen ) ? WS_POPUP | WS_EX_TOPMOST : WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
			( screenWidth - width ) / 2,  ( screenHeight - height ) / 2, width, height, NULL, NULL, GetModuleHandle( NULL ), NULL );
	}

	static const WORD MAX_CONSOLE_LINES = 500;

	void Win32PlatformManager::CreateConsoleWindow( )
	{
		int hConHandle;

		long lStdHandle;

		CONSOLE_SCREEN_BUFFER_INFO coninfo;

		AllocConsole();

		// set the screen buffer to be big enough to let us scroll text

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),

			&coninfo);

		coninfo.dwSize.Y = MAX_CONSOLE_LINES;

		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),

			coninfo.dwSize);

		// redirect unbuffered STDOUT to the console

		lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);

		hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	}

	void Win32PlatformManager::Update( const float& deltaMilliseconds )
	{
		MSG msg;

		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			if ( msg.message == WM_QUIT )
			{
				Management::GetInstance( )->GetEventManager( )->QueueEvent( new Events::Event( Events::GAME_QUIT ) );
			}

			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}

	void Win32PlatformManager::CloseWindow( )
	{
		DestroyWindow( ( HWND ) _hWnd );
	}

	size_t Win32PlatformManager::GetWindowId( ) const
	{
		if ( _hWnd == 0 )
		{
			return ( size_t ) GetConsoleWindow( );
		}

		return _hWnd; 
	}

	float Win32PlatformManager::GetTime( ) const
	{
		return timeGetTime( );
	}

	void Win32PlatformManager::OutputDebugMessage( const std::string& message )
	{
		OutputDebugString( message.c_str( ) );
	}
}