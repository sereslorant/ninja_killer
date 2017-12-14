#ifndef AI_LOOK_AT_CHARACTER_H
#define AI_LOOK_AT_CHARACTER_H

#include <EntityBehaviors/Camera/CharacterTracking/PointAroundCharacter.h>

#include "AILookAt.h"

class AILookAtCharacter : public IBehavior<AIContext>
{
private:
	EntityManager &entity_manager;
	std::string character_name;
	bool is_named;
	
public:
	
	virtual BehaviorState Run(AIContext &context) override
	{
		Character *followed_character = nullptr;
		if(is_named)
		{
			followed_character = entity_manager.GetNamedCharacter(character_name);
		}
		else
		{
			followed_character = context.GetLabeledCharacter(character_name);
		}
		
		if(followed_character != nullptr)
		{
			PointAroundCharacter followed_character_point(*followed_character,0.0,0.0,0.0);
			AILookAt look_at_behavior(followed_character_point);
			
			return look_at_behavior.Run(context);
		}
		
		return FAILED;
	}
	
	AILookAtCharacter(EntityManager &p_entity_manager,const std::string &p_character_name,bool p_is_named)
		:entity_manager(p_entity_manager),
		 character_name(p_character_name),
		 is_named(p_is_named)
	{}
	
	virtual ~AILookAtCharacter() override
	{}
};

#endif // AI_LOOK_AT_CHARACTER_H
