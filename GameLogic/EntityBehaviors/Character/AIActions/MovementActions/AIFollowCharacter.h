#ifndef AI_FOLLOW_BEHAVIOR_H
#define AI_FOLLOW_BEHAVIOR_H

#include <EntityBehaviors/Camera/CharacterTracking/PointAroundCharacter.h>

#include "AIGoto.h"

class AIFollowCharacter : public IBehavior<AIContext>
{
private:
	EntityManager &entity_manager;
	std::string character_name;
	bool is_named;
	float radius;
	
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
			AIGoto goto_behavior(followed_character_point,radius);
			
			return goto_behavior.Run(context);
		}
		
		return FAILED;
	}
	
	AIFollowCharacter(EntityManager &p_entity_manager,const std::string &p_character_name,bool p_is_named,float p_radius)
		:entity_manager(p_entity_manager),
		 character_name(p_character_name),
		 is_named(p_is_named),
		 radius(p_radius)
	{}
	
	virtual ~AIFollowCharacter() override
	{}
};

#endif // 
