#include "OgreRendererFixture.h"

#include "Graphics/OgreRenderer.h"

#include "Exceptions/ScreenDimensionsException.hpp"

#include "Events/EventManager.h"
#include "IO/FileManager.h"
#include "Logging/Logger.h"

#include "Exceptions/UnInitializedException.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( OgreRendererFixture );

void OgreRendererFixture::setUp( )
{
	Logger::Initialize( );
	EventManager::Initialize( );
	FileManager::Initialize( );

	_renderer = new OgreRenderer( );
}

void OgreRendererFixture::tearDown( )
{
	delete _renderer;

	FileManager::GetInstance( )->Release( );
	EventManager::GetInstance( )->Release( );
	Logger::GetInstance( )->Release( );
}

void OgreRendererFixture::Should_Intialize_Correctly( )
{
	_renderer->Initialize( 800, 600, false );
}

void OgreRendererFixture::Should_Throw_ScreenDimensionsException_On_Initialize_Given_Negative_Dimensions( )
{
	CPPUNIT_ASSERT_THROW( _renderer->Initialize( -1, -1, -1 ), ScreenDimensionsException );
}

void OgreRendererFixture::Should_Throw_ScreenDimensionsException_On_Initialize_Given_Zero_Dimensions( )
{
	CPPUNIT_ASSERT_THROW( _renderer->Initialize( 0, 0, 0 ), ScreenDimensionsException );
}


void OgreRendererFixture::Should_Render_Given_Initialized( )
{
	_renderer->Initialize( 1, 1, false );
	_renderer->Render( );
}

void OgreRendererFixture::Should_Throw_On_Render_Given_Not_Intiailized( )
{
	CPPUNIT_ASSERT_THROW( _renderer->Render( ), UnInitializedException );
}

void OgreRendererFixture::Should_Update_Given_Initialized( )
{
	_renderer->Initialize( 1, 1, false );
	_renderer->Update( );
}

void OgreRendererFixture::Should_Throw_On_Update_Given_Not_Intialized( )
{
	CPPUNIT_ASSERT_THROW( _renderer->Update( ), UnInitializedException );
}

void OgreRendererFixture::Should_Return_Positive_Hwnd( )
{
	_renderer->Initialize( 1, 1, false );
	CPPUNIT_ASSERT( _renderer->GetHwnd( ) > 0 );
}

void OgreRendererFixture::Should_Throw_On_GetHWND_Given_Not_Intialized( )
{
	CPPUNIT_ASSERT_THROW( _renderer->GetHwnd( ), UnInitializedException );
}

void OgreRendererFixture::Should_Throw_On_GetGUI_Given_Not_Initialized( )
{
	CPPUNIT_ASSERT_THROW( _renderer->GetGui( ), UnInitializedException );
}

void OgreRendererFixture::Should_Return_GUI_Given_Initialized( )
{
	_renderer->Initialize( 1, 1, false );
	CPPUNIT_ASSERT( 0 != _renderer->GetGui( ) );
}