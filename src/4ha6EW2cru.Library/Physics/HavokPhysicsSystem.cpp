#include "HavokPhysicsSystem.h"

using namespace Maths;

#include "../Logging/Logger.h"
using namespace Logging;

#include "../Management/Management.h"

#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Memory/hkThreadMemory.h>
#include <Common/Base/Memory/Memory/Pool/hkPoolMemory.h>									

#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastInput.h>			
#include <Physics/Collide/Query/Collector/RayCollector/hkpAllRayHitCollector.h>
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>			

#include <Physics/Dynamics/World/hkpWorld.h>								
#include <Physics/Dynamics/Entity/hkpRigidBody.h>							

#define INCLUDE_HAVOK_PHYSICS_CLASSES
#define HK_CLASSES_FILE <Common/Serialize/Classlist/hkClasses.h>
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.cxx>
#define HK_COMPAT_FILE <Common/Compat/hkCompatVersions.h>
#include <Common/Compat/hkCompat_None.cxx> 

namespace Physics
{
	ISystemScene* HavokPhysicsSystem::CreateScene( )
	{
		hkpWorldCinfo info;

		info.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_DISCRETE;
		info.m_gravity.set( 0,-9.8f,0);
		info.m_collisionTolerance = 0.1f; 
		info.setBroadPhaseWorldSize( 10000.0f );
		info.setupSolverInfo( hkpWorldCinfo::SOLVER_TYPE_4ITERS_MEDIUM );

		HavokPhysicsSystemScene* scene = new HavokPhysicsSystemScene( info );

		_scenes.push_back( scene );

		return scene;
	}

	void HavokPhysicsSystem::Initialize()
	{
		hkPoolMemory* memoryManager = new hkPoolMemory( );
		_threadMemory = new hkThreadMemory( memoryManager );
		hkBaseSystem::init( memoryManager, _threadMemory, errorReportFunction );
		memoryManager->removeReference( );

		int stackSize = 0x100000;
		_stackBuffer = hkAllocate<char>( stackSize, HK_MEMORY_CLASS_BASE );
		hkThreadMemory::getInstance( ).setStackArea( _stackBuffer, stackSize );

		Management::GetInstance( )->GetServiceManager( )->RegisterService( this ); 
	}

	void HavokPhysicsSystem::Release()
	{
		_threadMemory->setStackArea(0, 0);
		hkDeallocate( _stackBuffer );
		_threadMemory->removeReference();

		hkBaseSystem::quit( );
	}

	void HavokPhysicsSystem::errorReportFunction( const char* errorMessage, void* errorOutputObject )
	{
		Logger::Warn( errorMessage );
	}

	std::vector< std::string > HavokPhysicsSystem::RayQuery( const Maths::MathVector3& origin, const Maths::MathVector3& destination, const bool& sortByDistance, const unsigned int& maxResults )
	{
		hkpWorldRayCastInput input;
		input.m_from = origin.AshkVector4( );
		input.m_to = destination.AshkVector4( );

		hkpAllRayHitCollector collector;

		_scenes[ 0 ]->GetWorld( )->castRay( input, collector );

		if( sortByDistance )
		{
			collector.sortHits( );
		}

		std::vector< std::string > results;
		int resultCount = 0;
		for( int i = 0; i < collector.getHits( ).getSize( ); i++ )
		{
			if ( collector.getHits( )[ i ].hasHit( ) )
			{
				hkpRigidBody* body = hkGetRigidBody( collector.getHits( )[ i ].m_rootCollidable );

				if ( body )
				{
					results.push_back( body->getName( ) );
					
					if ( ++resultCount >= maxResults )
					{
						break;
					}
				}
			}
		}

		return results;
	}

	AnyValue::AnyValueMap HavokPhysicsSystem::Execute( const std::string& actionName, AnyValue::AnyValueMap& parameters )
	{
		AnyValue::AnyValueMap results;

		if ( actionName == "rayQuery" )
		{
			results[ "hits" ] = this->RayQuery( 
				parameters[ "origin" ].GetValue< MathVector3 >( ),
				parameters[ "destination" ].GetValue< MathVector3 >( ),
				parameters[ "sortByDistance" ].GetValue< bool >( ),
				parameters[ "maxResults" ].GetValue< unsigned int >( )
				);
		}

		return results;
	}
};