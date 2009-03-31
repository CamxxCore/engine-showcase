#ifndef __OGRERENDERSYSTEM_H
#define __OGRERENDERSYSTEM_H

#include "../System/ISystem.hpp"
#include "../System/ISystemScene.hpp"
#include "../System/Configuration.h"

#include "../IO/IFileManager.hpp"

#include "IInterface.hpp"
#include <Ogre.h>
using namespace Ogre;

class OgreRenderSystem : public ISystem, public Ogre::WindowEventListener
{

public:

	virtual ~OgreRenderSystem( );

	OgreRenderSystem( Configuration* configuration );

	virtual void Initialize( );
	virtual void Update( float deltaMilliseconds );
	virtual void Release( ) { };

	inline ISystemScene* CreateScene( );
	inline SystemType GetSystemType( ) { return RenderSystemType; };
	inline PropertyMap GetProperties( ) { return _properties; };

	inline Ogre::Root* GetRoot( ) { return _root; };

	virtual void windowClosed( RenderWindow* rw );

private:

	void OnGraphicsSettingsUpdated( const IEvent* event );

	void Constructor( Configuration* configuration, IFileManager* fileManager );
	void LoadResources( );
	std::vector< std::string > GetVideoModes( ) const;

	PropertyMap _properties;
	Configuration* _configuration;
	IInterface* _interface;
	bool _badStubCreated;
	bool _isIntialized;

	Ogre::Root* _root;
	Ogre::RenderWindow* _window;
	Ogre::ArchiveFactory* _badFactory;

	OgreRenderSystem( ) { };
	OgreRenderSystem( const OgreRenderSystem & copy ) { };
	OgreRenderSystem & operator = ( const OgreRenderSystem & copy ) { return *this; };

};

#endif