/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   AISystemComponent.h
*  @date   2009/04/25
*/
#ifndef __AISYSTEMCOMPONENT_H
#define __AISYSTEMCOMPONENT_H

#include <string>
#include "../System/SystemType.hpp"

#include "../Maths/MathVector3.hpp"
#include "../Maths/MathQuaternion.hpp"

#include "IBehavior.hpp"
#include "IAISystemComponent.hpp"

namespace AI
{
	/*! 
	 *  An Artificial Intelligence System Scene Component
	 */
	class AISystemComponent : public IAISystemComponent, public IBehaviour
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~AISystemComponent( ) { };


		/*! Default Constructor
		 *
		 *  @param[in] const std::string & name
		 *  @param[in] IScriptComponent * scriptComponent
		 *  @return ()
		 */
		AISystemComponent( const std::string& name, const int& frameAssignment )
			: _name( name )
			, _frameAssignment( frameAssignment )
			, _scriptState( 0 )
			, _observer( 0 )
			, _id( 0 )
		{

		}

		/* Inherited from ISystemComponent */

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
		void AddObserver( IObserver* observer );


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


		/*! Gets the Name of the Component
		 *
		 *  @return (const std::string&)
		 */
		inline const std::string& GetName( ) const { return _name; };


		/*! Sets the Id of the component unique to its containing World Entity
		*
		*  @param[in] const unsigned int & id
		*  @return (void)
		*/
		inline void SetId( const unsigned int& id ) { _id = id; };


		/*! Returns a numerical Id for the component unique to its containing World Entity
		*
		*  @return (unsigned int)
		*/
		inline unsigned int GetId( ) const { return _id; };


		/*! Gets the System::Types::Type of the Component
		 *
		 *  @return (System::Types::Type)
		 */
		inline System::Types::Type GetType( ) const { return System::Types::AI; };


		/*! Gets the types of Changes this component is interested in
		 *
		 *  @return (unsigned int)
		 */
		inline unsigned int GetRequestedChanges( ) const  
		{ 
			return System::Changes::Geometry::All;
		};


		/*! Gets the properties of the Component
		 *
		 *  @return (AnyValueMap)
		 */
		inline AnyValue::AnyValueMap GetProperties( ) const { return AnyValue::AnyValueMap( ); };


		/*! Sets the Properties of the Component
		 *
		 *  @param[in] AnyValue::AnyValueMap systemProperties
		 *  @return (void)
		 */
		inline void SetProperties( AnyValue::AnyValueMap& properties ) { };


		/*! Gets the Position of the Component
		 *
		 *  @return (MathVector3)
		 */
		inline Maths::MathVector3 GetPosition( ) const { return _position; };


		/*! Gets the Scale of the Component
		 *
		 *  @return (MathVector3)
		 */
		inline Maths::MathVector3 GetScale( ) const { return Maths::MathVector3::Zero( ); };


		/*! Gets the Orientation of the Component
		 *
		 *  @return (MathQuaternion)
		 */
		inline Maths::MathQuaternion GetOrientation( ) const { return _orientation; };


		/* Inherited from IBehavior */

		/*! Sets the current Behavior of the Component
		 *
		 *  @param[in] const std::string & behavior
		 *  @return (void)
		 */
		void SetBehavior( const std::string& behavior );


		/*! Gets the current Behavior of the Component
		 *
		 *  @return (std::string)
		 */
		std::string GetBehavior( ) const { return _behavior; };


		/* AI Specific */

		/*! Returns the frame number that this ai will perform its logic update
		*
		*  @return (int)
		*/
		inline int GetFrameAssignment( ) const { return _frameAssignment; };


		/* Script Callbacks */

		/*! Walks the Parent Entity Forward
		 *
		 *  @return (void)
		 */
		void WalkForward( );


		/*! Walks the Parent Entity Backwards
		 *
		 *  @return (void)
		 */
		void WalkBackward( );


		/*! Rotates the Parent Entity towards the Player
		 *
		 *  @return (void)
		 */
		void FacePlayer( );


		/*! Fires the AI Weapon
		 *
		 *  @return (void)
		 */
		void FireWeapon( );


		/*! Gets the Distance to the Player
		 *
		 *  @return (float)
		 */
		inline float GetPlayerDistance( ) { return _playerDistance; };


		/*! Plays an Animation
		 *
		 *  @param[in] const std::string & animationName
		 *  @param[in] const bool & loopAnimation
		 *  @return (void)
		 */
		void PlayAnimation( const std::string& animationName, const bool& loopAnimation );

	private:

		std::string _name;
		unsigned int _id;

		lua_State* _scriptState;
		int _frameAssignment;

		IObserver* _observer;

		std::string _behavior;

		Maths::MathVector3 _position;
		Maths::MathQuaternion _orientation;

		Maths::MathVector3 _playerPosition;
		Maths::MathQuaternion _playerOrientation;
		float _playerDistance;

	};
};

#endif