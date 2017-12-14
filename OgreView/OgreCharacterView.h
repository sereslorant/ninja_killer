#ifndef OGRE_CHARACTER_VIEW_H
#define OGRE_CHARACTER_VIEW_H

#include <GameLogic/IGameObserver.h>

#include "OgreEntityRepository.h"

#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneNode.h>



#include "OgreAnimation/CharacterAnimator.h"

#include "AnimationState/CompositeAnimationState.h"
#include "AnimationState/PrimitiveAnimationState.h"

class OgreCharacterView : public ICharacterObserver
{
private:
	OgreEntityRepository &entity_repository;
	
	bool initialized = false;
	Ogre::Entity *character_entity = nullptr;
	Ogre::SceneNode *character_entity_node = nullptr;
	Ogre::SceneNode &entity_node;
	
	CharacterAnimator leg_animator;
	
	std::list<std::unique_ptr<IAnimationState> > leg_children;
	IAnimationState *leg_root;
	
	CharacterAnimator up_animator;
	
	std::list<std::unique_ptr<IAnimationState> > up_children;
	IAnimationState *up_root;
	
public:
	
	virtual void OnLabelChanged(const std::string &name) override
	{
		initialized = false;
		
		if(character_entity != nullptr && character_entity_node != nullptr)
		{
			entity_node.removeChild(character_entity_node);
			
			entity_repository.DestroyEntity(character_entity_node,character_entity);
		}
		
		initialized = false;
		
		std::tie(character_entity_node,character_entity) = entity_repository.CreateEntity(name);
		character_entity->getSkeleton()->setBlendMode(Ogre::SkeletonAnimationBlendMode::ANIMBLEND_CUMULATIVE);
		
		entity_node.addChild(character_entity_node);
		
		leg_animator = entity_repository.GetLegAnimator(name);
		up_animator = entity_repository.GetBodyAnimator(name);
		
		leg_children.clear();
		up_children.clear();
		
		auto leg_anim_state = entity_repository.GetLegAnimState(name);
		if(leg_anim_state != nullptr)
		{
			leg_root = leg_anim_state->Clone(leg_children);
		}
		else
		{
			leg_root = nullptr;
		}
		
		auto up_anim_state = entity_repository.GetBodyAnimState(name);
		if(up_anim_state != nullptr)
		{
			up_root = up_anim_state->Clone(up_children);
		}
		else
		{
			up_root = nullptr;
		}
	}
	
	virtual void OnPositionChanged(float x,float y,float z) override
	{
		entity_node.setPosition(x,y,z);
	}
	
	virtual void OnOrientationChanged(float w,float x,float y,float z) override
	{
		entity_node.setOrientation(w,x,y,z);
	}
	
	virtual void OnStanding() override
	{
		if(leg_root != nullptr)
		{leg_root->UpdateState("OnStanding");}
		
		if(up_root != nullptr)
		{up_root->UpdateState("OnStanding");}
	}
	
	virtual void OnMoving() override
	{
		if(leg_root != nullptr)
		{leg_root->UpdateState("OnMoving");}
		
		if(up_root != nullptr)
		{up_root->UpdateState("OnMoving");}
	}
	
	virtual void OnAiming() override
	{
		if(leg_root != nullptr)
		{leg_root->UpdateState("OnAiming");}
		
		if(up_root != nullptr)
		{up_root->UpdateState("OnAiming");}
	}
	
	virtual void OnAimReleased() override
	{
		if(leg_root != nullptr)
		{leg_root->UpdateState("OnAimReleased");}
		
		if(up_root != nullptr)
		{up_root->UpdateState("OnAimReleased");}
	}
	
	virtual void OnMelee() override
	{
		if(leg_root != nullptr)
		{leg_root->UpdateState("OnMelee");}
		
		if(up_root != nullptr)
		{up_root->UpdateState("OnMelee");}
		
	}
	
	virtual void OnMeleeReleased() override
	{
		if(leg_root != nullptr)
		{leg_root->UpdateState("OnMeleeReleased");}
		
		if(up_root != nullptr)
		{up_root->UpdateState("OnMeleeReleased");}
	}
	
	virtual void OnShooting() override
	{
		if(leg_root != nullptr)
		{leg_root->UpdateState("OnShooting");}
		
		if(up_root != nullptr)
		{up_root->UpdateState("OnShooting");}
		/*
		if(leg_root != nullptr)
		{leg_root->UpdateState("OnDying");}
			
		if(up_root != nullptr)
		{up_root->UpdateState("OnDying");}
		*/
	}
	
	virtual void OnShootingReleased() override
	{
		if(leg_root != nullptr)
		{leg_root->UpdateState("OnShootingReleased");}
		
		if(up_root != nullptr)
		{up_root->UpdateState("OnShootingReleased");}
	}
	
	virtual void OnDying() override
	{
		if(leg_root != nullptr)
		{leg_root->UpdateState("OnDying");}
			
		if(up_root != nullptr)
		{up_root->UpdateState("OnDying");}
	}
	
	void Update()
	{
		if(leg_root != nullptr)
		{
			leg_animator.Visit(*leg_root,character_entity);
			leg_animator.Animate(character_entity);
		}
		
		if(up_root != nullptr)
		{
			up_animator.Visit(*up_root,character_entity);
			up_animator.Animate(character_entity);
		}
	}
	
	OgreCharacterView(OgreEntityRepository &p_entity_repository,Ogre::SceneNode &p_entity_node)
		:entity_repository(p_entity_repository),entity_node(p_entity_node)
	{}
	
	virtual ~OgreCharacterView() override
	{}
};

#endif // OGRE_CHARACTER_VIEW_H
