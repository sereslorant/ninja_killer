#ifndef OGRE_ENTITY_REPOSITORY_H
#define OGRE_ENTITY_REPOSITORY_H

#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>

#include <map>
#include <tuple>

class OgreEntityRepository
{
private:
	
	struct MeshRecord
	{
		Ogre::Vector3 displacement;//		= {0.0,0.0,0.0};
		Ogre::Vector3 scale;//				= {1.0,1.0,1.0};
		Ogre::Quaternion orientation;//	= {Ogre::Radian(0.0),{0.0,1.0,0.0}};
		
		std::string mesh_name;
		
		MeshRecord(const Ogre::Vector3 &p_displacement,const Ogre::Vector3 &p_scale,const Ogre::Quaternion &p_orientation,const std::string &p_mesh_name)
			:displacement(p_displacement),scale(p_scale),orientation(p_orientation),mesh_name(p_mesh_name)
		{}
	};
	
	Ogre::SceneManager &scene_manager;
	std::map<std::string,MeshRecord> mesh_records;
	
public:
	
	std::tuple<Ogre::SceneNode*,Ogre::Entity*> CreateEntity(const std::string &label)
	{
		std::tuple<Ogre::SceneNode*,Ogre::Entity*> ret_value = {nullptr,nullptr};
		
		auto I = mesh_records.find(label);
		if(I != mesh_records.end())
		{
			Ogre::Entity *new_entity = scene_manager.createEntity(I->second.mesh_name);
			Ogre::SceneNode *new_node = scene_manager.createSceneNode();
			
			new_node->setPosition(I->second.displacement);
			new_node->setOrientation(I->second.orientation);
			new_node->setScale(I->second.scale);
			
			new_node->attachObject(new_entity);
			
			ret_value = std::make_tuple(new_node,new_entity);
		}
		
		return ret_value;
	}
	
	void DestroyEntity(Ogre::SceneNode *scene_node,Ogre::Entity *entity)
	{
		scene_node->detachObject(entity);
		
		scene_manager.destroyEntity(entity);
		scene_manager.destroySceneNode(scene_node);
	}
	
	OgreEntityRepository(Ogre::SceneManager &p_scene_manager,const std::string &filename);
	
	~OgreEntityRepository()
	{}
};

#endif // OGRE_ENTITY_REPOSITORY_H
