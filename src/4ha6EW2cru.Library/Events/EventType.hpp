#ifndef __EVENTTYPE_H
#define __EVENTTYPE_H

/*!
	A list of all possible Events within the Game
*/
enum EventType 
{

	TEST_EVENT,
	SCREEN_INITIALIZED,
	CHANGE_SCREEN,
	GAME_INITIALIZED,
	GAME_QUIT,
	KEY_UP,
	KEY_DOWN,
	INPUT_MOUSE_PRESSED,
	INPUT_MOUSE_RELEASED,
	INPUT_MOUSE_MOVED,
	EVENTTYPE_MAX
	
};

#endif