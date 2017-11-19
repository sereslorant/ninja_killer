#ifndef AI_TURN_TOWARDS_CHARACTER_LOADER_H
#define AI_TURN_TOWARDS_CHARACTER_LOADER_H

#include "AIBehaviorLoaderBase.h"

#include <EntityBehaviors/Character/AIActions/AITurnTowardsCharacter.h>

class AITurnTowardsCharacterLoader : public AIBehaviorLoaderBase
{
public:
	
	virtual IBehavior<AIContext> *LoadBehavior(const liJSON_Object *object) override
	{
		const std::string &character_name = ToConstString(object->GetVariable("Character"))->GetValue();
		
		Character *followed_character = entity_manager.GetNamedCharacter(character_name);
		float epsilon = lJSON_Util::FloatFromJSON(object->GetVariable("Epsilon"));
		
		//std::cout << "Turn towards character loaded " << followed_character << ";" <<character_name << ";" << "radius" << epsilon << std::endl;
		
		return new AITurnTowardsCharacter(*followed_character,epsilon);
	}
	
	AITurnTowardsCharacterLoader(BehaviorManager &p_behavior_manager,EntityManager &p_entity_manager)
		:AIBehaviorLoaderBase(p_behavior_manager,p_entity_manager,"AITurnTowardsCharacter")
	{}
	
	virtual ~AITurnTowardsCharacterLoader() override
	{}
};

#endif // AI_TURN_TOWARDS_CHARACTER_LOADER_H
