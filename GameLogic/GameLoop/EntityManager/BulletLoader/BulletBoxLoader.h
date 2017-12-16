#ifndef BULLET_BOX_LOADER_H
#define BULLET_BOX_LOADER_H

#include <Physics/PhysBuilder/PhysBoxBuilder.h>

#include "BulletLoaderUtil.h"

class BulletBoxLoader
{
private:
	PhysBoxBuilder &box_builder;
	
public:
	
	void Load(const liJSON_Object *object)
	{
		object->Forall([this](const std::string &key,const liJSON_Value *value)
			{
				if(key == "translate")
				{
					box_builder.SetPosition(BulletLoaderUtil::LoadVector(ToConstArray(value)));
				}
				if(key == "scale")
				{
					box_builder.SetHalfExtents(0.5*BulletLoaderUtil::LoadVector(ToConstArray(value)));
				}
			}
		);
		
		box_builder.Build();
	}
	
	BulletBoxLoader(PhysBoxBuilder &p_box_builder)
		:box_builder(p_box_builder)
	{}
};

#endif // BULLET_BOX_LOADER_H
