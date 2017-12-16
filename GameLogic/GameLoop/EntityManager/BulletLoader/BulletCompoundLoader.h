#ifndef BULLET_COMPOUND_LOADER_H
#define BULLET_COMPOUND_LOADER_H

#include <Physics/PhysBuilder/PhysCompositeBuilder.h>

#include "BulletLoaderUtil.h"

class BulletCompoundLoader
{
private:
	PhysCompositeBuilder &compound_builder;
	
public:
	
	void Load(const liJSON_Object *object)
	{
		object->Forall([this](const std::string &key,const liJSON_Value *value)
			{
				if(key == "children")
				{
					const liJSON_Array *children = ToConstArray(value);
					for(int i=0;i < children->Size();i++)
					{
						const liJSON_Object *child = ToConstObject(children->GetElement(i));
						BulletLoaderUtil::LoadShape(compound_builder,ToConstObject(children->GetElement(i)));
					}
				}
				if(key == "translate")
				{
					compound_builder.SetPosition(BulletLoaderUtil::LoadVector(ToConstArray(value)));
				}
			}
		);
		compound_builder.Build();
	}
	
	BulletCompoundLoader(PhysCompositeBuilder &p_compound_builder)
		:compound_builder(p_compound_builder)
	{}
};

#endif // BULLET_COMPOUND_LOADER_H
