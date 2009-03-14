#ifndef __KEYBOARDLISTENER_H
#define __KEYBOARDLISTENER_H

#include "OIS/OISKeyboard.h"

#include "../Events/Event.h"
#include "../Events/EventData.hpp"

#include "../System/Management.h"

using OIS::KeyEvent;

/*!
	Listens for input from the Keyboard
*/
class KeyboardListener : public OIS::KeyListener
{

public:

	virtual ~KeyboardListener( ) { };

	KeyboardListener( OIS::Keyboard* keyboard )
		: _keyboard( keyboard )
	{

	};

	/* Fired when the user presses a button on the keyboard */
	bool keyPressed( const KeyEvent &arg )
	{
		Event* event = new Event( INPUT_KEY_DOWN, new KeyEventData( arg.key, _keyboard->getAsString( arg.key ) ) );
		Management::GetInstance( )->GetEventManager( )->TriggerEvent( event );

		return true;
	};

	/* Fired when the user releases a button on the keyboard */
	bool keyReleased( const KeyEvent &arg )
	{
		Event* event = new Event( INPUT_KEY_UP, new KeyEventData( arg.key, _keyboard->getAsString( arg.key ) ) );
		Management::GetInstance( )->GetEventManager( )->TriggerEvent( event );

		return true;
	};

private:

	OIS::Keyboard* _keyboard;

	KeyboardListener( ) { };
	KeyboardListener( const KeyboardListener & copy ) { };
	KeyboardListener & operator = ( const KeyboardListener & copy ) { return *this; };

};

#endif
