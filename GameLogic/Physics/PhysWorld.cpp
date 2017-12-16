
#include "PhysWorld.h"

#include <Entities/ICollisionCallback.h>

bool GlobalCollisionCallback(btManifoldPoint& cp,const btCollisionObjectWrapper* colObj0Wrap,int partId0,int index0,const btCollisionObjectWrapper* colObj1Wrap,int partId1,int index1)
{
	ICollisionCallback *body0_callback = (ICollisionCallback *)colObj0Wrap->getCollisionObject()->getUserPointer();
	ICollisionCallback *body1_callback = (ICollisionCallback *)colObj1Wrap->getCollisionObject()->getUserPointer();
	
	if(body0_callback != nullptr)
	{
		body0_callback->AcceptCollision(body1_callback);
	}
	
	if(body1_callback != nullptr)
	{
		body1_callback->AcceptCollision(body0_callback);
	}
	
	return false;
}

PhysWorld::PhysWorld(const btVector3 &gravity)
{
	collision_configuration.reset(new btDefaultCollisionConfiguration);
	dispatcher.reset(new btCollisionDispatcher(collision_configuration.get()));
	broadphase_interface.reset(new btDbvtBroadphase);
	constraint_solver.reset(new btSequentialImpulseConstraintSolver);
	
	dynamics_world.reset(new btDiscreteDynamicsWorld(dispatcher.get(),broadphase_interface.get(),constraint_solver.get(),collision_configuration.get()));
	dynamics_world->setGravity(gravity);
	
	//gContactProcessedCallback = GlobalCollisionCallback;
	gContactAddedCallback = GlobalCollisionCallback;
}
