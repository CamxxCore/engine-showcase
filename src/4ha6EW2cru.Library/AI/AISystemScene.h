/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   AISystemScene.h
*  @date   2009/04/25
*/
#ifndef AISYSTEMSCENE_H
#define AISYSTEMSCENE_H

#include "IAISystemComponent.hpp"
#include "IAISystemScene.hpp"
#include "../Scripting/IScriptSystemScene.hpp"

#include <hash_map>

namespace AI
{
	/*! 
	*  An AI System Specific Scene
	*/
	class AISystemScene : public IAISystemScene
	{

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		~AISystemScene( ) { };


		/*! Default Constructor
		 *
		 *  @return ()
		 */
		AISystemScene( )
		{

		}

		/*!  Initializes the System Scene
		*
		*  @return (void)
		*/
		void Initialize( );

		/*! Steps internal data of the SystemScene
		*
		*  @param[in] float deltaMilliseconds
		*  @return (void)
		*/
		void Update( const float& deltaMilliseconds );


		/*! Destroys the System Scene
		*
		*  @return (void)
		*/
		inline void Destroy( ) { };


		/*! Gets the System::Types::Type of the SystemScene
		*
		*  @return (System::Types::Type)
		*/
		inline System::Types::Type GetType( ) const { return System::Types::AI; };

		/*! Creates a SystemComponent specific to the SystemScene
		*
		*  @param[in] const std::string & name
		*  @param[in] const std::string & type
		*  @return (ISystemComponent*)
		*/
		ISystemComponent* CreateComponent( const std::string& name, const std::string& type );
		
		/*! Destroys a SystemComponent created by the SystemScene
		*
		*  @param[in] ISystemComponent * component
		*  @return (void)
		*/
		void DestroyComponent( ISystemComponent* component );


		/*! Returns all way points in the Scene
		*
		* @return ( ISystemComponent::SystemComponentList )
		*/
		ISystemComponent::SystemComponentList& GetWaypoints( ) { return m_waypoints; };


		/*! Returns the Navigation Mesh for the Scene
		*
		* @return ( INavigationMesh* )
		*/
		ISystemComponent* GetNavigationMesh( ) { return m_navigationMesh; };

	private:

		ISystemComponent::SystemComponentMap m_components;
		ISystemComponent::SystemComponentList m_waypoints;
		ISystemComponent* m_navigationMesh;

	};
};

#endif