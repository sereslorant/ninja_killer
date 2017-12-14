#ifndef AI_FOLLOW_CHARACTER_LOADER_H
#define AI_FOLLOW_CHARACTER_LOADER_H

#include "../AIBehaviorLoaderBase.h"

#include <EntityBehaviors/Character/AIActions/MovementActions/AIFollowCharacter.h>

class AIFollowCharacterLoader : public AIBehaviorLoaderBase
{
public:
	
	virtual IBehavior<AIContext> *LoadBehavior(const liJSON_Object *object) override
	{
		const liJSON_Object *character_info = ToConstObject(object->GetVariable("Character"));
		
		const std::string &character_name = ToConstString(character_info->GetVariable("Name"))->GetValue();
		bool named = ToConstBool(character_info->GetVariable("IsNamed"))->GetValue();
		float radius = lJSON_Util::FloatFromJSON(object->GetVariable("Radius"));
		
		//std::cout << "Follow character loaded " << followed_character << ";" <<character_name << ";" << "radius" << radius << std::endl;
		
		return new AIFollowCharacter(entity_manager,character_name,named,radius);
	}
	
	AIFollowCharacterLoader(BehaviorManager &p_behavior_manager,EntityManager &p_entity_manager)
		:AIBehaviorLoaderBase(p_behavior_manager,p_entity_manager,"AIFollowCharacter")
	{}
	
	virtual ~AIFollowCharacterLoader() override
	{}
};

#endif // AI_FOLLOW_CHARACTER_LOADER_H
