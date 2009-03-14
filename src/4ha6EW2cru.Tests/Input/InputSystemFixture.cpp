#include "InputSystemFixture.h"

#include "Input/InputSystem.h"
#include "Logging/Logger.h"
#include "IO/FileManager.h"
#include "Graphics/IRenderer.hpp"
#include "Events/EventManager.h"

#include "Exceptions/IntializeFailedException.hpp"
#include "Exceptions/OutOfRangeException.hpp"
#include "Exceptions/AlreadyInitializedException.hpp"
#include "Exceptions/UnInitializedException.hpp"

#include "../Suites.h"
//CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( InputSystemFixture, Suites::InputSuite( ) );

void InputSystemFixture::setUp( )
{
	Logger::Initialize( );
	FileManager::Initialize( );
	EventManager::Initialize( );
}

void InputSystemFixture::tearDown( )
{
	EventManager::GetInstance( )->Release();
	FileManager::GetInstance( )->Release();
	Logger::GetInstance( )->Release( );
}

void InputSystemFixture::Should_Initialize_Properly( )
{
	InputSystem* inputSystem = new InputSystem( 0 );
	inputSystem->Initialize( );

	delete inputSystem;
}

void InputSystemFixture::Should_Throw_Given_Already_Initialized( )
{
	InputSystem* inputSystem = new InputSystem( 0 );
	inputSystem->Initialize( );
	CPPUNIT_ASSERT_THROW( inputSystem->Initialize( ), AlreadyInitializedException );

	delete inputSystem;
}

void InputSystemFixture::Should_Not_Initialize_With_NULL_HWND( )
{	
	InputSystem* inputSystem = new InputSystem( 0 );
	CPPUNIT_ASSERT_THROW( inputSystem->Initialize( ), IntializeFailedException );

	delete inputSystem;
}