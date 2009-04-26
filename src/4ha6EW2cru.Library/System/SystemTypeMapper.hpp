/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   src\4ha6EW2cru.Library\System\SystemTypeMapper.hpp
*  @date   2009/04/25
*/
#ifndef __SYSTEMTYPEMAPPER_H
#define __SYSTEMTYPEMAPPER_H

#include <string>
#include "../Exceptions/OutOfRangeException.hpp"

namespace System
{
	/*! 
	 *  Maps Strings to System::Types::Type's
	 */
	class TypeMapper
	{

	public:

		/*! Maps the given string to a System::Types::Type
		 *
		 *  @param[in] std::string systemType
		 *  @return (System::Types::Type)
		 */
		inline static System::Types::Type StringToType( std::string systemType )
		{
			System::Types::Type returnType = System::Types::NONE;

			if( systemType == "graphics" )
			{
				return System::Types::RENDER;
			}
			else if ( systemType == "script" )
			{
				return System::Types::SCRIPT;
			}
			else if ( systemType == "geometry" )
			{
				return System::Types::GEOMETRY;
			}
			else if ( systemType == "physics" )
			{
				return System::Types::PHYSICS;
			}
			else if ( systemType == "input" )
			{
				return System::Types::INPUT;
			}
			else if ( systemType == "ai" )
			{
				return System::Types::AI;
			}

			if ( returnType == System::Types::NONE )
			{
				throw OutOfRangeException( "Couldn't match string to System::Types::Type" );
			}

			return System::Types::NONE;
		}
	};
};

#endif