#ifndef IPOINT_OF_INTEREST_H
#define IPOINT_OF_INTEREST_H

#include <LinearMath/btVector3.h>

class IPointOfInterest
{
public:
	virtual btVector3 GetPosition() = 0;
	
	IPointOfInterest()
	{}
	
	virtual ~IPointOfInterest()
	{}
};

#endif // IPOINT_OF_INTEREST_H
