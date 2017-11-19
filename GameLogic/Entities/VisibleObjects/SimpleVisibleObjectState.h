#ifndef SIMPLE_VISIBLE_OBJECT_STATE_H
#define SIMPLE_VISIBLE_OBJECT_STATE_H

#include "VisibleObject.h"

class SimpleVisibleObjectState : public IVisibleObjectState
{
private:
	btVector3		position	= btVector3(0.0,0.0,0.0);
	btQuaternion	orientation	= btQuaternion({0.0,1.0,0.0},0.0);
	
public:
	
	virtual const btVector3 &GetPosition() override
	{
		return position;
	}
	
	virtual const btQuaternion &GetOrientation() override
	{
		return orientation;
	}
	
	SimpleVisibleObjectState()
	{}
	
	SimpleVisibleObjectState(const btVector3 &p_position,const btQuaternion &p_orientation)
		:position(p_position),orientation(p_orientation)
	{}
	
	virtual ~SimpleVisibleObjectState() override
	{}
};

#endif // SIMPLE_VISIBLE_OBJECT_STATE_H
