#ifndef AI_CONTEXT_H
#define AI_CONTEXT_H

#include <Entities/VisibleObjects/Character.h>

#include "AIMovementController.h"
#include "AILookController.h"
#include "AIWeaponController.h"

#include <map>

class AIContext
{
private:
	std::list<unsigned int> &behavior_path;
	const std::map<std::string,Character *> &labeled_characters;
	
public:
	
	Character &self;
	AIMovementController &movement_controller;
	AILookController &look_controller;
	AIWeaponController &weapon_controller;
	
	std::list<unsigned int> &GetBehaviorPath()
	{
		return behavior_path;
	}
	
	Character *GetLabeledCharacter(const std::string &character_label)
	{
		Character *labeled_character = nullptr;
		
		auto I = labeled_characters.find(character_label);
		if(I != labeled_characters.end())
		{
			return I->second;
		}
		
		return labeled_character;
	}
	
	AIContext(std::list<unsigned int> &p_behavior_path,const std::map<std::string,Character *> &p_labeled_characters,Character &p_self,AIMovementController &p_movement_controller,AILookController &p_look_controller,AIWeaponController &p_weapon_controller)
		:behavior_path(p_behavior_path),labeled_characters(p_labeled_characters),self(p_self),movement_controller(p_movement_controller),look_controller(p_look_controller),weapon_controller(p_weapon_controller)
	{}
};

#endif // AI_CONTEXT_H
