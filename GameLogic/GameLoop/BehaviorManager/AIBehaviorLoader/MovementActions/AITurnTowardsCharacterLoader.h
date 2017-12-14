#ifndef AI_TURN_TOWARDS_CHARACTER_LOADER_H
#define AI_TURN_TOWARDS_CHARACTER_LOADER_H

#include "../AIBehaviorLoaderBase.h"

#include <EntityBehaviors/Character/AIActions/MovementActions/AITurnTowardsCharacter.h>

class AITurnTowardsCharacterLoader : public AIBehaviorLoaderBase
{
public:
	
	virtual IBehavior<AIContext> *LoadBehavior(const liJSON_Object *object) override
	{
		const liJSON_Object *character_info = ToConstObject(object->GetVariable("Character"));
		
		const std::string &character_name = ToConstString(character_info->GetVariable("Name"))->GetValue();
		bool named = ToConstBool(character_info->GetVariable("IsNamed"))->GetValue();
		float epsilon = lJSON_Util::FloatFromJSON(object->GetVariable("Epsilon"));
		
		//std::cout << "Turn towards character loaded " << followed_character << ";" <<character_name << ";" << "radius" << epsilon << std::endl;
		
		return new AITurnTowardsCharacter(entity_manager,character_name,named,epsilon);
	}
	
	AITurnTowardsCharacterLoader(BehaviorManager &p_behavior_manager,EntityManager &p_entity_manager)
		:AIBehaviorLoaderBase(p_behavior_manager,p_entity_manager,"AITurnTowardsCharacter")
	{}
	
	virtual ~AITurnTowardsCharacterLoader() override
	{}
};

#endif // AI_TURN_TOWARDS_CHARACTER_LOADER_H
