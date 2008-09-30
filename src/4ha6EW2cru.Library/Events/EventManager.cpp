#include "EventManager.h"
#include "../Logging/Logger.h"
#include "../Exceptions/UnInitializedException.hpp"
#include "../Exceptions/AlreadyInitializedException.hpp"

static EventManager* g_EventManagerInstance = 0;

EventManager* EventManager::GetInstance( )
{
	if ( 0 == g_EventManagerInstance )
	{
		UnInitializedException e( "EventManager::GetInstance - EventManager has not been Initialized" );
		Logger::GetInstance( )->Fatal( e.what( ) );
		throw e;
	}

	return g_EventManagerInstance;
}

void EventManager::Release( )
{
	Logger::GetInstance( )->Info( "EventManager::Release - Releasing Event Manager" );

	while( _eventQueue.size( ) > 0 )
	{
		delete _eventQueue.front( );
		_eventQueue.pop( );
	}

	for( EventListenerList::iterator i = _eventListeners.begin( ); i != _eventListeners.end( ); ++i )
	{
		delete ( *i ).second;
	}

	_eventListeners.erase( _eventListeners.begin( ), _eventListeners.end( ) );

	delete g_EventManagerInstance;
	g_EventManagerInstance = 0;
}

bool EventManager::Initialize( )
{
	Logger::GetInstance( )->Info( "EventManager::Initialize - Initializing Event Manager" );

	if ( g_EventManagerInstance != 0 )
	{
		AlreadyInitializedException e( "EventManager::Initialize - EventManager has already been Initialized" );
		Logger::GetInstance( )->Fatal( e.what ( ) );
		throw e;
	}

	g_EventManagerInstance = new EventManager( );

	return true;	
}

void EventManager::QueueEvent( const IEvent* event )
{
	if ( 0 == event )
	{
		NullReferenceException e( "EventManager::QueueEvent - Attempted to add a NULL Event to the Queue" );
		Logger::GetInstance( )->Fatal( e.what ( ) );
		throw e;
	}

	_eventQueue.push( event );
}

void EventManager::TriggerEvent( const IEvent* event )
{
	if ( 0 == event )
	{
		NullReferenceException e( "EventManager::TriggerEvent - Attempted to trigger a NULL Event" );
		Logger::GetInstance( )->Fatal( e.what ( ) );
		throw e;
	}

	std::pair< 
		EventListenerList::iterator, 
		EventListenerList::iterator
	> listeners;

	std::multimap< const EventType, IEventListener* > eventListeners( _eventListeners );

	listeners = eventListeners.equal_range( ( EventType ) event->GetEventType( ) ); 

	for ( EventListenerList::iterator i = listeners.first; i != listeners.second; ++i )
	{
		( *i ).second->HandleEvent( event );
	}

	delete event;
}

void EventManager::Update( )
{
	std::pair< 
			EventListenerList::iterator, 
			EventListenerList::iterator
		> listeners;

	std::multimap< const EventType, IEventListener* > eventListeners( _eventListeners );

	while( _eventQueue.size( ) > 0 )
	{
		int eventType = _eventQueue.front( )->GetEventType( );

		listeners = eventListeners.equal_range( ( EventType ) eventType ); 

		for ( EventListenerList::iterator i = listeners.first; i != listeners.second; ++i )
		{
			( *i ).second->HandleEvent( _eventQueue.front( ) );
		}

		delete _eventQueue.front( );
		_eventQueue.pop( );
	}
}