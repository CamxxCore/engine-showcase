#include "ConfigurationFile.h"

#include "../Management/Management.h"
#include "../IO/IResource.hpp"

namespace Configuration
{
	ConfigurationFile::~ConfigurationFile()
	{
		if( _ini != 0 )
		{
			delete _ini;
		}
	}

	ConfigurationFile::ConfigurationFile( const FileBuffer* fileBuffer )
	{
		_ini = new CSimpleIni( true );
		_ini->Load( fileBuffer->fileBytes );
	}

	ConfigurationFile* ConfigurationFile::Load( const std::string& filePath )
	{
		Resources::IResource* resource = Management::GetInstance( )->GetResourceManager( )->GetResource( filePath );
		return new ConfigurationFile( resource->GetFileBuffer( ) );
	}

	AnyValue ConfigurationFile::FindConfigItem( const std::string& section, const std::string& key, const AnyValue& defaultValue )
	{
		AnyValue result;
		AnyValue& unConstDefaultValue = const_cast< AnyValue& >( defaultValue );

		if ( unConstDefaultValue.GetType( ) == typeid( bool ) )
		{
			result = _ini->GetBoolValue( section.c_str( ), key.c_str( ), unConstDefaultValue.GetValue< bool >( ) );
		}

		if ( unConstDefaultValue.GetType( ) == typeid( int ) )
		{
			result = static_cast< int >( _ini->GetLongValue( section.c_str( ), key.c_str( ), unConstDefaultValue.GetValue< int >( ) ) );
		}

		if ( unConstDefaultValue.GetType( ) == typeid( std::string ) )
		{
			result = _ini->GetValue( section.c_str( ), key.c_str( ), unConstDefaultValue.GetValue< std::string >( ).c_str( ) );
		}

		return result;
	}

	void ConfigurationFile::Update( const std::string& section, const std::string& key, const AnyValue& value )
	{
		AnyValue& unConstValue = const_cast< AnyValue& >( value );

		if ( unConstValue.GetType( ) == typeid( bool ) )
		{
			_ini->SetBoolValue( section.c_str( ), key.c_str( ), unConstValue.GetValue< bool >( ) );
		}

		if ( unConstValue.GetType( ) == typeid( int ) )
		{
			_ini->SetLongValue( section.c_str( ), key.c_str( ), unConstValue.GetValue< int >( ) );
		}

		if ( unConstValue.GetType( ) == typeid( std::string ) )
		{
			_ini->SetValue( section.c_str( ), key.c_str( ), unConstValue.GetValue< std::string >( ).c_str( ) );
		}
	}

	void ConfigurationFile::Save( const std::string& filePath )
	{
		std::string output;
		_ini->Save( output );

		char* outputBuffer = new char[ output.length( ) + 1 ];
		memcpy( outputBuffer, output.c_str( ), output.length( ) );
		outputBuffer[ output.length( ) ] = '\0';

		FileBuffer fileBuffer( outputBuffer, output.length( ), filePath );
		Management::GetInstance( )->GetFileManager( )->SaveFile( fileBuffer );
	}
}