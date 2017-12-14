#ifndef AI_CHARACTER_WITHIN_RANGE_H
#define AI_CHARACTER_WITHIN_RANGE_H

#include <EntityBehaviors/BehaviorTree/IBehavior.h>
#include <EntityBehaviors/Character/AIController/AIContext.h>

class AICharacterWithinRange: public IBehavior<AIContext>
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
			btVector3 dir = followed_character->GetPosition() - context.self.GetPosition();
			if(dir.length2() < radius*radius)
			{
				return SUCCEEDED;
			}
		}
		
		return FAILED;
	}
	
	AICharacterWithinRange(EntityManager &p_entity_manager,const std::string &p_character_name,bool p_is_named,float p_radius)
		:entity_manager(p_entity_manager),
		 character_name(p_character_name),
		 is_named(p_is_named),
		 radius(p_radius)
	{}
	
	virtual ~AICharacterWithinRange() override
	{}
};

#endif // AI_CHARACTER_WITHIN_RANGE_H
