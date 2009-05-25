/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   AISystemComponent.h
*  @date   2009/04/25
*/
#ifndef AISYSTEMCOMPONENT_H
#define AISYSTEMCOMPONENT_H

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
	class AISystemComponent : public IAISystemComponent
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
			: m_name( name )
			, m_frameAssignment( frameAssignment )
			, m_scriptState( 0 )
			, m_observer( 0 )
			, m_playerDistance( 0 )
		{

		}

		/* Inherited from ISystemComponent */

		/*! Initializes the Component
		 *
		 *  @param[in] AnyType::AnyValueMap attributes
		 *  @return (void)
		 */
		void Initialize( );


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


		/*! Posts a message to observers
		*
		*  @param[in] const std::string & message
		*  @param[in] AnyType::AnyValueMap parameters
		*  @return (AnyType)
		*/
		AnyType PushMessage( const System::Message& message, AnyType::AnyTypeMap parameters );


		/*! Messages the Component to influence its internal state
		*
		*  @param[in] const std::string & message
		*  @return (AnyType)
		*/
		AnyType Message( const System::Message& message, AnyType::AnyTypeMap parameters );


		/*! Gets the attributes of the Component
		 *
		 *  @return (AnyValueMap)
		 */
		inline AnyType::AnyTypeMap GetAttributes( ) const { return m_attributes; };


		/*! Sets an Attribute on the Component *
		*
		*  @param[in] const unsigned int attributeId
		*  @param[in] const AnyType & value
		*/
		inline void SetAttribute( const System::Attribute& attributeId, const AnyType& value ) { m_attributes[ attributeId ] = value; };


		/* AI Specific */

		/*! Returns the frame number that this ai will perform its logic update
		*
		*  @return (int)
		*/
		inline int GetFrameAssignment( ) const { return m_frameAssignment; };


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
		inline float GetPlayerDistance( ) { return m_playerDistance; };


		/*! Plays an Animation
		 *
		 *  @param[in] const std::string & animationName
		 *  @param[in] const bool & loopAnimation
		 *  @return (void)
		 */
		void PlayAnimation( const std::string& animationName, const bool& loopAnimation );

		/*! Gets the Name of the Component
		*
		*  @return (const std::string&)
		*/
		inline std::string GetName( ) { return m_attributes[ System::Attributes::Name ].As< std::string >( ); };

	private:

		std::string m_name;

		lua_State* m_scriptState;
		int m_frameAssignment;

		IObserver* m_observer;

		float m_playerDistance;

		AnyType::AnyTypeMap m_attributes;

	};
};

#endif