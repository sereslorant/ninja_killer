#ifndef BULLET_LOADER_UTIL_H
#define BULLET_LOADER_UTIL_H

#include <lJSON/lJSON_Util.h>

#include <Physics/PhysBuilder/PhysBodyBuilder.h>

class BulletLoaderUtil
{
public:
	
	static btVector3 LoadVector(const liJSON_Array *array);
	
	static btQuaternion LoadQuaternion(const liJSON_Object *object);
	
	static void LoadShape(IPhysShapeBuilderFactory &builder_factory,const liJSON_Object *object);
	
};

#endif // BULLET_LOADER_UTIL_H
