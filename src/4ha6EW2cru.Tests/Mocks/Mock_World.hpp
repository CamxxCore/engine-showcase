#ifndef __MOCK_WORLD_H
#define __MOCK_WORLD_H

#include "mockpp/mockpp.h"
#include "mockpp/MockObject.h"
#include "mockpp/ExpectationCounter.h"

USING_NAMESPACE_MOCKPP

#include "State/IWorld.hpp"

#include "Mock_SystemComponent.hpp"
#include "Mock_Entity.hpp"

class Mock_World : public IWorld, public MockObject
{

public:

	virtual ~Mock_World( )
	{
		for ( EntityList::iterator e = _entities.begin( ); e != _entities.end( ); ++e )
		{
			SystemComponentList components = ( *e )->GetComponents( );

			for( SystemComponentList::iterator c = components.begin( ); c != components.end( ); ++c )
			{
				_systemScenes[ ( *c )->GetType( ) ]->DestroyComponent( ( *c ) );
			}

			delete ( *e );
		}

		for ( SystemSceneList::iterator i = _systemScenes.begin( ); i != _systemScenes.end( ); ++i )
		{
			delete ( *i ).second;
		}
	}

	Mock_World( )
		: MockObject( "Mock_World", 0 )
		, createEntity_count( "Mock_World/CreateComponent", this )
		, destroyEntity_count( "Mock_World/DestroyComponent", this )
	{ };

	ExpectationCounter createEntity_count;
	ExpectationCounter destroyEntity_count;

	IEntity* CreateEntity( const std::string& name )
	{
		IEntity* entity = new Mock_Entity( );
		_entities.push_back( entity );
		return entity;
	}

	void DestroyEntity( IEntity* entity )
	{

	}

	void AddSystemScene( ISystemScene* systemScene )
	{
		_systemScenes[ systemScene->GetType( ) ] = systemScene;
	}

	const SystemSceneList& GetSystemScenes( ) { return _systemScenes; };

	void Update( float deltaMilliseconds ) { };

private:

	SystemSceneList _systemScenes;
	EntityList _entities;

private:

	Mock_World & operator = ( const Mock_World & copy ) { return *this; };
};

#endif