#ifndef __MOCK_ENTITY_H
#define __MOCK_ENTITY_H

#include "mockpp/mockpp.h"
#include "mockpp/MockObject.h"
#include "mockpp/ExpectationCounter.h"

USING_NAMESPACE_MOCKPP


class Mock_Entity : public IEntity, public MockObject
{

public:

	~Mock_Entity( ) { };

	Mock_Entity( )
		: MockObject( "Mock_Entity", 0 )
	{

	}

	const std::string& GetName( ) { return "test_entity"; };
	void AddComponent( ISystemComponent* component ) { _components.push_back( component ); }
	SystemComponentList& GetComponents( ) { return _components; };

private:

	Mock_Entity & operator = ( const Mock_Entity & copy ) { return *this; };

	SystemComponentList _components;
};

#endif