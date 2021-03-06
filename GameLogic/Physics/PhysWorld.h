#ifndef BULLET_WORLD_H
#define BULLET_WORLD_H

#include <btBulletDynamicsCommon.h>

#include <memory>

#include <list>

class PhysWorld
{
private:
	
	class RigidBodyDeleter
	{
	private:
		btDynamicsWorld &dynamics_world;
		
		void DeleteCollisionShape(btCollisionShape *collision_shape)
		{
			if(collision_shape->isCompound())
			{
				btCompoundShape *compound_shape = (btCompoundShape *)collision_shape;
				for(int i=0;i < compound_shape->getNumChildShapes();i++)
				{
					DeleteCollisionShape(compound_shape->getChildShape(i));
				}
			}
			
			delete collision_shape;
		}
		
	public:
		
		void operator() (btRigidBody *rigid_body)
		{
			dynamics_world.removeRigidBody(rigid_body);
			
			DeleteCollisionShape(rigid_body->getCollisionShape());
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
	
	btRigidBody *raytrace(const btVector3 &begin,const btVector3 &direction)
	{
		btVector3 end = begin + direction;
		btCollisionWorld::ClosestRayResultCallback result(begin, end);

		dynamics_world->rayTest(begin, end, result);

		if(result.hasHit()){
			return (btRigidBody *)result.m_collisionObject;
		}
		
		return nullptr;
	}
	
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
	
	PhysWorld(const btVector3 &gravity = btVector3(0.0,5.0*-10.0,0.0));
	
	~PhysWorld()
	{}
	/*
	 * End of class
	 */
};

#endif // BULLET_WORLD_H
