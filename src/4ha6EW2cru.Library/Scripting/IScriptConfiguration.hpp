#ifndef __ISCRIPTCONFIGURATION_H
#define __ISCRIPTCONFIGURATION_H

class IScriptConfiguration
{

public:

	virtual bool IsFullScreen( ) const  = 0;
	virtual void SetFullScreen( bool isFullScreen ) = 0;

	virtual int GetDisplayWidth ( ) const = 0;
	virtual void SetDisplayWidth( int width )  = 0;

	virtual int GetDisplayHeight ( ) const = 0;
	virtual void SetDisplayHeight( int height ) = 0;

	virtual int GetColorDepth( ) const = 0;

	//virtual const VideoModeList& GetAvailableVideoModes( ) const = 0;
	//virtual void SetAvailableVideoModes( VideoModeList modes ) = 0;
};

#endif