#include "AISystemScene.h"

#include "AISystemComponent.h"

#include "../Management/Management.h"

#include "../Scripting/ScriptComponent.h"

#include <luabind/luabind.hpp>
using namespace luabind;

namespace AI
{
	AISystemScene::~AISystemScene( )
	{
		delete _scriptScene;
	}

	AISystemScene::AISystemScene( )
	{
		_scriptScene = static_cast< ScriptSystemScene* >( Management::GetInstance( )->GetSystemManager( )->GetSystem( System::Types::SCRIPT )->CreateScene( ) );
	}

	void AISystemScene::Initialize( )
	{
		module( _scriptScene->GetState( ) )
		[
			class_< AISystemComponent >( "AISystemComponent" )
				.def( "walkForward", &AISystemComponent::WalkForward )
				.def( "walkBackward", &AISystemComponent::WalkBackward )
				.def( "facePlayer", &AISystemComponent::FacePlayer )
				.def( "setBehavior", &AISystemComponent::SetBehavior )
				.def( "getName", &AISystemComponent::GetName )
				.def( "getPlayerDistance", &AISystemComponent::GetPlayerDistance )
				.def( "fireWeapon", &AISystemComponent::FireWeapon )
		];
	}

	ISystemComponent* AISystemScene::CreateComponent( const std::string& name, const std::string& type )
	{
		ScriptComponent* scriptComponent = static_cast< ScriptComponent* >( _scriptScene->CreateComponent( name, type ) );
		AISystemComponent* aiComponent = new AISystemComponent( name, scriptComponent );

		_components.push_back( aiComponent );

		return aiComponent;
	}

	void AISystemScene::DestroyComponent( ISystemComponent* component )
	{
		for( SystemComponentList::iterator i = _components.begin( ); i != _components.end( ); ++i )
		{
			if ( ( *i )->GetName( ) == component->GetName( ) )
			{
				_components.erase( i );
				delete component;
				component = 0;
				return;
			}
		}
	}

	void AISystemScene::Update( float deltaMilliseconds )
	{
		for( SystemComponentList::iterator i = _components.begin( ); i != _components.end( ); ++i )
		{
			AISystemComponent* component = static_cast< AISystemComponent* > ( ( *i ) );
			component->Update( deltaMilliseconds );
		}
	}
}