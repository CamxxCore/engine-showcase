#include "ControlFixture.h"

#include "Logging/Logger.h"
#include "Logging/ConsoleAppender.h"

#include "IO/FileManager.h"
#include "Events/EventManager.h"

#include "Graphics/GUI/Control.h"

//#include "Exceptions/FileNotFoundException.hpp"
#include "Exceptions/NullReferenceException.hpp"

#include "Graphics/OgreRenderer.h"

#include "../../Suites.h"
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( ControlFixture, Suites::GraphicsSuite( ) );

void ControlFixture::setUp( )
{
	Logger::Initialize( );

	Logger::GetInstance( )->AddAppender( new ConsoleAppender( ) );

	EventManager::Initialize( );
	FileManager::Initialize( );

	FileManager::GetInstance( )->AddFileStore( "../game/test" );

	_renderer = new OgreRenderer( );
	_renderer->Initialize( 640, 480, false );
}

void ControlFixture::tearDown( )
{
	delete _renderer;

	FileManager::GetInstance( )->Release( );
	EventManager::GetInstance( )->Release( );
	Logger::GetInstance( )->Release( );
}

/*void ControlFixture::Should_Throw_On_Initialize_Given_NULL_Not_Gui( )
{
	Control control( "existingscript", 0 );
	CPPUNIT_ASSERT_THROW( control.Initialize( ), NullReferenceException );
}

void ControlFixture::Should_Throw_On_Initialize_Given_Layout_Not_Found( )
{
	//Control control( "existingscript", 0 );
	//CPPUNIT_ASSERT_THROW( control.Initialize( ), FileNotFoundException );
}*/

void ControlFixture::Should_Throw_On_Initialize_Given_Script_Not_Found( )
{
	Control control( "blah" );
	CPPUNIT_ASSERT_THROW( control.Initialize( ), FileNotFoundException );
}

void ControlFixture::Should_Initialize_Correctly( )
{
	Control control( "test" );
	control.Initialize( );
}