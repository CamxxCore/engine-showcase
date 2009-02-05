#include "RootUIController.h"

#include "../../Scripting/ScriptManager.h"
#include "../../Events/EventManager.h"

#include "UIView.h"
#include "UIController.h"

RootUIController::~RootUIController( )
{	
	for ( WidgetList::iterator widget = _widgetList.begin( ); widget != _widgetList.end( ); ++widget )
	{
		void* userData = ( *widget )->getUserData( );
		WidgetUserData* widgetUserData = static_cast< WidgetUserData* >( userData );

		for ( WidgetUserData::iterator i = widgetUserData->begin( ); i != widgetUserData->end( ); ++i )
		{
			delete ( *i ).second;
		}

		delete widgetUserData;
	}

	if ( _script != 0 )
	{
		delete _script;
	}
}

void RootUIController::Initialize( )
{
	_script = ScriptManager::GetInstance( )->CreateScript( "/data/interface/interface.lua" );

	module( _script->GetState( ) )
	[
		def( "findWidget", &RootUIController::FindWidget ),
		def( "loadComponent", &RootUIController::LoadComponent ),
		def( "getScreenWidth", &RootUIController::GetScreenWidth ),
		def( "getScreenHeight", &RootUIController::GetScreenHeight ),
		def( "scriptWidget", &RootUIController::ScriptWidget ),
		def( "showMouse", &RootUIController::ShowMouse ),
		def( "hideMouse", &RootUIController::HideMouse ),

		class_< Widget >( "Widget" )
			.def( "getDimensions", &MyGUI::Widget::getClientCoord )
			.def( "setPosition", ( void( MyGUI::Widget::* )( int, int ) ) &MyGUI::Widget::setPosition )
			.def( "getType", &MyGUI::Widget::getClassTypeName )
			.def( "hide", &MyGUI::Widget::hide )
			.def( "show", &MyGUI::Widget::show ),

		class_< IntCoord >( "IntCoord" )
			.def_readonly( "x" , &MyGUI::IntCoord::left )
			.def_readonly( "y" , &MyGUI::IntCoord::top )
			.def_readonly( "width" , &MyGUI::IntCoord::width )
			.def_readonly( "height" , &MyGUI::IntCoord::height )
	];

	_script->Initialize( );
}

WidgetPtr RootUIController::FindWidget( const std::string widgetName )
{
	return Gui::getInstancePtr( )->findWidgetT( widgetName );
}

void RootUIController::ScriptWidget( Widget* widget, const std::string eventName, object function )
{
	/*void* userData = widget->getUserData( );
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
		widget->eventMouseButtonReleased = newDelegate( &RootUIController::OnMouseReleased );
	}*/
}

void RootUIController::OnMouseReleased( Widget* widget, int left, int top, MouseButton buttonId )
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

void RootUIController::LoadComponent( const std::string componentName )
{
	std::stringstream layoutPath;
	layoutPath << "/data/interface/components/" << componentName << ".layout";

	MyGUI::LayoutManager::getInstance().load( layoutPath.str( ) );

	std::stringstream scriptPath;
	scriptPath << "/data/interface/components/" << componentName << ".lua";

	ScriptManager::GetInstance( )->LoadScript( scriptPath.str( ) );
}