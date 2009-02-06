#ifndef __EVENTTYPE_H
#define __EVENTTYPE_H

/*!
	A list of all possible Events within the Game
*/
enum EventType 
{
	ALL_EVENTS,
	TEST_EVENT,
	VIEW_SCREEN_INITIALIZED,
	VIEW_CHANGE_SCREEN,
	GAME_INITIALIZED,
	GAME_LEVEL_CHANGED,
	GAME_QUIT,
	INPUT_KEY_UP,
	INPUT_KEY_DOWN,
	INPUT_MOUSE_PRESSED,
	INPUT_MOUSE_RELEASED,
	INPUT_MOUSE_MOVED,
	UI_TITLE_SCREEN,
	UI_MAIN_MENU,
	UI_OPTIONS,
	UI_CLEAR,
	LOG_MESSAGE_APPENDED,
	SCRIPT_COMMAND_EXECUTED,
	EVENTTYPE_MAX
	
};

#endif