
#include "PhysBodyBuilder.h"

PhysBodyBuilder &PhysBodyBuilder::SetPosition(const btVector3 &new_position)
{
	transform.setOrigin(new_position);
	
	return *this;
}

PhysBodyBuilder &PhysBodyBuilder::SetOrientation(const btQuaternion &new_orientation)
{
	transform.setRotation(new_orientation);
	
	return *this;
}

PhysBodyBuilder &PhysBodyBuilder::SetMass(btScalar new_mass)
{
	mass = new_mass;
	
	return *this;
}

PhysBodyBuilder &PhysBodyBuilder::SetVelocity(const btVector3 &new_velocity)
{
	velocity = new_velocity;
	
	return *this;
}

PhysBodyBuilder &PhysBodyBuilder::SetAngularFactor(const btVector3 &new_angular_factor)
{
	angular_factor = new_angular_factor;
	
	return *this;
}

PhysSphereBuilder &PhysBodyBuilder::CreateSphere()
{
	PhysSphereBuilder *new_builder = new PhysSphereBuilder;
	shape_builder = PhysShapeBuilder::Wrapper(new_builder);
	
	return *new_builder;
}

PhysBoxBuilder &PhysBodyBuilder::CreateBox()
{
	PhysBoxBuilder *new_builder = new PhysBoxBuilder;
	shape_builder = PhysShapeBuilder::Wrapper(new_builder);
	
	return *new_builder;
}

PhysCompositeBuilder &PhysBodyBuilder::CreateCompound()
{
	PhysCompositeBuilder *new_builder = new PhysCompositeBuilder;
	shape_builder = PhysShapeBuilder::Wrapper(new_builder);
	
	return *new_builder;
}

btRigidBody *PhysBodyBuilder::Build()
{
	btCollisionShape *collision_shape = shape_builder.Instantiate();
	if(collision_shape == nullptr)
		{return nullptr;}
	
	btMotionState *motion_state = new btDefaultMotionState(transform);
	
	btVector3 local_inertia(0.0,0.0,0.0);
	if(mass > 0.0)
	{
		collision_shape->calculateLocalInertia(mass,local_inertia);
	}
	
	btRigidBody::btRigidBodyConstructionInfo ConstructionInfo(mass,motion_state,collision_shape,local_inertia);
	btRigidBody *rigid_body = world.createBody(ConstructionInfo);
	
	rigid_body->setLinearVelocity(velocity);
	
	rigid_body->setAngularFactor(angular_factor);
	
	rigid_body->setCollisionFlags(rigid_body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	
	return rigid_body;
}

PhysBodyBuilder::PhysBodyBuilder(PhysWorld &p_world)
	:world(p_world)
{
	transform.setIdentity();
}

PhysBodyBuilder::~PhysBodyBuilder()
{}
