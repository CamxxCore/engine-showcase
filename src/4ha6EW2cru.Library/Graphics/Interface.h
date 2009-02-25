#ifndef __ROOTUICONTROLLER_H
#define __ROOTUICONTROLLER_H

#include <MyGUI.h>
using namespace MyGUI;

#include <luabind/luabind.hpp>
using namespace luabind;

#include "../Scripting/Script.h"

class Interface : MyGUI::IUnlinkWidget
{
	typedef std::map< const std::string, object* > WidgetUserData;

public:

	Interface( Gui*  gui )
		: _gui( gui )
	{

	}

	void Initialize( );

	virtual ~Interface( ) { };

	virtual void _unlinkWidget ( WidgetPtr widget );

private:

	/*! Loads a UI Component for Rendering */
	static void LoadComponent( const std::string componentName );

	/*! Retrieves a widget from the UI */
	static WidgetPtr FindWidget( const std::string widgetName );

	/*! Attaches an LUA function to a Widget Event */
	static void ScriptWidget( Widget* widget, const std::string eventName, object function );

	/*! Returns the Screen Width in pixels */
	static inline int GetScreenWidth( ) { return Gui::getInstancePtr( )->getRenderWindow( )->getWidth( ); };

	/*! Returns the Screen Height in pixels */
	static inline int GetScreenHeight( ) { return Gui::getInstancePtr( )->getRenderWindow( )->getHeight( ); };

	/*! Shows the mouse */
	static inline void ShowMouse( ) { Gui::getInstancePtr( )->showPointer( ); };

	/*! Hides the mouse */
	static inline void HideMouse( ) { Gui::getInstancePtr( )->hidePointer( ); };

	/*! Forwards Mouse Button Released Events to the subscribing Widgets in Script */
	static void OnMouseReleased( WidgetPtr widget, int left, int top, MouseButton id );

	/*! Casts a widget to a Button */
	static inline ButtonPtr AsButton( WidgetPtr widget ) { return static_cast< ButtonPtr >( widget ); };

	/*! Casts a widget to a ComboBox */
	static inline ComboBoxPtr AsComboBox( WidgetPtr widget ) { return static_cast< ComboBoxPtr >( widget ); };

	Gui* _gui;
	Script* _script;

};


#endif
