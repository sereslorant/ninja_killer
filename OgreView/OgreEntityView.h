#ifndef OGRE_ENTITY_VIEW_H
#define OGRE_ENTITY_VIEW_H

#include <GameLogic/IGameObserver.h>

#include "OgreEntityRepository.h"

#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneNode.h>

class OgreEntityView : public IVisibleObserver
{
private:
	OgreEntityRepository &entity_repository;
	
	Ogre::Entity *current_entity = nullptr;
	Ogre::SceneNode *current_entity_node = nullptr;
	
	Ogre::SceneNode &entity_node;
	
public:
	
	virtual void OnLabelChanged(const std::string &name) override
	{
		if(current_entity != nullptr && current_entity_node != nullptr)
		{
			entity_node.removeChild(current_entity_node);
			
			entity_repository.DestroyEntity(current_entity_node,current_entity);
		}
		
		std::tie(current_entity_node,current_entity) = entity_repository.CreateEntity(name);
		
		entity_node.addChild(current_entity_node);
	}
	
	virtual void OnPositionChanged(float x,float y,float z) override
	{
		entity_node.setPosition(x,y,z);
	}
	
	virtual void OnOrientationChanged(float w,float x,float y,float z) override
	{
		entity_node.setOrientation(w,x,y,z);
	}
	
	OgreEntityView(OgreEntityRepository &p_entity_repository,Ogre::SceneNode &p_entity_node)
		:entity_repository(p_entity_repository),entity_node(p_entity_node)
	{}
	
	virtual ~OgreEntityView() override
	{}
};

#endif // OGRE_ENTITY_VIEW_H
