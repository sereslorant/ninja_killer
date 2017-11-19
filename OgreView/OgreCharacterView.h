#ifndef OGRE_CHARACTER_VIEW_H
#define OGRE_CHARACTER_VIEW_H

#include <GameLogic/IGameObserver.h>

#include "OgreEntityRepository.h"

#include <OGRE/OgreEntity.h>
#include <OGRE/OgreSceneNode.h>

class OgreCharacterView : public ICharacterObserver
{
private:
	OgreEntityRepository &entity_repository;
	
	bool initialized = false;
	Ogre::Entity *character_entity = nullptr;
	Ogre::SceneNode *character_entity_node = nullptr;
	Ogre::SceneNode &entity_node;
	
	enum MovementState
	{
		STANDING,
		MOVING,
	};
	
	MovementState leg_movement_state = STANDING;
	
	void StepLeg()
	{
		float dt = 1.0/60.0;
		float anim_speed = 2.0;
		
		switch(leg_movement_state)
		{
		case MOVING:
			character_entity->getAnimationState("leg_run")->addTime(dt*anim_speed);
			break;
		case STANDING:
			character_entity->getAnimationState("leg_stand")->addTime(dt*anim_speed);
			break;
		}
	}
	
	MovementState up_movement_state = STANDING;
	bool aim_state = false;
	bool shoot_state = false;
	
	void StepUpperBody()
	{
		
		
		float dt = 1.0/60.0;
		float shoot_speed = 2.5;
		float anim_speed = 2.0;
		
		if(shoot_state)
		{
			character_entity->getAnimationState("up_shoot")->addTime(dt*shoot_speed);
		}
		else if(aim_state)
		{
			character_entity->getAnimationState("up_weapon_hold")->addTime(dt*anim_speed);
		}
		else
		{
			switch(up_movement_state)
			{
			case MOVING:
				character_entity->getAnimationState("up_run")->addTime(dt*anim_speed);
				break;
			case STANDING:
				character_entity->getAnimationState("up_stand")->addTime(dt*anim_speed);
				break;
			}
		}
		/*
		switch(upper_body_state)
		{
		case SHOOTING:
			character_entity->getAnimationState("up_shoot")->addTime(dt*shoot_speed);
			break;
		case AIMING:
			character_entity->getAnimationState("up_weapon_hold")->addTime(dt*anim_speed);
			break;
		case IDLE:
			switch(up_movement_state)
			{
			case MOVING:
				character_entity->getAnimationState("up_run")->addTime(dt*anim_speed);
				break;
			case STANDING:
				character_entity->getAnimationState("up_stand")->addTime(dt*anim_speed);
				break;
			}
			break;
		}
		*/
	}
	
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
		
		OnStanding();
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
		if(leg_movement_state == MOVING || !initialized)
		{
			character_entity->getAnimationState("leg_run")->setEnabled(false);
			
			character_entity->getAnimationState("leg_stand")->setEnabled(true);
			character_entity->getAnimationState("leg_stand")->setWeight(1);
			character_entity->getAnimationState("leg_stand")->setTimePosition(0.0);
			
			leg_movement_state = STANDING;
		}
		
		if(up_movement_state == MOVING || !initialized)
		{
			initialized = true;
			
			if(!aim_state)
			{
				character_entity->getAnimationState("up_run")->setEnabled(false);
				
				character_entity->getAnimationState("up_stand")->setEnabled(true);
				character_entity->getAnimationState("up_stand")->setWeight(1);
				character_entity->getAnimationState("up_stand")->setTimePosition(0.0);
			}
			
			up_movement_state = STANDING;
		}
	}
	
	virtual void OnMoving() override
	{
		if(leg_movement_state == STANDING || !initialized)
		{
			character_entity->getAnimationState("leg_stand")->setEnabled(false);
			
			character_entity->getAnimationState("leg_run")->setEnabled(true);
			character_entity->getAnimationState("leg_run")->setWeight(1);
			character_entity->getAnimationState("leg_run")->setTimePosition(0.0);
			
			leg_movement_state = MOVING;
		}
		
		if(up_movement_state == STANDING || !initialized)
		{
			initialized = true;
			
			if(!aim_state)
			{
				character_entity->getAnimationState("up_stand")->setEnabled(false);
				
				character_entity->getAnimationState("up_run")->setEnabled(true);
				character_entity->getAnimationState("up_run")->setWeight(1);
				character_entity->getAnimationState("up_run")->setTimePosition(0.0);
			}
			
			up_movement_state = MOVING;
		}
	}
	
	virtual void OnAiming() override
	{
		if(!aim_state || !initialized)
		{
			initialized = true;
			
			if(leg_movement_state == MOVING)
			{character_entity->getAnimationState("up_run")->setEnabled(false);}
			else
			{character_entity->getAnimationState("up_stand")->setEnabled(false);}
			
			character_entity->getAnimationState("up_weapon_hold")->setEnabled(true);
			character_entity->getAnimationState("up_weapon_hold")->setWeight(1);
			character_entity->getAnimationState("up_weapon_hold")->setTimePosition(0.0);
			
			aim_state = true;
		}
	}
	
	virtual void OnAimReleased() override
	{
		if(aim_state || !initialized)
		{
			initialized = true;
			
			character_entity->getAnimationState("up_weapon_hold")->setEnabled(false);
			
			if(up_movement_state == MOVING)
			{
				character_entity->getAnimationState("up_run")->setEnabled(true);
				character_entity->getAnimationState("up_run")->setWeight(1);
				character_entity->getAnimationState("up_run")->setTimePosition(0.0);
			}
			else
			{
				character_entity->getAnimationState("up_stand")->setEnabled(true);
				character_entity->getAnimationState("up_stand")->setWeight(1);
				character_entity->getAnimationState("up_stand")->setTimePosition(0.0);
			}
			
			aim_state = false;
		}
	}
	
	virtual void OnShooting() override
	{
		if(!shoot_state || !initialized)
		{
			initialized = true;
			
			if(aim_state)
			{
				character_entity->getAnimationState("up_weapon_hold")->setEnabled(false);
			}
			else
			{
				if(up_movement_state == MOVING)
				{
					character_entity->getAnimationState("up_run")->setEnabled(false);
				}
				else
				{
					character_entity->getAnimationState("up_stand")->setEnabled(false);
				}
			}
			
			character_entity->getAnimationState("up_shoot")->setEnabled(true);
			character_entity->getAnimationState("up_shoot")->setWeight(1);
			character_entity->getAnimationState("up_shoot")->setTimePosition(0.0);
			
			shoot_state = true;
		}
	}
	
	virtual void OnShootingReleased() override
	{
		if(shoot_state || !initialized)
		{
			initialized = true;
			
			character_entity->getAnimationState("up_shoot")->setEnabled(false);
			
			if(aim_state)
			{
				character_entity->getAnimationState("up_weapon_hold")->setEnabled(true);
				character_entity->getAnimationState("up_weapon_hold")->setWeight(1);
				character_entity->getAnimationState("up_weapon_hold")->setTimePosition(0.0);
			}
			else
			{
				if(up_movement_state == MOVING)
				{
					character_entity->getAnimationState("up_run")->setEnabled(true);
					character_entity->getAnimationState("up_run")->setWeight(1);
					character_entity->getAnimationState("up_run")->setTimePosition(0.0);
				}
				else
				{
					character_entity->getAnimationState("up_stand")->setEnabled(true);
					character_entity->getAnimationState("up_stand")->setWeight(1);
					character_entity->getAnimationState("up_stand")->setTimePosition(0.0);
				}
			}
			
			shoot_state = false;
		}
	}
	
	void Update()
	{
		StepLeg();
		StepUpperBody();
	}
	
	OgreCharacterView(OgreEntityRepository &p_entity_repository,Ogre::SceneNode &p_entity_node)
		:entity_repository(p_entity_repository),entity_node(p_entity_node)
	{
		//OnStanding();
	}
	
	virtual ~OgreCharacterView() override
	{}
};

#endif // OGRE_CHARACTER_VIEW_H
