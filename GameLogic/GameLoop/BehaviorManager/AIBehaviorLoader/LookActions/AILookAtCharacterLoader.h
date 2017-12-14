#ifndef AI_LOOK_AT_CHARACTER_LOADER_H
#define AI_LOOK_AT_CHARACTER_LOADER_H

#include "../AIBehaviorLoaderBase.h"

#include <EntityBehaviors/Character/AIActions/LookActions/AILookAtCharacter.h>

class AILookAtCharacterLoader : public AIBehaviorLoaderBase
{
public:
	
	virtual IBehavior<AIContext> *LoadBehavior(const liJSON_Object *object) override
	{
		const liJSON_Object *character_info = ToConstObject(object->GetVariable("Character"));
		
		const std::string &character_name = ToConstString(character_info->GetVariable("Name"))->GetValue();
		bool named = ToConstBool(character_info->GetVariable("IsNamed"))->GetValue();
		
		//std::cout << "Look at character loaded " << followed_character << ";" <<character_name << ";" << "radius" << radius << std::endl;
		
		return new AILookAtCharacter(entity_manager,character_name,named);
	}
	
	AILookAtCharacterLoader(BehaviorManager &p_behavior_manager,EntityManager &p_entity_manager)
		:AIBehaviorLoaderBase(p_behavior_manager,p_entity_manager,"AILookAtCharacter")
	{}
	
	virtual ~AILookAtCharacterLoader() override
	{}
};

#endif // AI_LOOK_AT_CHARACTER_LOADER_H
