#ifndef BULLET_BODY_BUILDER_H
#define BULLET_BODY_BUILDER_H

#include "PhysCompositeBuilder.h"

#include <Physics/PhysWorld.h>

class PhysBodyBuilder : public IPhysShapeBuilderFactory
{
private:
	PhysWorld &world;
	PhysShapeBuilder::Wrapper shape_builder;
	
	btTransform transform;
	btScalar mass = 0.0;
	
	btVector3 velocity = {0.0,0.0,0.0};
	
	btVector3 angular_factor = {1.0,1.0,1.0};
	
public:
	
	PhysBodyBuilder &SetPosition(const btVector3 &new_position);
	
	PhysBodyBuilder &SetOrientation(const btQuaternion &new_orientation);
	
	PhysBodyBuilder &SetMass(btScalar new_mass);
	
	PhysBodyBuilder &SetVelocity(const btVector3 &new_velocity);
	
	PhysBodyBuilder &SetAngularFactor(const btVector3 &new_angular_factor);
	
	virtual PhysSphereBuilder &CreateSphere() override;
	
	virtual PhysBoxBuilder &CreateBox() override;
	
	virtual PhysCompositeBuilder &CreateCompound() override;
	
	btRigidBody *Build();
	
	PhysBodyBuilder(PhysWorld &p_world);
	
	virtual ~PhysBodyBuilder() override;
};

#endif // BULLET_BODY_BUILDER_H

