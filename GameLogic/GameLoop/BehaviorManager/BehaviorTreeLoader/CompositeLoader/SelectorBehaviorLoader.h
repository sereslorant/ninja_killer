#ifndef SELECTOR_BEHAVIOR_LOADER_H
#define SELECTOR_BEHAVIOR_LOADER_H

#include "CompositeBehaviorLoader.h"

#include <EntityBehaviors/BehaviorTree/Composites/SelectorBehavior.h>

class SelectorBehaviorLoader : public CompositeBehaviorLoader
{
protected:
	
	virtual IBehavior<AIContext> *CreateComposite(const std::list<IBehavior<AIContext> *> &children) override
	{
		return new SelectorBehavior<AIContext>(children.begin(),children.end());
	}
	
public:
	
	SelectorBehaviorLoader(BehaviorManager &p_behavior_manager)
		:CompositeBehaviorLoader(p_behavior_manager,"SelectorBehavior")
	{}
	
	virtual ~SelectorBehaviorLoader() override
	{}
};

#endif // SELECTOR_BEHAVIOR_LOADER_H
