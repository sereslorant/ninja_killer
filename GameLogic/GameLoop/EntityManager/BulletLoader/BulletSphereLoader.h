#ifndef BULLET_SPHERE_LOADER_H
#define BULLET_SPHERE_LOADER_H

#include "BulletLoaderUtil.h"

class BulletSphereLoader
{
private:
	BulletSphereBuilder &sphere_builder;
	
public:
	
	void Load(const liJSON_Object *object)
	{
		object->Forall([this](const std::string &key,const liJSON_Value *value)
			{
				if(key == "translate")
				{
					sphere_builder.SetPosition(BulletLoaderUtil::LoadVector(ToConstArray(value)));
				}
				if(key == "radius")
				{
					sphere_builder.SetRadius(lJSON_Util::FloatFromJSON(value));
				}
			}
		);
		
		sphere_builder.Build();
	}
	
	BulletSphereLoader(BulletSphereBuilder &p_sphere_builder)
		:sphere_builder(p_sphere_builder)
	{}
};

#endif // BULLET_SPHERE_LOADER_H
