#include "UXSystemComponent.h"

using namespace luabind;
using namespace MyGUI;

#include "../Scripting/ScriptEvent.hpp"
using namespace Script;

#include "../Service/IService.hpp"
#include "../Management/Management.h"

namespace UX
{
	std::vector< std::string > UXSystemComponent::GetSupportedResolutions( )
	{
		typedef std::vector< std::string > StringVector;

		IService* renderService = Management::GetInstance( )->GetServiceManager( )->FindService( System::Types::RENDER );
		StringVector resolutions = renderService->Execute( "getAvailableVideoModes", AnyValue::AnyValueMap( ) )[ "availableVideoModes" ].GetValue< StringVector >( );

		std::multimap< int, std::string > resolutionWidths;

		for( StringVector::iterator i = resolutions.begin( ); i != resolutions.end( ); ++i )
		{
			std::string resolution = ( *i );

			std::stringstream resolutionStream;
			resolutionStream << resolution.substr( 0, resolution.find( " x " ) );

			int resolutionWidth = 0;
			resolutionStream >> resolutionWidth;
			resolutionWidths.insert( std::make_pair( resolutionWidth, resolution ) );
		}

		resolutions.clear( );

		for( std::multimap< int, std::string >::iterator i = resolutionWidths.begin( ); i != resolutionWidths.end( ); ++i )
		{
			resolutions.push_back( ( *i ).second );
		}

		return resolutions;
	}

	void UXSystemComponent::ChangeResolution( int width, int height, bool isFullScreen )
	{
		IService* renderService = Management::GetInstance( )->GetServiceManager( )->FindService( System::Types::RENDER );

		AnyValue::AnyValueMap parameters;
		parameters[ "width" ] = width;
		parameters[ "height" ] = height;
		parameters[ "fullScreen" ] = isFullScreen;

		renderService->Execute( "changeResolution", parameters );

		Management::GetInstance( )->GetEventManager( )->QueueEvent( new ScriptEvent( "GRAPHICS_SETTINGS_CHANGED", width, height ) );

		_scene->GetGui( )->windowResized( _scene->GetGui( )->getRenderWindow( ) );
	}

	void UXSystemComponent::SetInputAllowed( bool inputAllowed )
	{
		IService* inputService = Management::GetInstance( )->GetServiceManager( )->FindService( System::Types::INPUT );
		
		AnyValue::AnyValueMap parameters;
		parameters[ "inputAllowed" ] = inputAllowed;
		
		inputService->Execute( "setInputAllowed", parameters );
	}

	void UXSystemComponent::ScriptWidget( MyGUI::Widget* widget, const std::string eventName, luabind::object function )
	{
		void* userData = widget->getUserData( );

		WidgetUserData* widgetUserData = static_cast< WidgetUserData* >( userData );

		if ( widgetUserData == 0 )
		{
			widgetUserData = new WidgetUserData( );
		}

		object* handlerFunctionPtr = new object( function );
		widgetUserData->insert( std::make_pair( eventName, handlerFunctionPtr ) );

		widget->setUserData( static_cast< void* >( widgetUserData ) );

		if ( eventName == "onRelease" )
		{
			widget->eventMouseButtonReleased = newDelegate( &UXSystemComponent::OnMouseReleased );
		}

		if ( eventName == "onKeyUp" )
		{
			widget->eventKeyButtonReleased = newDelegate( &UXSystemComponent::OnKeyUp );
		}
	}

	void UXSystemComponent::LoadComponent( const std::string componentName )
	{
		_scene->CreateComponent( componentName, "default" );
	}

	void UXSystemComponent::SetFarClip( const float& farClip )
	{

	}

	void UXSystemComponent::OnMouseReleased( MyGUI::WidgetPtr widget, int left, int top, MyGUI::MouseButton id )
	{
		void* userData = widget->getUserData( );
		WidgetUserData* widgetUserData = static_cast< WidgetUserData* >( userData );

		for ( WidgetUserData::iterator i = widgetUserData->begin( ); i != widgetUserData->end( ); ++i )
		{
			if ( ( *i ).first == "onRelease" )
			{
				object eventHandler = *( *i ).second;
				eventHandler( left, top );
			}
		}
	}

	void UXSystemComponent::OnKeyUp( MyGUI::WidgetPtr widget, MyGUI::KeyCode key )
	{
		void* userData = widget->getUserData( );
		WidgetUserData* widgetUserData = static_cast< WidgetUserData* >( userData );

		for ( WidgetUserData::iterator i = widgetUserData->begin( ); i != widgetUserData->end( ); ++i )
		{
			if ( ( *i ).first == "onKeyUp" )
			{
				Char keyCode = InputManager::getInstancePtr( )->getKeyChar( key, 0 );
				char* keyText = ( char* ) &keyCode;

				object eventHandler = *( *i ).second;
				eventHandler( keyCode, std::string( keyText ) );
			}
		}
	}
}