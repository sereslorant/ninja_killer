
#include <fstream>

#include "OgreEntityRepository.h"

#include <lJSON/lJSON_Util.h>
#include <lJSON/lJSON_TypeRetriever.h>



Ogre::Vector3 VectorFromJSON(const liJSON_Array *array)
{
	float values[3] = {0.0,0.0,0.0};
	
	for(int i=0;i < std::min<int>(array->Size(),3);i++)
	{
		values[i] = lJSON_Util::FloatFromJSON(array->GetElement(i));
	}
	
	return Ogre::Vector3(values);
}

Ogre::Quaternion QuaternionFromJSON(const liJSON_Object *object)
{
	float angle = lJSON_Util::FloatFromJSON(object->GetVariable("Angle"));
	Ogre::Vector3 axis = VectorFromJSON(ToConstArray(object->GetVariable("Axis")));
	
	return Ogre::Quaternion(Ogre::Radian(angle),axis);
}

OgreEntityRepository::OgreEntityRepository(Ogre::SceneManager &p_scene_manager,const std::string &filename)
		:scene_manager(p_scene_manager)
{
	std::ifstream fin(filename.c_str());
	
	if(fin.is_open())
	{
		liJSON_Value *value;
		lJSON_Util::Parse(fin,value);
		
		const liJSON_Object *root = ToConstObject(value);
		if(root != nullptr)
		{
			root->Forall([this](const std::string &key,const liJSON_Value *value)
				{
					std::cout << key << std::endl;
					const liJSON_Object *mesh = ToConstObject(value);
					
					Ogre::Vector3 displacement = VectorFromJSON(ToConstArray(mesh->GetVariable("Displacement")));
					Ogre::Vector3 scale = VectorFromJSON(ToConstArray(mesh->GetVariable("Scale")));
					Ogre::Quaternion orientation = QuaternionFromJSON(ToConstObject(mesh->GetVariable("Orientation")));
					
					const std::string &mesh_name = ToConstString(mesh->GetVariable("MeshName"))->GetValue();
					
					mesh_records.insert({key,MeshRecord(displacement,scale,orientation,mesh_name)});
				}
			);
		}
		
		delete value;
	}
}
