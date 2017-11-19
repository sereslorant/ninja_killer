#ifndef BULLET_WORLD_H
#define BULLET_WORLD_H

#include <btBulletDynamicsCommon.h>

#include <memory>

#include <list>

class BulletWorldWrapper
{
private:
	
	class RigidBodyDeleter
	{
	private:
		btDynamicsWorld &dynamics_world;
		
	public:
		
		void operator() (btRigidBody *rigid_body)
		{
			dynamics_world.removeRigidBody(rigid_body);
			
			delete rigid_body->getCollisionShape();
			delete rigid_body->getMotionState();
		}
		
		RigidBodyDeleter(btDynamicsWorld &p_dynamics_world)
			:dynamics_world(p_dynamics_world)
		{}
	};
	
	std::unique_ptr<btDispatcher>				dispatcher;
	std::unique_ptr<btBroadphaseInterface>		broadphase_interface;
	std::unique_ptr<btConstraintSolver>			constraint_solver;
	std::unique_ptr<btCollisionConfiguration>	collision_configuration;
	
	std::unique_ptr<btDynamicsWorld>			dynamics_world;
	
	std::list<std::unique_ptr<btRigidBody,RigidBodyDeleter> > rigid_bodies;
	
public:
	
	btRigidBody *createBody(btRigidBody::btRigidBodyConstructionInfo &construction_info)
	{
		btRigidBody *rigid_body = new btRigidBody(construction_info);
		dynamics_world->addRigidBody(rigid_body);
		
		rigid_bodies.emplace_back(rigid_body,RigidBodyDeleter(*dynamics_world));
		
		return rigid_body;
	}
	
	void stepSimulation(btScalar dt)
	{
		dynamics_world->stepSimulation(dt);
	}
	
	BulletWorldWrapper(const btVector3 &gravity = btVector3(0.0,-10.0,0.0));
	
	~BulletWorldWrapper()
	{}
	/*
	 * End of class
	 */
};

#endif // BULLET_WORLD_H
