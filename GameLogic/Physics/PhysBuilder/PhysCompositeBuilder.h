#ifndef BULLET_COMPOUND_BUILDER_H
#define BULLET_COMPOUND_BUILDER_H

#include "PhysSphereBuilder.h"
#include "PhysBoxBuilder.h"

#include <list>

class PhysCompositeBuilder;

class IPhysShapeBuilderFactory
{
public:
	virtual PhysSphereBuilder &CreateSphere() = 0;
	virtual PhysBoxBuilder &CreateBox() = 0;
	virtual PhysCompositeBuilder &CreateCompound() = 0;
	
	IPhysShapeBuilderFactory()
	{}
	virtual ~IPhysShapeBuilderFactory()
	{}
};

class PhysCompositeBuilder : public PhysShapeBuilder, public IPhysShapeBuilderFactory
{
private:
	std::list<PhysShapeBuilder::Wrapper> children;
	
protected:
	
	virtual bool CanBuild() override
	{
		return true;
	}
	
	virtual btCollisionShape *Instantiate() override;
	
public:
	
	PhysCompositeBuilder &SetPosition(const btVector3 &new_position);
	
	virtual PhysSphereBuilder &CreateSphere() override;
	
	virtual PhysBoxBuilder &CreateBox() override;
	
	virtual PhysCompositeBuilder &CreateCompound() override;
	
	PhysCompositeBuilder();
	
	virtual ~PhysCompositeBuilder() override;
};

#endif // BULLET_COMPOUND_BUILDER_H
