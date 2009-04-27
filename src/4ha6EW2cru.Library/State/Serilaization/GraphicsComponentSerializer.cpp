#include "GraphicsComponentSerializer.h"

#include <yaml.h>

namespace Serialization
{
	ISystemComponent* GraphicsComponentSerializer::Deserialize( const std::string& entityName, const YAML::Node& componentNode, const SystemSceneMap&  systemScenes )
	{
		AnyValue::AnyValueMap properties;
	
		for( YAML::Iterator componentProperty = componentNode.begin( ); componentProperty != componentNode.end( ); ++componentProperty ) 
		{
			std::string propertyKey, propertyValue;
	
			componentProperty.first( ) >> propertyKey;
			componentProperty.second( ) >> propertyValue;
	
			properties.insert( std::make_pair( propertyKey, propertyValue ) );
		}
	
		std::string type = properties[ "type" ].GetValue< std::string >( );
	
		SystemSceneMap::const_iterator systemScene = systemScenes.find( System::Types::RENDER );
	
		ISystemComponent* systemComponent = ( *systemScene ).second->CreateComponent( entityName, ( type == "camera" ) ? type : "default" );;
		systemComponent->Initialize( properties );
	
		return systemComponent;
	}
}