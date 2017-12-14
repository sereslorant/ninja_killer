#ifndef VISIBLE_OBJECT_LOADER_H
#define VISIBLE_OBJECT_LOADER_H

#include "VisibleLoader.h"

class IBodyLoader
{
public:
	
	virtual void SetPosition(const btVector3 &new_position) = 0;
	virtual void SetOrientation(const btQuaternion &new_orientation) = 0;
	
	virtual void Load(const liJSON_Object *object) = 0;
	virtual IVisibleObjectState *Build() = 0;
	
	IBodyLoader()
	{}
	virtual ~IBodyLoader()
	{}
};

#include "../BulletLoader/BulletBodyLoader.h"

#include <Entities/VisibleObjects/SimpleVisibleObjectState.h>

class SimpleBodyLoader : public IBodyLoader
{
private:
	btVector3 position = {0.0,0.0,0.0};
	btQuaternion orientation ={{0.0,1.0,0.0},0.0};
	
public:
	
	virtual void SetPosition(const btVector3 &new_position) override
	{
		position = new_position;
	}
	
	virtual void SetOrientation(const btQuaternion &new_orientation) override
	{
		orientation = new_orientation;
	}
	
	virtual void Load(const liJSON_Object *object) override
	{
		object->Forall([this](const std::string &key,const liJSON_Value *value)
			{
				if(key == "position")
				{
					SetPosition(BulletLoaderUtil::LoadVector(ToConstArray(value)));
				}
				if(key == "orientation")
				{
					SetOrientation(BulletLoaderUtil::LoadQuaternion(ToConstObject(value)));
				}
			}
		);
	}
	
	virtual IVisibleObjectState *Build() override
	{
		return new SimpleVisibleObjectState(position,orientation);
	}
	
	SimpleBodyLoader()
	{}
};

#include <Entities/PhysicsObjects/BulletVisibleObjectState.h>

class PhysBodyLoader : public IBodyLoader
{
private:
	BulletBodyBuilder &phys_body_builder;
	
public:
	
	virtual void SetPosition(const btVector3 &new_position) override
	{
		phys_body_builder.SetPosition(new_position);
	}
	
	virtual void SetOrientation(const btQuaternion &new_orientation) override
	{
		phys_body_builder.SetOrientation(new_orientation);
	}
	
	virtual void Load(const liJSON_Object *object) override
	{
		BulletBodyLoader body_loader(phys_body_builder);
		
		body_loader.Load(object);
	}
	
	virtual IVisibleObjectState *Build() override
	{
		return new BulletVisibleObjectState(phys_body_builder.Build());
	}
	
	PhysBodyLoader(BulletBodyBuilder &p_phys_body_builder)
		:phys_body_builder(p_phys_body_builder)
	{}
};

class VisibleObjectLoader
{
private:
	VisibleLoader visible_loader;
	BulletBodyBuilder phys_body_builder;
	
	std::unique_ptr<IBodyLoader> body_loader;
	
public:
	
	IBodyLoader *CreateStateLoader(const liJSON_Object *object)
	{
		std::string type = ToConstString(object->GetVariable("type"))->GetValue();
		
		if(type == "rigid_body")
		{
			return new PhysBodyLoader(phys_body_builder);
		}
		if(type == "simple")
		{
			return new SimpleBodyLoader;
		}
		
		return nullptr;
	}
	
	void SetPosition(const btVector3 &new_position)
	{
		if(body_loader != nullptr)
			{body_loader->SetPosition(new_position);}
	}
	
	void SetOrientation(const btQuaternion &new_orientation)
	{
		if(body_loader != nullptr)
			{body_loader->SetOrientation(new_orientation);}
	}
	
	virtual void Load(const liJSON_Object *object)
	{
		object->Forall([this](const std::string &key,const liJSON_Value *value)
			{
				if(key == "visible")
				{
					visible_loader.Load(ToConstObject(value));
				}
				if(key == "body")
				{
					body_loader = std::unique_ptr<IBodyLoader>(CreateStateLoader(ToConstObject(value)));
					body_loader->Load(ToConstObject(value));
				}
			}
		);
	}
	
	VisibleObject *Build()
	{
		VisibleObject *new_visible_object = nullptr;
		
		if(body_loader != nullptr)
		{
			new_visible_object = visible_loader.Build(body_loader->Build());
		}
		
		return new_visible_object;
	}
	
	VisibleObjectLoader(BulletWorldWrapper &world)
		:phys_body_builder(world)
	{}
};

#endif // VISIBLE_OBJECT_LOADER_H
