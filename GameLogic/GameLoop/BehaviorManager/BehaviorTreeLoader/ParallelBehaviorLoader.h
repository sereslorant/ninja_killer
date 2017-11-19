#ifndef PARALLEL_BEHAVIOR_LOADER_H
#define PARALLEL_BEHAVIOR_LOADER_H

#include "CompositeBehaviorLoader.h"

class ParallelBehaviorLoader : public CompositeBehaviorLoader
{
protected:
	
	virtual IBehavior<AIContext> *CreateComposite(const std::list<IBehavior<AIContext> *> &children) override
	{
		return new ParallelBehavior<AIContext>(children.begin(),children.end());
	}
	
public:
	
	ParallelBehaviorLoader(BehaviorManager &p_behavior_manager)
		:CompositeBehaviorLoader(p_behavior_manager,"ParallelBehavior")
	{}
	
	virtual ~ParallelBehaviorLoader() override
	{}
};

#endif // PARALLEL_BEHAVIOR_LOADER_H
