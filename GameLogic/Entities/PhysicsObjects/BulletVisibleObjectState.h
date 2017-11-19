#ifndef BULLET_VISIBLE_OBJECT_STATE_H
#define BULLET_VISIBLE_OBJECT_STATE_H

#include <Entities/VisibleObjects/VisibleObject.h>

#include <btBulletDynamicsCommon.h>

class BulletVisibleObjectState : public IVisibleObjectState
{
private:
	btRigidBody *wrapped_body;
	btQuaternion tmpOrientation;
	
public:
	
	virtual const btVector3 &GetPosition() override
	{
		return wrapped_body->getCenterOfMassPosition();
	}
	
	virtual const btQuaternion &GetOrientation() override
	{
		tmpOrientation = wrapped_body->getOrientation();
		return tmpOrientation;
	}
	
	BulletVisibleObjectState(btRigidBody *p_wrapped_body)
		:wrapped_body(p_wrapped_body)
	{}
	
	virtual ~BulletVisibleObjectState() override
	{}
};

#endif // BULLET_VISIBLE_OBJECT_STATE_H
