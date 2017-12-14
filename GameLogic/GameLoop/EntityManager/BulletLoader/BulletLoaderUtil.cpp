
#include "BulletLoaderUtil.h"

#include "BulletBoxLoader.h"
#include "BulletSphereLoader.h"
#include "BulletCompoundLoader.h"

btVector3 BulletLoaderUtil::LoadVector(const liJSON_Array *array)
{
	float values[3] = {0.0,0.0,0.0};
	
	for(int i=0;i < std::min<int>(array->Size(),3);i++)
	{
		values[i] = lJSON_Util::FloatFromJSON(array->GetElement(i));
	}
	
	return btVector3(values[0],values[1],values[2]);
}

btQuaternion BulletLoaderUtil::LoadQuaternion(const liJSON_Object *object)
{
	float angle = lJSON_Util::FloatFromJSON(object->GetVariable("angle"));
	btVector3 axis = LoadVector(ToConstArray(object->GetVariable("axis")));
	
	return btQuaternion(axis,angle);
}

void BulletLoaderUtil::LoadShape(IBulletShapeBuilderFactory &builder_factory,const liJSON_Object *object)
{
	std::string type = ToConstString(object->GetVariable("type"))->GetValue();
	
	if(type == "box")
	{
		BulletBoxLoader box_loader(builder_factory.CreateBox());
		box_loader.Load(object);
	}
	if(type == "sphere")
	{
		BulletSphereLoader sphere_loader(builder_factory.CreateSphere());
		sphere_loader.Load(object);
	}
	if(type == "compound")
	{
		BulletCompoundLoader compound_loader(builder_factory.CreateCompound());
		compound_loader.Load(object);
	}
}
