#ifndef AI_MELEE_LOADER_H
#define AI_MELEE_LOADER_H

#include "../AIBehaviorLoaderBase.h"

#include <EntityBehaviors/Character/AIActions/WeaponActions/AIMelee.h>

class AIMeleeLoader : public AIBehaviorLoaderBase
{
public:
	
	virtual IBehavior<AIContext> *LoadBehavior(const liJSON_Object *object) override
	{
		return new AIMelee;
	}
	
	AIMeleeLoader(BehaviorManager &p_behavior_manager,EntityManager &p_entity_manager)
		:AIBehaviorLoaderBase(p_behavior_manager,p_entity_manager,"AIMelee")
	{}
	
	virtual ~AIMeleeLoader() override
	{}
};

#endif // AI_MELEE_LOADER_H
