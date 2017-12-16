#ifndef BULLET_SPHERE_BUILDER_H
#define BULLET_SPHERE_BUILDER_H

#include "PhysShapeBuilder.h"

class PhysSphereBuilder : public PhysShapeBuilder
{
private:
	btScalar radius = 0.0;
	
protected:
	
	virtual bool CanBuild() override
	{
		return true;
	}
	
	virtual btCollisionShape *Instantiate() override
	{
		return new btSphereShape(radius);
	}
	
public:
	
	PhysSphereBuilder &SetRadius(btScalar new_radius)
	{
		radius = new_radius;
		
		return *this;
	}
	
	PhysSphereBuilder &SetPosition(const btVector3 &new_position)
	{
		transform.setOrigin(new_position);
		
		return *this;
	}
	
	PhysSphereBuilder()
	{}
	
	virtual ~PhysSphereBuilder()
	{}
};

#endif // BULLET_SPHERE_BUILDER_H
