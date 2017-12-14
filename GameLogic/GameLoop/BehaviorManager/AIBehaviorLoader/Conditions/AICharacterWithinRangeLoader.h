#ifndef AI_CHARACTER_WITHIN_RANGE_LOADER_H
#define AI_CHARACTER_WITHIN_RANGE_LOADER_H

#include "../AIBehaviorLoaderBase.h"

#include <EntityBehaviors/Character/AIConditions/AICharacterWithinRange.h>

class AICharacterWithinRangeLoader : public AIBehaviorLoaderBase
{
public:
	
	virtual IBehavior<AIContext> *LoadBehavior(const liJSON_Object *object) override
	{
		const liJSON_Object *character_info = ToConstObject(object->GetVariable("Character"));
		
		const std::string &character_name = ToConstString(character_info->GetVariable("Name"))->GetValue();
		bool named = ToConstBool(character_info->GetVariable("IsNamed"))->GetValue();
		float radius = lJSON_Util::FloatFromJSON(object->GetVariable("Radius"));
		
		//std::cout << "Character within range loaded " << character_name << ";" << "radius" << radius << std::endl;
		
		return new AICharacterWithinRange(entity_manager,character_name,named,radius);
	}
	
	AICharacterWithinRangeLoader(BehaviorManager &p_behavior_manager,EntityManager &p_entity_manager)
		:AIBehaviorLoaderBase(p_behavior_manager,p_entity_manager,"AICharacterWithinRange")
	{}
	
	virtual ~AICharacterWithinRangeLoader() override
	{}
};

#endif // AI_CHARACTER_WITHIN_RANGE_LOADER_H
