
#include "PhysCompositeBuilder.h"


btCollisionShape *PhysCompositeBuilder::Instantiate()
{
	btCompoundShape *compound_shape = new btCompoundShape;
	
	for(auto &child : children)
	{
		btCollisionShape *child_shape = child.Instantiate();
		
		if(child_shape != nullptr)
		{
			compound_shape->addChildShape(child.GetTransform(),child_shape);
		}
	}
	
	return compound_shape;
}

PhysCompositeBuilder &PhysCompositeBuilder::SetPosition(const btVector3 &new_position)
{
	transform.setOrigin(new_position);
	
	return *this;
}

PhysSphereBuilder &PhysCompositeBuilder::CreateSphere()
{
	PhysSphereBuilder *new_builder = new PhysSphereBuilder;
	children.emplace_back(new_builder);
	
	return *new_builder;
}

PhysBoxBuilder &PhysCompositeBuilder::CreateBox()
{
	PhysBoxBuilder *new_builder = new PhysBoxBuilder;
	children.emplace_back(new_builder);
	
	return *new_builder;
}

PhysCompositeBuilder &PhysCompositeBuilder::CreateCompound()
{
	PhysCompositeBuilder *new_builder = new PhysCompositeBuilder;
	children.emplace_back(new_builder);
	
	return *new_builder;
}

PhysCompositeBuilder::PhysCompositeBuilder()
{}

PhysCompositeBuilder::~PhysCompositeBuilder()
{}
