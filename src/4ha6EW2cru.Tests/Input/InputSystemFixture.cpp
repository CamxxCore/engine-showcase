#include "InputSystemFixture.h"

#include "Input/InputSystem.h"
#include "Logging/Logger.h"
#include "IO/FileManager.h"
#include "Graphics/IRenderer.hpp"

#include "Exceptions/IntializeFailedException.hpp"
#include "Exceptions/OutOfRangeException.hpp"
#include "Exceptions/AlreadyInitializedException.hpp"
#include "Exceptions/UnInitializedException.hpp"

#include "Graphics/OgreRenderer.h"

#include "../Suites.h"
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( InputSystemFixture, Suites::InputSuite( ) );

void InputSystemFixture::setUp( )
{
	Logger::Initialize( );
	FileManager::Initialize( );
	EventManager::Initialize( );

	_renderer = new OgreRenderer( );
	_renderer->Initialize( 640, 480, false );

	_inputSystem = new InputSystem( _renderer->GetHwnd( ) );
}

void InputSystemFixture::tearDown( )
{
	delete _inputSystem;
	delete _renderer;

	EventManager::GetInstance( )->Release();
	FileManager::GetInstance( )->Release();
	Logger::GetInstance( )->Release( );
}

void InputSystemFixture::Should_Initialize_Properly( )
{
	_inputSystem->Initialize( );
}

void InputSystemFixture::Should_Throw_Given_Already_Initialized( )
{
	_inputSystem->Initialize( );
	CPPUNIT_ASSERT_THROW( _inputSystem->Initialize( ), AlreadyInitializedException );
}

void InputSystemFixture::Should_Not_Initialize_With_NULL_HWND( )
{	
	delete _inputSystem;

	_inputSystem = new InputSystem( 0 );
	CPPUNIT_ASSERT_THROW( _inputSystem->Initialize( ), IntializeFailedException );
}

void InputSystemFixture::Should_Throw_Given_Invalid_Capture_Area( )
{
	_inputSystem->Initialize( );

	CPPUNIT_ASSERT_THROW( _inputSystem->SetCaptureArea( 0, 0 ), OutOfRangeException );
}

void InputSystemFixture::Should_Accept_Valid_Capture_Area( )
{
	_inputSystem->Initialize( );

	_inputSystem->SetCaptureArea( 1, 1 );
}

void InputSystemFixture::Should_Throw_Given_Unitialized_SetCaptureArea( )
{
	delete _inputSystem;

	_inputSystem = new InputSystem( 0 );
	CPPUNIT_ASSERT_THROW( _inputSystem->SetCaptureArea( 1, 1 ), UnInitializedException );
}

void InputSystemFixture::Should_Update_Given_Initialized( )
{
	_inputSystem->Initialize( );
	_inputSystem->Update( );
}

void InputSystemFixture::Should_Throw_Given_UnIntialized_Update( )
{
	delete _inputSystem;

	_inputSystem = new InputSystem( 0 );
	CPPUNIT_ASSERT_THROW( _inputSystem->Update( ), UnInitializedException );
}