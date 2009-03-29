#include "Interface.h"

#include "../Events/Event.h"
#include "../Events/EventManager.h"

#include "MyGUI_Any.h"

#include "../System/Management.h"
#include "../Scripting/ScriptSystemScene.h"
#include "../Scripting/ScriptSystem.h"
#include "../Scripting/ScriptComponent.h"

static ScriptSystemScene* g_InterfaceScriptScene = 0;

Interface::~Interface( )
{
	Management::GetInstance( )->GetEventManager( )->RemoveEventListener( INPUT_MOUSE_PRESSED, this, &Interface::OnMousePressed );
	Management::GetInstance( )->GetEventManager( )->RemoveEventListener( INPUT_MOUSE_MOVED, this, &Interface::OnMouseMoved );
	Management::GetInstance( )->GetEventManager( )->RemoveEventListener( INPUT_MOUSE_RELEASED, this, &Interface::OnMouseReleased );
	Management::GetInstance( )->GetEventManager( )->RemoveEventListener( INPUT_KEY_DOWN, this, &Interface::OnKeyDown );
	Management::GetInstance( )->GetEventManager( )->RemoveEventListener( INPUT_KEY_UP, this, &Interface::OnKeyUp );

	if ( _gui != 0 )
	{
		_gui->shutdown( );
		delete _gui;
		_gui = 0;
	}

	if ( g_InterfaceScriptScene != 0 )
	{
		delete g_InterfaceScriptScene;
		g_InterfaceScriptScene = 0;
	}
}

void Interface::Initialize( )
{
	g_InterfaceScriptScene = ( ScriptSystemScene* ) Management::GetInstance( )->GetSystemManager( )->GetSystem( ScriptSystemType )->CreateScene( );
	g_InterfaceScriptScene->Initialize( );

	Ogre::RenderWindow* window = static_cast< Ogre::RenderWindow* >( _ogreRoot->getRenderTarget(  _configuration->Find< std::string >( "Graphics", "window_title" ) ) );
	_gui->initialise( window, "/data/interface/core/core.xml" );

	Management::GetInstance( )->GetEventManager( )->AddEventListener( INPUT_MOUSE_PRESSED, this, &Interface::OnMousePressed );
	Management::GetInstance( )->GetEventManager( )->AddEventListener( INPUT_MOUSE_MOVED, this, &Interface::OnMouseMoved );
	Management::GetInstance( )->GetEventManager( )->AddEventListener( INPUT_MOUSE_RELEASED, this, &Interface::OnMouseReleased );
	Management::GetInstance( )->GetEventManager( )->AddEventListener( INPUT_KEY_DOWN, this, &Interface::OnKeyDown );
	Management::GetInstance( )->GetEventManager( )->AddEventListener( INPUT_KEY_UP, this, &Interface::OnKeyUp );

	ScriptComponent* scriptComponent = ( ScriptComponent* ) g_InterfaceScriptScene->CreateComponent( "interface", "default" );

	SystemPropertyList properties;
	std::string scriptPath = "/data/interface/interface.lua";
	properties.insert( std::make_pair( "scriptPath", SystemProperty( "scriptPath", scriptPath ) ) );
	scriptComponent->Initialize( properties );

	module( scriptComponent->GetState( ) )
	[
		def( "findWidget", &Interface::FindWidget ),
		def( "loadComponent", &Interface::LoadComponent ),
		def( "getScreenWidth", &Interface::GetScreenWidth ),
		def( "getScreenHeight", &Interface::GetScreenHeight ),
		def( "scriptWidget", &Interface::ScriptWidget ),
		def( "executeString", &Interface::ExecuteString ),
		def( "showMouse", &Interface::ShowMouse ),
		def( "hideMouse", &Interface::HideMouse ),

		def( "registerEventHandler", &Interface::RegisterEventHandler ),
		def( "registerEvent", &Interface::RegisterEvent ),
		def( "unregisterEvent", &Interface::UnRegisterEvent ),
		def( "broadcastEvent", &Interface::BroadcastEvent ),

		class_< Widget >( "Widget" )
			.def( "getDimensions", &Widget::getClientCoord )
			.def( "setPosition", ( void( Widget::* )( int, int ) ) &Widget::setPosition )
			.def( "getType", &Widget::getClassTypeName )
			.def( "setVisible", &Widget::setVisible )
			.def( "isVisible", &Widget::isVisible )
			.def( "getText", &Widget::getCaption )
			.def( "setText", &Widget::setCaption )
			.def( "asButton", &Interface::AsButton )
			.def( "asComboBox", &Interface::AsComboBox )
			.def( "asEditBox", &Interface::AsEditBox ),

		class_< Button >( "Button" )
			.def( "setChecked", &Button::setStateCheck )
			.def( "getChecked", &Button::getStateCheck ),

		class_< ComboBox, Widget >( "ComboBox" )
			.def( "addItem", ( void ( ComboBox::* ) ( const std::string&, const std::string& ) ) &ComboBox::addItem )
			.def( "getValueAt", ( const std::string& ( ComboBox::* ) ( int ) ) &ComboBox::getItemNameAt )
			.def( "getSelectedIndex", &ComboBox::getIndexSelected )
			.def( "setSelectedIndex", &ComboBox::setIndexSelected ),

		class_< Edit, Widget >( "EditBox" ),

		class_< IntCoord >( "IntCoord" )
			.def_readonly( "x" , &IntCoord::left )
			.def_readonly( "y" , &IntCoord::top )
			.def_readonly( "width" , &IntCoord::width )
			.def_readonly( "height" , &IntCoord::height ),

		class_< Ogre::UTFString >( "utf" )
			.def( constructor< std::string >( ) )
			.def( "asString", &Interface::AsString ),

		class_< Any >( "Any" )
			.def( constructor<>( ) )
	];

	lua_pcall( scriptComponent->GetState( ), 0, 0, 0 );

	WidgetManager::getInstancePtr( )->registerUnlinker( this );
}

void Interface::Update( const float deltaMilliseconds ) const
{
	_gui->injectFrameEntered( deltaMilliseconds );
}

void Interface::LoadComponent( const std::string componentName )
{
	std::stringstream layoutPath;
	layoutPath << "/data/interface/components/" << componentName << ".layout";

	LayoutManager::getInstance().load( layoutPath.str( ) );

	std::stringstream scriptPath;
	scriptPath << "/data/interface/components/" << componentName << ".lua";

	ScriptComponent* scriptComponent = ( ScriptComponent* ) g_InterfaceScriptScene->CreateComponent( componentName, "default" );

	SystemPropertyList properties;
	properties.insert( std::make_pair( "scriptPath", SystemProperty( "scriptPath", scriptPath.str( ) ) ) );
	scriptComponent->Initialize( properties );

	lua_pcall( scriptComponent->GetState( ), 0, 0, 0 );
}

WidgetPtr Interface::FindWidget( const std::string widgetName )
{
	return Gui::getInstancePtr( )->findWidgetT( widgetName );
}

void Interface::_unlinkWidget ( WidgetPtr widget )
{
	void* userData = widget->getUserData( );
	WidgetUserData* widgetUserData = static_cast< WidgetUserData* >( userData );
	
	if ( 0 != widgetUserData )
	{
		for ( WidgetUserData::iterator i = widgetUserData->begin( ); i != widgetUserData->end( ); ++i )
		{
			delete ( *i ).second;
		}

		delete widgetUserData;
	}
}

void Interface::ScriptWidget( Widget* widget, const std::string eventName, object function )
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
		widget->eventMouseButtonReleased = newDelegate( &Interface::OnMouseReleased );
	}

	if ( eventName == "onKeyUp" )
	{
		widget->eventKeyButtonReleased = newDelegate( &Interface::OnKeyUp );
	}
}

void Interface::OnMouseReleased( WidgetPtr widget, int left, int top, MouseButton id )
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

void Interface::OnKeyUp( WidgetPtr widget, KeyCode key )
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

void Interface::OnMouseMoved( const IEvent* event )
{
	MouseEventData* eventData = static_cast< MouseEventData* >( event->GetEventData( ) );
	_gui->injectMouseMove( eventData->GetMouseState( ).X.abs, eventData->GetMouseState( ).Y.abs, eventData->GetMouseState( ).Z.abs );
}

void Interface::OnMousePressed( const IEvent* event )
{
	MouseEventData* eventData = static_cast< MouseEventData* >( event->GetEventData( ) );
	_gui->injectMousePress( eventData->GetMouseState( ).X.abs, eventData->GetMouseState( ).Y.abs, MouseButton::Enum( eventData->GetMouseButtonId( ) ) );
}

void Interface::OnMouseReleased( const IEvent* event )
{
	MouseEventData* eventData = static_cast< MouseEventData* >( event->GetEventData( ) );
	_gui->injectMouseRelease( eventData->GetMouseState( ).X.abs, eventData->GetMouseState( ).Y.abs, MouseButton::Enum( eventData->GetMouseButtonId( ) ) );
}

void Interface::OnKeyUp( const IEvent* event )
{
	KeyEventData* eventData = static_cast< KeyEventData* >( event->GetEventData( ) );
	_gui->injectKeyRelease( KeyCode::Enum( eventData->GetKeyCode( ) ) );
}

void Interface::OnKeyDown( const IEvent* event )
{
	KeyEventData* eventData = static_cast< KeyEventData* >( event->GetEventData( ) );
	_gui->injectKeyPress( KeyCode::Enum( eventData->GetKeyCode( ) ) );
}

void Interface::RegisterEvent( EventType eventType, object function )
{
	g_InterfaceScriptScene->RegisterEvent( eventType, function );
}

void Interface::UnRegisterEvent( EventType eventType, object function )
{
	g_InterfaceScriptScene->UnRegisterEvent( eventType, function );
}

void Interface::BroadcastEvent( EventType eventType )
{
	Management::GetInstance( )->GetEventManager( )->QueueEvent( new Event( eventType ) );
}

void Interface::ExecuteString( const std::string& input )
{
	g_InterfaceScriptScene->ExecuteString( input );
}

void Interface::RegisterEventHandler( object function )
{
	g_InterfaceScriptScene->RegisterEvent( ALL_EVENTS, function );
}