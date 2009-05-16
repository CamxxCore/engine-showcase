/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   ScriptComponent.h
*  @date   2009/04/27
*/
#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "IScriptComponent.hpp"
#include "../Events/IEvent.hpp"

#include "IScriptController.hpp"
#include "IScriptFunctionHandler.hpp"

#include <luabind/luabind.hpp>

namespace Script
{
	/*!
	 *  A Script System Component 
	 */
	class ScriptComponent : public IScriptComponent
	{
		typedef std::vector< IScriptFunctionHandler* > FunctionList;
		typedef std::vector< IScriptController* > ScriptControllerList;

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		~ScriptComponent( ) { };


		/*! Default Constructor
		*
		*  @param[in] const std::string & name
		*  @return ()
		*/
		ScriptComponent( const std::string& name, lua_State* state )
			: m_name( name )
			, m_id( 0 )
			, m_state( state )
			, m_observer( 0 )
			, m_eventHandlers( 0 )
		{

		};


		/*! Initializes the Component
		*
		*  @param[in] AnyValue::AnyValueMap properties
		*  @return (void)
		*/
		void Initialize( AnyValue::AnyValueMap& properties );


		/*! Steps the internal data of the Component
		*
		*  @param[in] float deltaMilliseconds
		*  @return (void)
		*/
		void Update( const float& deltaMilliseconds );


		/*! Destroys the Component
		*
		*  @return (void)
		*/
		void Destroy( );


		/*! Adds an Observer to the Component
		*
		*  @param[in] IObserver * observer
		*  @return (void)
		*/
		inline void AddObserver( IObserver* observer ) { m_observer = observer; };


		/*! Observes a change in the Subject
		*
		*  @param[in] ISubject * subject
		*  @param[in] const unsigned int& systemChanges
		*  @return (void)
		*/
		void Observe( ISubject* subject, const unsigned int& systemChanges );


		/*! Pushes any Changes to the Observers
		*
		*  @param[in] const unsigned int& systemChanges
		*  @return (void)
		*/
		void PushChanges( const unsigned int& systemChanges );


		/*! Gets the types of Changes this component is interested in
		*
		*  @return (unsigned int)
		*/
		inline unsigned int GetRequestedChanges( ) const 
		{
			return 
				System::Changes::Geometry::All |
				System::Changes::Input::All |
				System::Changes::POI::LookAt;
		};


		/*! Gets the Name of the Component
		*
		*  @return (const std::string&)
		*/
		inline const std::string& GetName( ) const { return m_name; };


		/*! Sets the Id of the component unique to its containing World Entity
		*
		*  @param[in] const unsigned int & id
		*  @return (void)
		*/
		inline void SetId( const unsigned int& id ) { m_id = id; };


		/*! Returns a numerical Id for the component unique to its containing World Entity
		*
		*  @return (unsigned int)
		*/
		inline unsigned int GetId( ) const { return m_id; };


		/*! Gets the System::Types::Type of the Component
		*
		*  @return (System::Types::Type)
		*/
		inline System::Types::Type GetType( ) const { return System::Types::SCRIPT; };


		/*! Gets the properties of the Component
		*
		*  @return (AnyValueMap)
		*/
		AnyValue::AnyValueMap GetAttributes( ) const { return AnyValue::AnyValueMap( ); };


		/*! Sets the Properties of the Component
		*
		*  @param[in] AnyValue::AnyValueMap systemProperties
		*  @return (void)
		*/
		void SetAttributes( AnyValue::AnyValueMap& properties ) { };


		/*! Gets the Position of the Component
		*
		*  @return (MathVector3)
		*/
		inline Maths::MathVector3 GetPosition( ) const { return m_position; };


		/*! Gets the Scale of the Component
		*
		*  @return (MathVector3)
		*/
		inline Maths::MathVector3 GetScale( ) const { return m_scale; };


		/*! Gets the Orientation of the Component
		*
		*  @return (MathQuaternion)
		*/
		inline Maths::MathQuaternion GetOrientation( ) const { return m_orientation; };


		/*! Messages the Component to influence its internal state
		*
		*  @param[in] const std::string & message
		*  @return (AnyValue)
		*/
		AnyValue Message( const std::string& message, AnyValue::AnyValueMap parameters );


		/*! Posts a message to the parent Entity
		 *
		 *  @param[in] const std::string & message
		 *  @param[in] AnyValue::AnyValueMap parameters
		 *  @return (AnyValue)
		 */
		AnyValue PostMessage( const std::string& message, AnyValue::AnyValueMap parameters ) { return m_observer->Message( message, parameters ); };


		/*! Returns the LUA state of the Component
		*
		*  @return (lua_State*)
		*/
		inline lua_State* GetState( ) const { return m_state; };


		/*! Generic Event Handler to Forward Game Events to the Script
		 *
		 *  @param[in] const Events::IEvent * event
		 *  @return (void)
		 */
		void OnEvent( const Events::IEvent* event );


		/* Script Handlers */

		/*! Executes the Loaded Script
		 *
		 *  @return (void)
		 */
		void Execute( );


		/*! Loads a Script From the File System
		 *
		 *  @param[in] const std::string & scriptPath
		 *  @return (void)
		 */
		void LoadScript( const std::string& scriptPath );


		/*! Includes a script into the current LUA State
		 *
		 *  @param[in] const std::string & scriptPath
		 *  @return (void)
		 */
		void IncludeScript( const std::string& scriptPath );


		/*! Registers an LUA function to receive in Game Events
		 *
		 *  @param[in] luabind::object function
		 *  @return (void)
		 */
		void RegisterEvent( const luabind::object& function );


		/*! UnRegisters an LUA function from receiving in Game Events
		 *
		 *  @param[in] luabind::object function
		 *  @return (void)
		 */
		void UnRegisterEvent( const luabind::object& function );


		/*!  Registers an LUA function to be included in the Game Update Loop
		 *
		 *  @param[in] luabind::object function
		 *  @return (void)
		 */
		void RegisterUpdate( const luabind::object& function );


		/*! UnRegisters an LUA function from being included in the Game Update Loop
		*
		*  @param[in] luabind::object function
		*  @return (void)
		*/
		void UnRegisterUpdate( const luabind::object& function );


		/*! Executed the given string as LUA code against the components LUA State
		 *
		 *  @param[in] const std::string & input
		 *  @return (void)
		 */
		void ExecuteString( const std::string& input );


		/*! Broadcasts an Event to the LUA State with no parameters
		 *
		 *  @param[in] const std::string & eventName
		 *  @return (void)
		 */
		void BroadcastEvent( const std::string& eventName );


		/*! Broadcasts an Event to the LUA State with parameters
		 *
		 *  @param[in] const std::string & eventName
		 *  @param[in] const std::string & var1
		 *  @return (void)
		 */
		void BroadcastEvent( const std::string& eventName, const std::string& var1 );


		/*! Broadcasts an Event to the LUA State with parameters
		 *
		 *  @param[in] const std::string & eventName
		 *  @param[in] const int & var1
		 *  @return (void)
		 */
		void BroadcastEvent( const std::string& eventName, const int& var1 );



		/*! Broadcasts an Event to the LUA State with parameters
		 *
		 *  @param[in] const std::string & eventName
		 *  @param[in] const std::string & var1
		 *  @param[in] const std::string & var2
		 *  @return (void)
		 */
		void BroadcastEvent( const std::string& eventName, const std::string& var1, const std::string& var2 );
		
		
		
		/*! Broadcasts an Event to the LUA State with parameters
		 *
		 *  @param[in] const std::string & eventName
		 *  @param[in] const std::string & var1
		 *  @param[in] const int & var2
		 *  @return (void)
		 */
		void BroadcastEvent( const std::string& eventName, const std::string& var1, const int& var2 );
		
		
		/*! Broadcasts an Event to the LUA State with parameters
		 *
		 *  @param[in] const std::string & eventName
		 *  @param[in] const int & var1
		 *  @param[in] const std::string & var2
		 *  @return (void)
		 */
		void BroadcastEvent( const std::string& eventName, const int& var1, const std::string& var2 );
		
		
		/*! Broadcasts an Event to the LUA State with parameters
		 *
		 *  @param[in] const std::string & eventName
		 *  @param[in] const int & var1
		 *  @param[in] const int & var2
		 *  @return (void)
		 */
		void BroadcastEvent( const std::string& eventName, const int& var1, const int& var2 );


		/*! Performs a Ray Query
		 *
		 *  @param[in] bool sortByDistance
		 *  @param[in] int maxResults
		 *  @return (std::vector< std::string >)
		 */
		std::vector< std::string > RayQuery( Maths::MathVector3 origin, Maths::MathVector3 direction, const float& length, const bool& sortByDistance, const unsigned int& maxResults );


		/*! If a Render Component is attached to this component's parent, 
		 *  then this will request it plays the given animation
		 *
		 *  @param[in] const std::string & animationName
		 *  @param[in] bool loopAnimation
		 *  @return (void)
		 */
		void PlayAnimation( const std::string& animationName, const bool& loopAnimation );


		/*! Returns the system time in Milliseconds
		 *
		 *  @return (float)
		 */
		float GetTime( ) const;

		Maths::MathVector3 GetLookAt( ) const { return m_lookAt; };

	private:

		ScriptComponent( const ScriptComponent & copy ) { };
		ScriptComponent & operator = ( const ScriptComponent & copy ) { return *this; };

		lua_State* m_state;
		std::string m_name;
		unsigned int m_id;

		FunctionList m_eventHandlers;
		FunctionList m_updateHandlers;

		ScriptControllerList m_controllers;

		IObserver* m_observer;

		Maths::MathVector3 m_position;
		Maths::MathVector3 m_scale;
		Maths::MathQuaternion m_orientation;
		Maths::MathVector3 m_lookAt;

	};
};

#endif