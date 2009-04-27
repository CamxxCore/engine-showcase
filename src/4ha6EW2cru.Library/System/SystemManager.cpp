#include "SystemManager.h"

using namespace State;

SystemManager::~SystemManager()
{
	for( SystemList::reverse_iterator i = _systems.rbegin( ); i != _systems.rend( ); ++i )
	{
		delete ( *i );
	}

	_systems.clear( );
}

void SystemManager::RegisterSystem( ISystem* system )
{
	_systems.push_back( system );
}

ISystem* SystemManager::GetSystem( const System::Types::Type& systemType ) const
{
	for( SystemList::const_iterator i = _systems.begin( ); i != _systems.end( ); ++i )
	{
		if ( ( *i )->GetType( ) == systemType )
		{
			return ( *i );
		}
	}

	return 0;
}

void SystemManager::InitializeAllSystems()
{
	for( SystemList::iterator i = _systems.begin( ); i != _systems.end( ); ++i )
	{
		( *i )->Initialize( );
	}
}

void SystemManager::Update( const float& deltaMilliseconds )
{
	for( SystemList::iterator i = _systems.begin( ); i != _systems.end( ); ++i )
	{
		( *i )->Update( deltaMilliseconds );
	}
}

void SystemManager::Release()
{
	for( SystemList::reverse_iterator i = _systems.rbegin( ); i != _systems.rend( ); ++i )
	{
		( *i )->Release( );
	}
}

IWorld* SystemManager::CreateWorld()
{
	IWorld* world = new World( );

	for( SystemList::iterator i = _systems.begin( ); i != _systems.end( ); ++i )
	{
		world->AddSystemScene( ( *i )->CreateScene( ) );
	}

	return world;
}