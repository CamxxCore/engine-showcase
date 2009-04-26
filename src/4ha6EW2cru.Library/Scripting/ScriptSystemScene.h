#ifndef __SCRIPTSYSTEMSCENE_H
#define __SCRIPTSYSTEMSCENE_H

#include <vector>

#include "ScriptConfiguration.h"

#include "../IO/IFileManager.hpp"
#include "../Configuration/IConfiguration.hpp"
#include "../System/ISystem.hpp"

#include "IScriptComponent.hpp"

#include "../Events/IEvent.hpp"
#include "../Events/EventType.hpp"
#include "../Events/EventData.hpp"

extern "C" 
{
#	include <lua.h>
#	include <lualib.h>
}

#include <luabind/luabind.hpp>

class ScriptSystemScene : public ISystemScene
{
	typedef std::pair< Events::EventType, luabind::object > EventHandler;
	typedef std::vector< EventHandler > EventHandlerList;
	typedef std::vector< IScriptComponent* > ScriptComponentList;

public:

	virtual ~ScriptSystemScene( );

	ScriptSystemScene( Configuration::IConfiguration* configuration );

	void Initialize( );
	inline void Update( float deltaMilliseconds );

	ISystemComponent* CreateComponent( const std::string& name, const std::string& type );
	void DestroyComponent( ISystemComponent* component );

	inline System::Types::Type GetType( ) { return System::Types::SCRIPT; };

	void RegisterEvent( Events::EventType eventType, luabind::object function );
	void UnRegisterEvent( Events::EventType eventType, luabind::object function );
	void BroadcastEvent( Events::EventType eventType );

	/*! Returns the Master LUA State for the Scene */
	lua_State* GetState( ) const { return _state; };

	/*! Executes the specified string */
	void ExecuteString( const std::string& input );

	/*! Prints the specified message to the console */
	static void Print( const std::string& message );

	/*! Quits the game */
	static void Quit( );

	/*! Loads the specified level */
	static void LoadLevel( const std::string& levelName );

	/*! Ends the current Game */
	static void EndGame( );

	/*! Gets called when an error occurs inside a running script */
	static int Script_PError( lua_State* luaState );

	/*! Gets called when an error occurs inside a script */
	static void Script_Error( lua_State* luaState );

	/*! Gets called when a casting error occurs inside a script */
	static void Script_CastError( lua_State* luaState, LUABIND_TYPE_INFO typeInfo );


private:

	void OnEvent( const Events::IEvent* event );

	ScriptConfiguration* _scriptConfiguration;

	lua_State* _state;
	ScriptComponentList _components;
	EventHandlerList* _eventHandlers;

	ScriptSystemScene( ) { };
	ScriptSystemScene( const ScriptSystemScene & copy ) { };
	ScriptSystemScene & operator = ( const ScriptSystemScene & copy ) { return *this; };

};

#endif