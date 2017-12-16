#ifndef BULLET_SHAPE_BUILDER_H
#define BULLET_SHAPE_BUILDER_H

#include <btBulletCollisionCommon.h>

#include <memory>

class PhysShapeBuilder
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
		std::unique_ptr<PhysShapeBuilder> shape_builder;
		
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
		
		Wrapper(PhysShapeBuilder *p_shape_builder)
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
	
	PhysShapeBuilder()
	{
		transform.setIdentity();
	}
	
	virtual ~PhysShapeBuilder()
	{}
};

#endif // BULLET_SHAPE_BUILDER_H
