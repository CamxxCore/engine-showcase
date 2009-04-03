#ifndef __INPUTSYSTEMSCENE_H
#define __INPUTSYSTEMSCENE_H

#include <vector>

#include "InputSystemComponent.h"

#include "../System/ISystem.hpp"
#include "../System/ISystemScene.hpp"

#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

class InputSystemScene : public ISystemScene
{
	typedef std::vector< InputSystemComponent* > InputSystemComponentList;

public:

	virtual ~InputSystemScene( ) { };

	InputSystemScene( OIS::Mouse* mouse, OIS::Keyboard* keyboard )
		: _inputAllowed( true )
		, _mouse( mouse )
		, _keyboard( keyboard )
	{

	}

	ISystemComponent* CreateComponent( const std::string& name, const std::string& type );
	void DestroyComponent( ISystemComponent* component );
	SystemType GetType( ) { return InputSystemType; }

	void Update( float deltaMilliseconds );

	void SetInputAllowed( const bool& inputAllowed ) { _inputAllowed = inputAllowed; };

	/* Fired when the user presses a button on the keyboard */
	bool keyPressed( const OIS::KeyEvent &arg );

	/* Fired when the user releases a button on the keyboard */
	bool keyReleased( const OIS::KeyEvent &arg );

	/* Fired when the user moves the mouse */
	bool mouseMoved( const OIS::MouseEvent &arg );

	/* Fired when the user presses a button on the mouse */
	bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

	/* Fired when the user releases a button on the mouse */
	bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

private:

	bool _inputAllowed;

	InputSystemComponentList _inputComponents;

	OIS::Mouse* _mouse;
	OIS::Keyboard* _keyboard;

	InputSystemScene( ) { };
	InputSystemScene( const InputSystemScene & copy ) { };
	InputSystemScene & operator = ( const InputSystemScene & copy ) { return *this; };

};

#endif