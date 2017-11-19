#ifndef BEHAVIOR_LOADER_BASE_H
#define BEHAVIOR_LOADER_BASE_H

#include <GameLoop/BehaviorManager/BehaviorManager.h>

class BehaviorLoaderBase : public IBehaviorLoader
{
protected:
	BehaviorManager &behavior_manager;
	
public:
	
	BehaviorLoaderBase(BehaviorManager &p_behavior_manager,const std::string &type)
		:behavior_manager(p_behavior_manager)
	{
		behavior_manager.AddBehaviorLoader(type,this);
	}
	
	virtual ~BehaviorLoaderBase()
	{}
};

#endif // BEHAVIOR_LOADER_BASE_H
