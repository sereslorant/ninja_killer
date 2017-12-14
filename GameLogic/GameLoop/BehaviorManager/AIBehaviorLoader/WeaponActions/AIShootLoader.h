#ifndef AI_SHOOT_LOADER_H
#define AI_SHOOT_LOADER_H

#include "../AIBehaviorLoaderBase.h"

#include <EntityBehaviors/Character/AIActions/WeaponActions/AIShoot.h>

class AIShootLoader : public AIBehaviorLoaderBase
{
public:
	
	virtual IBehavior<AIContext> *LoadBehavior(const liJSON_Object *object) override
	{
		return new AIShoot;
	}
	
	AIShootLoader(BehaviorManager &p_behavior_manager,EntityManager &p_entity_manager)
		:AIBehaviorLoaderBase(p_behavior_manager,p_entity_manager,"AIShoot")
	{}
	
	virtual ~AIShootLoader() override
	{}
};

#endif // AI_SHOOT_LOADER_H
