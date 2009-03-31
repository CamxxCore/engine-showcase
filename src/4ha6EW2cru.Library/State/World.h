#ifndef __WORLD_H
#define __WORLD_H

#include <vector>

#include "IWorld.hpp"

class World : public IWorld
{

public:

	virtual ~World( );
	World( ) { };

	IEntity* CreateEntity( const std::string& name );

	inline void AddSystemScene( ISystemScene* systemScene ) { _systemScenes[ systemScene->GetType( ) ] = systemScene; }
	inline const SystemSceneMap& GetSystemScenes( ) { return _systemScenes; };

	void Update( float deltaMilliseconds );
	void Clear( );

private:

	std::string _name;
	EntityList _entities;
	SystemSceneMap _systemScenes;

	World( const World & copy ) { };
	World & operator = ( const World & copy ) { return *this; };

};

#endif