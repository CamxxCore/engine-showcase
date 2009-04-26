/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   src\4ha6EW2cru.Library\Configuration\ConfigurationFile.h
*  @date   2009/04/25
*/
#ifndef __CONFIGURATIONFILE_H
#define __CONFIGURATIONFILE_H

#include "IConfigurationFile.hpp"

#include "../IO/FileBuffer.hpp"
#include "../Utility/SimpleIni.h"

namespace Configuration
{
	/*! 
	 *  Loads and Saves Configuration Information to the File System
	 */
	class ConfigurationFile : public IConfigurationFile
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		~ConfigurationFile( );


		/*! Loads the Configuration File from the specified path
		 *
		 *  @param[in] const std::string & filePath
		 *  @return (ConfigurationFile*)
		 */
		static ConfigurationFile* Load( const std::string& filePath );
		

		/*! Finds a Configuration Item based on the given section and key
		 *
		 *  @param[in] const std::string & section
		 *  @param[in] const std::string & key
		 *  @param[in] const AnyValue & defaultValue
		 *  @return (AnyValue)
		 */
		AnyValue FindConfigItem( const std::string& section, const std::string& key, const AnyValue& defaultValue );


		/*! Updates a configuration item based on the given section and key
		 *
		 *  @param[in] const std::string & section
		 *  @param[in] const std::string & key
		 *  @param[in] const AnyValue & value
		 *  @return (void)
		 */
		void Update( const std::string& section, const std::string& key, const AnyValue& value );


		/*! Saves the configuration file to the File System
		 *
		 *  @param[in] const std::string & filePath
		 *  @return (void)
		 */
		void Save( const std::string& filePath );

	private:

		ConfigurationFile( const FileBuffer* fileBuffer );

		CSimpleIni* _ini;

		ConfigurationFile( const ConfigurationFile & copy ) { };
		ConfigurationFile & operator = ( const ConfigurationFile & copy ) { return *this; };

	};
};

#endif
