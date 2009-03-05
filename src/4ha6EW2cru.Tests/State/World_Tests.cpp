#include "World_Tests.h"

#include "../Suites.h"
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( World_Tests, Suites::StateSuite( ) );

#include "../Mocks/Mock_System.hpp"
#include "State/IEntity.hpp"
#include "State/World.h"

void World_Tests::Should_Call_CreateScene_On_The_Given_System_On_Extend( )
{
	Mock_System system( RenderSystemType );
	system.createScene_count.setExpected( 1 );

	World world;
	world.RegisterSystem( &system );

	system.verify( );
}

void World_Tests::Entity_Should_Be_Created_on_CreateEntity()
{
	World world;
	IEntity* entity = world.CreateEntity( "test" );

	CPPUNIT_ASSERT( entity != 0 );
}

void World_Tests::GetSystemScenes_Should_Return_All_Extended_Scenes()
{
	World world;

	Mock_System system1( RenderSystemType );
	world.RegisterSystem( &system1 );

	CPPUNIT_ASSERT( !world.GetSystemScenes( ).empty( ) );
}