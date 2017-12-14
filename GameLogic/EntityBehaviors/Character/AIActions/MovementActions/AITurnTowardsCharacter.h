#ifndef AI_TURN_TOWARDS_CHARACTE_H
#define AI_TURN_TOWARDS_CHARACTE_H

#include "AITurnTowards.h"

#include <GameLogic/EntityBehaviors/Camera/CharacterTracking/PointAroundCharacter.h>

class AITurnTowardsCharacter : public IBehavior<AIContext>
{
private:
	EntityManager &entity_manager;
	std::string character_name;
	bool is_named;
	float epsilon;
	
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
			AITurnTowards turn_towards(followed_character_point,epsilon);
			
			return turn_towards.Run(context);
		}
		
		return FAILED;
	}
	
	AITurnTowardsCharacter(EntityManager &p_entity_manager,const std::string &p_character_name,bool p_is_named,float p_epsilon)
		:entity_manager(p_entity_manager),
		 character_name(p_character_name),
		 is_named(p_is_named),
		 epsilon(p_epsilon)
	{}
	
	virtual ~AITurnTowardsCharacter() override
	{}
};

#endif // AI_TURN_TOWARDS_CHARACTE_H
