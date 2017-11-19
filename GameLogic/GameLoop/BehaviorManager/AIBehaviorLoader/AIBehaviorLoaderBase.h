#ifndef AI_BEHAVIOR_LOADER_BASE_H
#define AI_BEHAVIOR_LOADER_BASE_H

#include <GameLoop/BehaviorManager/BehaviorLoaderBase.h>

#include <GameLoop/EntityManager/EntityManager.h>

class AIBehaviorLoaderBase : public BehaviorLoaderBase
{
protected:
	EntityManager &entity_manager;
	
public:
	
	AIBehaviorLoaderBase(BehaviorManager &p_behavior_manager,EntityManager &p_entity_manager,const std::string &type)
		:BehaviorLoaderBase(p_behavior_manager,type),entity_manager(p_entity_manager)
	{}
	
	virtual ~AIBehaviorLoaderBase() override
	{}
};

#endif // AI_BEHAVIOR_LOADER_BASE_H
