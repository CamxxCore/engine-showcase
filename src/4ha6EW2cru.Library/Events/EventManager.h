#ifndef __EVENTMANAGER_H
#define __EVENTMANAGER_H

#include <queue>
#include <map>

#include "IEvent.hpp"
#include "EventListener.h"
#include "IEventListener.hpp"

/*!
	Manages all Events distributed thoughout the Game
*/
class EventManager
{

	typedef std::queue< const IEvent* > EventQueue;
	typedef std::multimap< const EventType, IEventListener* > EventListenerList;

public:

	/*! Retrieves an instance of the EventManager Singleton */
	static EventManager* GetInstance( );

	/*! Releases all resources and the EventManager Singleton */
	void Release( );

	/*! Initializes the Event Managment mechanism */
	static bool Initialize( );

	/*! Queues an Event for processing on the next Tick */
	void QueueEvent( const IEvent* event );

	/*! Fires all events in the Event Queue */
	void Update( );

	/*! Adds an EventListener for Event processing */
	template< class AT >
	void AddEventListener( const EventType eventType, AT* eventTarget, void ( AT::*handlerFunctor ) ( const IEvent* event ) )
	{
		if ( 0 == eventTarget )
		{
			std::string targetNUllMessage = "EventManager::AddEventListener - Event Target is NULL";
			Logger::GetInstance( )->Fatal( targetNUllMessage );
			throw NullReferenceException( targetNUllMessage );
		}

		if ( 0 == handlerFunctor )
		{
			std::string handlerNUllMessage = "EventManager::AddEventListener - Handler Functor is NULL";
			Logger::GetInstance( )->Fatal( handlerNUllMessage );
			throw NullReferenceException( handlerNUllMessage );
		}

		EventListener< AT >* eventListener = new EventListener< AT >( eventType, eventTarget, handlerFunctor );

		std::pair< const EventType, IEventListener* > listenerPair( eventListener->GetEventType( ), eventListener );
		_eventListeners.insert( listenerPair );
	}

	/*! Removed an EventListener and destroys it */
	template< class RT >
	void RemoveEventListener( const EventType eventType, RT* handlerTarget, void ( RT::*handlerFunctor ) ( const IEvent* event ) )
	{
		std::pair< 
			EventListenerList::iterator, 
			EventListenerList::iterator
		> listeners;

		listeners = _eventListeners.equal_range( eventType ); 

		for ( EventListenerList::iterator i = listeners.first; i != listeners.second; ++i )
		{
			EventListener< RT >* eventListener = static_cast< EventListener< RT >* >( ( *i ).second );

			if ( 
				handlerFunctor == eventListener->GetHandlerFunctor( ) &&
				eventType == eventListener->GetEventType( ) &&
				handlerTarget == eventListener->GetHandlerTarget( )
				)
			{
				delete ( *i ).second;
				_eventListeners.erase( i );
				return;
			}
		}
	}

	/*! Gets the number of attached EventListeners */
	//inline int GetEventListenerCount( ) const { return _eventListeners.size( ); };

private:

	EventManager( ) { };
	~EventManager( ) { };
	EventManager( const EventManager & copy ) { };
	EventManager & operator = ( const EventManager & copy ) { return *this; };

	EventQueue _eventQueue;
	EventListenerList _eventListeners;

};

#endif