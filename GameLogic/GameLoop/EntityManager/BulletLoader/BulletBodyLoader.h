#ifndef BULLET_BODY_LOADER_H
#define BULLET_BODY_LOADER_H

#include "BulletLoaderUtil.h"

#include "BulletBoxLoader.h"
#include "BulletSphereLoader.h"
#include "BulletCompoundLoader.h"

#include <Physics/BulletBuilder/BulletBodyBuilder.h>

class BulletBodyLoader
{
private:
	BulletBodyBuilder &body_builder;
	
public:
	
	void SetPosition(const btVector3 &new_position)
	{
		body_builder.SetPosition(new_position);
	}
	
	void SetOrientation(const btQuaternion &new_orientation)
	{
		
	}
	
	void Load(const liJSON_Object *object)
	{
		object->Forall([this](const std::string &key,const liJSON_Value *value)
			{
				if(key == "shape")
				{
					BulletLoaderUtil::LoadShape(body_builder,ToConstObject(value));
				}
				if(key == "position")
				{
					body_builder.SetPosition(BulletLoaderUtil::LoadVector(ToConstArray(value)));
				}
				if(key == "angular_factor")
				{
					body_builder.SetAngularFactor(BulletLoaderUtil::LoadVector(ToConstArray(value)));
				}
				if(key == "mass")
				{
					body_builder.SetMass(lJSON_Util::FloatFromJSON(value));
				}
			}
		);
	}
	
	btRigidBody *Build()
	{
		return body_builder.Build();
	}
	
	BulletBodyLoader(BulletBodyBuilder &p_body_builder)
		:body_builder(p_body_builder)
	{}
};

#endif // BULLET_BODY_LOADER_H
