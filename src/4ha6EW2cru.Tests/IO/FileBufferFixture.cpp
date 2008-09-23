#include "FileBufferFixture.h"

#include "IO/FileBuffer.hpp"

#include "../Suites.h"
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( FileBufferFixture, Suites::IOSuite( ) );

void FileBufferFixture::Should_Contain_Given_Values( )
{
	FileBuffer* fileBuffer = new FileBuffer( );

	char* fileBytes = new char[ 1 ];
	std::string filePath = "path";
	int fileSize = 99;

	fileBuffer->fileBytes = fileBytes;
	fileBuffer->filePath = filePath;
	fileBuffer->fileSize = fileSize;

	CPPUNIT_ASSERT( fileBytes == fileBuffer->fileBytes );
	CPPUNIT_ASSERT( filePath == fileBuffer->filePath );
	CPPUNIT_ASSERT( fileSize == fileBuffer->fileSize );

	delete fileBuffer;
}
