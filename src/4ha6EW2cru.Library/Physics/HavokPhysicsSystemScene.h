#ifndef __HAVOKPHYSICS_SYSTEMSCENE
#define __HAVOKPHYSICS_SYSTEMSCENE

#include "../System/ISystemScene.hpp"
#include "../System/ISystemComponent.hpp"

#include <Common/Base/hkBase.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/World/Listener/hkpIslandActivationListener.h>
#include <Physics/Dynamics/World/Listener/hkpIslandPostIntegrateListener.h>

#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics/Utilities/VisualDebugger/hkpPhysicsContext.h>			

class HavokPhysicsSystemScene : public ISystemScene, public hkpIslandPostIntegrateListener
{

	typedef std::map< int, ISystemComponent* > PhysicsSystemComponentList;

public:

	virtual ~HavokPhysicsSystemScene( );

	HavokPhysicsSystemScene( const hkpWorldCinfo& worldInfo );

	ISystemComponent* CreateComponent( const std::string& name, const std::string& type );
	void DestroyComponent( ISystemComponent* component );
	SystemType GetType( ) { return PhysicsSystemType; };

	void Update( float deltaMilliseconds );

	hkpWorld* GetWorld( ) { return _world; };

	virtual void postIntegrateCallback( hkpSimulationIsland *island, const hkStepInfo &stepInfo );

private:

	hkpWorld* _world;
	hkVisualDebugger* _vdb;
	hkpPhysicsContext* _context;
	PhysicsSystemComponentList _components;

	int _lastComponentId;

	HavokPhysicsSystemScene( ) { };
	HavokPhysicsSystemScene( const HavokPhysicsSystemScene & copy ) { };
	HavokPhysicsSystemScene & operator = ( const HavokPhysicsSystemScene & copy ) { return *this; };

};

#endif