#ifndef BULLET_BOX_BUILDER_H
#define BULLET_BOX_BUILDER_H

#include "PhysShapeBuilder.h"

class PhysBoxBuilder : public PhysShapeBuilder
{
private:
	btVector3 half_extents = {0.0,0.0,0.0};
	
protected:
	
	virtual bool CanBuild() override
	{
		return true;
	}
	
	virtual btCollisionShape *Instantiate() override
	{
		return new btBoxShape(half_extents);
	}
	
public:
	
	PhysBoxBuilder &SetHalfExtents(const btVector3 &new_half_extents)
	{
		half_extents = new_half_extents;
		
		return *this;
	}
	
	PhysBoxBuilder &SetPosition(const btVector3 &new_position)
	{
		transform.setOrigin(new_position);
		
		return *this;
	}
	
	PhysBoxBuilder()
	{}
	
	virtual ~PhysBoxBuilder()
	{}
};

#endif // BULLET_BOX_BUILDER_H
