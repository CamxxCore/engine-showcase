#include "GeometrySystemComponent.h"

#include "../Physics/PhysicsSystemComponent.h"
#include "../ai/AISystemComponent.h"
#include "../Input/InputSystemComponent.h"

void GeometrySystemComponent::Initialize( AnyValueMap properties )
{
	for( AnyValueMap::iterator i = properties.begin( ); i != properties.end( ); ++i )
	{
		if ( ( *i ).first == "position" )
		{
			_position = ( *i ).second.GetValue< MathVector3 >( );
			this->PushChanges( System::Changes::Geometry::Position );
		}

		if ( ( *i ).first == "scale" )
		{
			_scale = ( *i ).second.GetValue< MathVector3 >( );
			this->PushChanges( System::Changes::Geometry::Scale );
		}

		if ( ( *i ).first == "orientation" )
		{
			_orientation = ( *i ).second.GetValue< MathQuaternion >( );
			this->PushChanges( System::Changes::Geometry::Orientation );
		}
	}
}

void GeometrySystemComponent::PushChanges( unsigned int systemChanges )
{
	if ( _observer != 0 )
	{
		_observer->Observe( this, systemChanges );
	}
}

void GeometrySystemComponent::Observe( ISubject* subject, unsigned int systemChanges )
{
	ISystemComponent* component = static_cast< ISystemComponent* >( subject );

	if ( component->GetType( ) == PhysicsSystemType )
	{
		PhysicsSystemComponent* physicsComponent = static_cast< PhysicsSystemComponent* >( subject );

		_position = physicsComponent->GetPosition( );
		_orientation = physicsComponent->GetOrientation( );

		this->PushChanges( 
			System::Changes::Geometry::Position |
			System::Changes::Geometry::Orientation
			);
	}

	if ( component->GetType( ) == AISystemType )
	{
		AISystemComponent* aiComponent = static_cast< AISystemComponent* >( subject );

		_position = aiComponent->GetPosition( );
		_orientation = aiComponent->GetOrientation( );

		this->PushChanges( 
			System::Changes::Geometry::Position |
			System::Changes::Geometry::Orientation
			);
	}
}