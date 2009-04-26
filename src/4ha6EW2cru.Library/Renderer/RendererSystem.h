#ifndef __OGRERENDERSYSTEM_H
#define __OGRERENDERSYSTEM_H

#include "../Events/IEvent.hpp"
#include "../Service/IService.hpp"
#include "../System/ISystem.hpp"
#include "../Configuration/IConfiguration.hpp"

#include "../IO/IFileManager.hpp"

#include "IRenderSystemScene.h"

#include "IInterface.hpp"
#include <Ogre.h>
using namespace Ogre;

class RendererSystem : public ISystem, public IService, public Ogre::WindowEventListener
{

	typedef std::vector< std::string > StringList;

public:

	virtual ~RendererSystem( );

	RendererSystem( Configuration::IConfiguration* configuration )
		: _configuration( configuration )
		, _badStubCreated( false )
		, _isIntialized( false )
		, _root( 0 )
		, _window( 0 )
		, _sceneManager( 0 )
		, _interface( 0 )
		, _badFactory( 0 )
		, _scene( 0 )
		, _configSectionName( "Graphics" )
	{

	}

	virtual void Initialize( );
	virtual void Update( float deltaMilliseconds );
	virtual void Release( ) { };

	inline System::Types::Type GetType( ) { return System::Types::RENDER; };

	inline ISystemScene* CreateScene( );

	inline AnyValue::AnyValueMap GetProperties( ) { return _properties; };
	inline void SetProperty( const std::string& name, AnyValue value );

	virtual void windowClosed( RenderWindow* rw );

	AnyValue::AnyValueMap Execute( const std::string& actionName, AnyValue::AnyValueMap parameters );

private:

	void OnGraphicsSettingsUpdated( const Events::IEvent* event );

	void Constructor( Configuration::IConfiguration* configuration, IFileManager* fileManager );
	void LoadResources( );
	void CreateRenderWindow( const std::string& windowTitle, int width, int height, bool fullScreen );
	std::vector< std::string > GetVideoModes( ) const;

	AnyValue::AnyValueMap _properties;
	Configuration::IConfiguration* _configuration;
	IInterface* _interface;
	bool _badStubCreated;
	bool _isIntialized;
	IRenderSystemScene* _scene;

	std::string _configSectionName;
	std::vector< std::string > _supportedVideoModes;
	std::string _skyBoxMaterial;

	Ogre::Root* _root;
	Ogre::SceneManager* _sceneManager;
	Ogre::RenderWindow* _window;
	Ogre::ArchiveFactory* _badFactory;

	RendererSystem( ) { };
	RendererSystem( const RendererSystem & copy ) { };
	RendererSystem & operator = ( const RendererSystem & copy ) { return *this; };

};

#endif