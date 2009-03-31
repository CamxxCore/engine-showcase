#ifndef __WORLDLOADER_H
#define __WORLDLOADER_H

#include "yaml.h"

#include "IWorldLoader.hpp"
#include "../io/IFileManager.hpp"

class WorldLoader : public IWorldLoader
{

public:

	virtual ~WorldLoader( ) { };

	WorldLoader( IWorld* world )
		: _world( world )
	{

	}

	void Load( const std::string& levelPath );

private:

	void LoadEntity( const YAML::Node& node );
	void LoadEntityComponents( const YAML::Node& node, IEntity* entity );

	IWorld* _world;

	WorldLoader( ) { };
	WorldLoader( const WorldLoader & copy ) { };
	WorldLoader & operator = ( const WorldLoader & copy ) { return *this; };

};

#endif