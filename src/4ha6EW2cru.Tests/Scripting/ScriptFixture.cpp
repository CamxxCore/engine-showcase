#include "ScriptFixture.h"

#include "Events/Event.h"
#include "Events/IEventListener.hpp"
#include "Events/EventManager.h"
#include "Scripting/ScriptManager.h"
#include "Logging/Logger.h"
#include "Logging/ConsoleAppender.h"
#include "IO/FileManager.h"

#include "Exceptions/UnInitializedException.hpp"
#include "Exceptions/AlreadyInitializedException.hpp"
#include "Exceptions/OutOfRangeException.hpp"

#include "../Mocks/MockEventData.hpp"
#include "../Mocks/MockScriptBinder.hpp"

#include "../Suites.h"
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( ScriptFixture, Suites::ScriptingSuite( ) );

void ScriptFixture::setUp( )
{
	Logger::Initialize( );
	Logger::GetInstance( )->AddAppender( new ConsoleAppender( ) );
	FileManager::Initialize( );
	EventManager::Initialize( );
	ScriptManager::Initialize( 0 );

	MockScriptBinder::handle_count = 0;

	FileManager::GetInstance( )->MountFileStore( "../game/test", "/" );
	_script = ScriptManager::GetInstance( )->CreateScript( "testscript.lua" );
}

void ScriptFixture::tearDown( )
{
	delete _script;

	ScriptManager::GetInstance( )->Release( );
	FileManager::GetInstance( )->Release( );
	EventManager::GetInstance( )->Release( );
	Logger::GetInstance( )->Release( );

	MockScriptBinder::handle_count = 0;
}

void ScriptFixture::Should_Initialize_Given_Valid_Script( )
{
	_script->Initialize( );
}

void ScriptFixture::Should_Throw_On_Initialize_Given_Invalid_Script( )
{
	FileManager::GetInstance( )->MountFileStore( "../game/test", "/" );
	Script* script = ScriptManager::GetInstance( )->CreateScript( "garbage.lua" );

	CPPUNIT_ASSERT_THROW( script->Initialize( ), ScriptException );

	delete script;
}

void ScriptFixture::Should_Throw_On_Initialize_Given_Already_Initialized( )
{
	_script->Initialize( );
	CPPUNIT_ASSERT_THROW( _script->Initialize( ), AlreadyInitializedException );
}
/*
void ScriptFixture::Should_Throw_On_CreateFromFileBuffer_Given_NULL_FileBuffer( )
{
	CPPUNIT_ASSERT_THROW( Script::CreateFromFileBuffer( 0 ), NullReferenceException );
}

void ScriptFixture::Should_Throw_On_CreateFromFileBuffer_Given_Invalid_FileBuffer( )
{
	FileBuffer* fileBuffer = new FileBuffer( );
	CPPUNIT_ASSERT_THROW( Script::CreateFromFileBuffer( fileBuffer ), UnInitializedException );
}

void ScriptFixture::Should_CreateFromFileBuffer_Given_Valid_FileBuffer( )
{
	FileManager::GetInstance( )->AddFileStore( "../game/test" );
	Script* script = ScriptManager::GetInstance( )->CreateScript( "testscript.lua" );

	delete script;
}*/

void ScriptFixture::Should_Throw_On_CallFunction_Given_Not_Initialized( )
{
	CPPUNIT_ASSERT_THROW( _script->CallFunction( "testFunction" ), UnInitializedException );
}

void ScriptFixture::Should_Throw_On_CallFunction_Given_Empty_FunctionName( )
{
	_script->Initialize( );

	CPPUNIT_ASSERT_THROW( _script->CallFunction( "" ), OutOfRangeException );
}

void ScriptFixture::Should_Throw_On_CallFunction_Given_Non_Existing_FunctionName( )
{
	_script->Initialize( );

	CPPUNIT_ASSERT_THROW( _script->CallFunction( "randomFunction" ), ScriptException );
}

void ScriptFixture::Should_Throw_On_CallFunction_Given_Lua_Error( )
{
	_script->Initialize( );

	CPPUNIT_ASSERT_THROW( _script->CallFunction( "killerFunction" ), ScriptException );
}

void ScriptFixture::Should_CallFunction_Given_Valid_FunctionName( )
{
	_script->Initialize( );

	_script->CallFunction( "testFunction" );
}

void ScriptFixture::Should_GetState( )
{
	_script->Initialize( );

	CPPUNIT_ASSERT( _script->GetState( ) != 0 );
}