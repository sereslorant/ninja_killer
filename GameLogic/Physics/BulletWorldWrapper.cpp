
#include "BulletWorldWrapper.h"

#include <Entities/ICollisionCallback.h>

#include <iostream>

bool GlobalCollisionCallback(btManifoldPoint& cp, void* body0, void* body1)
{
	btRigidBody *rigidbody0 = (btRigidBody*)body0;
	btRigidBody *rigidbody1 = (btRigidBody*)body1;
	
	ICollisionCallback *body0_callback = (ICollisionCallback *)rigidbody0->getUserPointer();
	ICollisionCallback *body1_callback = (ICollisionCallback *)rigidbody1->getUserPointer();
	
	if(body0_callback != nullptr)
	{
		body0_callback->AcceptCollision(body1_callback);
	}
	
	if(body1_callback != nullptr)
	{
		body1_callback->AcceptCollision(body0_callback);
	}
	
	return true;
}

BulletWorldWrapper::BulletWorldWrapper(const btVector3 &gravity)
{
	collision_configuration.reset(new btDefaultCollisionConfiguration);
	dispatcher.reset(new btCollisionDispatcher(collision_configuration.get()));
	broadphase_interface.reset(new btDbvtBroadphase);
	constraint_solver.reset(new btSequentialImpulseConstraintSolver);
	
	dynamics_world.reset(new btDiscreteDynamicsWorld(dispatcher.get(),broadphase_interface.get(),constraint_solver.get(),collision_configuration.get()));
	dynamics_world->setGravity(gravity);
	
	gContactProcessedCallback = GlobalCollisionCallback;
}
