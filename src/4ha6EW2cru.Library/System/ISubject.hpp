#ifndef __ISUBJECT
#define __ISUBJECT

class ISubject
{

public:

	virtual void PushChanges( unsigned int systemChanges ) = 0;

};

#endif