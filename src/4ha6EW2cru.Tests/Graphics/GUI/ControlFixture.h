#ifndef __CONTROLFIXTURE_H
#define __CONTROLFIXTURE_H

#include <cppunit/extensions/HelperMacros.h>

#include "Graphics/IRenderer.hpp"

class ControlFixture : public CPPUNIT_NS::TestFixture
{

	CPPUNIT_TEST_SUITE( ControlFixture );

	//CPPUNIT_TEST( Should_Throw_On_Initialize_Given_NULL_Not_Gui );
	//CPPUNIT_TEST( Should_Throw_On_Initialize_Given_Layout_Not_Found );
	CPPUNIT_TEST( Should_Throw_On_Initialize_Given_Script_Not_Found );
	CPPUNIT_TEST( Should_Initialize_Correctly );

	CPPUNIT_TEST_SUITE_END( );

public:

	void setUp( );
	void tearDown( );

protected:

	//void Should_Throw_On_Initialize_Given_NULL_Not_Gui( );
	//void Should_Throw_On_Initialize_Given_Layout_Not_Found( );
	void Should_Throw_On_Initialize_Given_Script_Not_Found( );
	void Should_Initialize_Correctly( );

private:

	IRenderer* _renderer;

};

#endif