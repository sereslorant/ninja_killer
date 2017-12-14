#ifndef AI_AIM_LOADER_H
#define AI_AIM_LOADER_H

#include "../AIBehaviorLoaderBase.h"

#include <EntityBehaviors/Character/AIActions/WeaponActions/AIAim.h>

class AIAimLoader : public AIBehaviorLoaderBase
{
public:
	
	virtual IBehavior<AIContext> *LoadBehavior(const liJSON_Object *object) override
	{
		return new AIAim;
	}
	
	AIAimLoader(BehaviorManager &p_behavior_manager,EntityManager &p_entity_manager)
		:AIBehaviorLoaderBase(p_behavior_manager,p_entity_manager,"AIAim")
	{}
	
	virtual ~AIAimLoader() override
	{}
};

#endif // AI_AIM_LOADER_H
