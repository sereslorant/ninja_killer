#ifndef BULLET_BODY_BUILDER_H
#define BULLET_BODY_BUILDER_H

#include <Physics/BulletWorldWrapper.h>

class BulletBodyBuilder;

class BulletShapeBuilder
{
private:
	bool built = false;
	
protected:
	
	btTransform transform;
	
	virtual bool CanBuild() = 0;
	
	virtual btCollisionShape *Instantiate() = 0;
	
public:
	
	class Wrapper
	{
	private:
		std::unique_ptr<BulletShapeBuilder> shape_builder;
		
	public:
		
		const btTransform &GetTransform()
		{
			return shape_builder->GetTransform();
		}
		
		btCollisionShape *Instantiate()
		{
			if(shape_builder != nullptr && shape_builder->built)
				{return shape_builder->Instantiate();}
			
			return nullptr;
		}
		
		Wrapper()
		{}
		
		Wrapper(BulletShapeBuilder *p_shape_builder)
			:shape_builder(p_shape_builder)
		{}
	};
	
	const btTransform &GetTransform()
	{
		return transform;
	}
	
	void Build()
	{
		built = CanBuild();
	}
	
	BulletShapeBuilder()
	{
		transform.setIdentity();
	}
	
	virtual ~BulletShapeBuilder()
	{}
};

class BulletSphereBuilder : public BulletShapeBuilder
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
	
	BulletSphereBuilder &SetRadius(btScalar new_radius)
	{
		radius = new_radius;
		
		return *this;
	}
	
	BulletSphereBuilder &SetPosition(const btVector3 &new_position)
	{
		transform.setOrigin(new_position);
		
		return *this;
	}
	
	BulletSphereBuilder()
	{}
	
	virtual ~BulletSphereBuilder()
	{}
};

class BulletBoxBuilder : public BulletShapeBuilder
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
	
	BulletBoxBuilder &SetHalfExtents(const btVector3 &new_half_extents)
	{
		half_extents = new_half_extents;
		
		return *this;
	}
	
	BulletBoxBuilder &SetPosition(const btVector3 &new_position)
	{
		transform.setOrigin(new_position);
		
		return *this;
	}
	
	BulletBoxBuilder()
	{}
	
	virtual ~BulletBoxBuilder()
	{}
};


class BulletCompoundBuilder;

class IBulletShapeBuilderFactory
{
public:
	virtual BulletSphereBuilder &CreateSphere() = 0;
	virtual BulletBoxBuilder &CreateBox() = 0;
	virtual BulletCompoundBuilder &CreateCompound() = 0;
	
	IBulletShapeBuilderFactory()
	{}
	virtual ~IBulletShapeBuilderFactory()
	{}
};

class BulletCompoundBuilder : public BulletShapeBuilder, public IBulletShapeBuilderFactory
{
private:
	std::list<BulletShapeBuilder::Wrapper> children;
	
protected:
	
	virtual bool CanBuild() override
	{
		return true;
	}
	
	virtual btCollisionShape *Instantiate() override
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
	
public:
	
	BulletCompoundBuilder &SetPosition(const btVector3 &new_position)
	{
		transform.setOrigin(new_position);
		
		return *this;
	}
	
	virtual BulletSphereBuilder &CreateSphere() override
	{
		BulletSphereBuilder *new_builder = new BulletSphereBuilder;
		children.emplace_back(new_builder);
		
		return *new_builder;
	}
	
	virtual BulletBoxBuilder &CreateBox() override
	{
		BulletBoxBuilder *new_builder = new BulletBoxBuilder;
		children.emplace_back(new_builder);
		
		return *new_builder;
	}
	
	virtual BulletCompoundBuilder &CreateCompound() override
	{
		BulletCompoundBuilder *new_builder = new BulletCompoundBuilder;
		children.emplace_back(new_builder);
		
		return *new_builder;
	}
	
	BulletCompoundBuilder()
	{}
	
	virtual ~BulletCompoundBuilder()
	{}
};

class BulletBodyBuilder : public IBulletShapeBuilderFactory
{
private:
	BulletWorldWrapper &world;
	BulletShapeBuilder::Wrapper shape_builder;
	
	btTransform transform;
	btScalar mass = 0.0;
	
	btVector3 velocity = {0.0,0.0,0.0};
	
	btVector3 angular_factor = {1.0,1.0,1.0};
	
public:
	
	BulletBodyBuilder &SetPosition(const btVector3 &new_position)
	{
		transform.setOrigin(new_position);
		
		return *this;
	}
	
	BulletBodyBuilder &SetOrientation(const btQuaternion &new_orientation)
	{
		transform.setRotation(new_orientation);
		
		return *this;
	}
	
	BulletBodyBuilder &SetMass(btScalar new_mass)
	{
		mass = new_mass;
		
		return *this;
	}
	
	BulletBodyBuilder &SetVelocity(const btVector3 &new_velocity)
	{
		velocity = new_velocity;
		
		return *this;
	}
	
	BulletBodyBuilder &SetAngularFactor(const btVector3 &new_angular_factor)
	{
		angular_factor = new_angular_factor;
		
		return *this;
	}
	
	virtual BulletSphereBuilder &CreateSphere() override
	{
		BulletSphereBuilder *new_builder = new BulletSphereBuilder;
		shape_builder = BulletShapeBuilder::Wrapper(new_builder);
		
		return *new_builder;
	}
	
	virtual BulletBoxBuilder &CreateBox() override
	{
		BulletBoxBuilder *new_builder = new BulletBoxBuilder;
		shape_builder = BulletShapeBuilder::Wrapper(new_builder);
		
		return *new_builder;
	}
	
	virtual BulletCompoundBuilder &CreateCompound() override
	{
		BulletCompoundBuilder *new_builder = new BulletCompoundBuilder;
		shape_builder = BulletShapeBuilder::Wrapper(new_builder);
		
		return *new_builder;
	}
	
	btRigidBody *Build()
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
	
	BulletBodyBuilder(BulletWorldWrapper &p_world)
		:world(p_world)
	{
		transform.setIdentity();
	}
	
	virtual ~BulletBodyBuilder()
	{}
};

#endif // BULLET_BODY_BUILDER_H

