
#include "BulletWorldWrapper.h"

BulletWorldWrapper::BulletWorldWrapper(const btVector3 &gravity)
{
	collision_configuration.reset(new btDefaultCollisionConfiguration);
	dispatcher.reset(new btCollisionDispatcher(collision_configuration.get()));
	broadphase_interface.reset(new btDbvtBroadphase);
	constraint_solver.reset(new btSequentialImpulseConstraintSolver);
	
	dynamics_world.reset(new btDiscreteDynamicsWorld(dispatcher.get(),broadphase_interface.get(),constraint_solver.get(),collision_configuration.get()));
	dynamics_world->setGravity(gravity);
}
