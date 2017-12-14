#ifndef SEQUENCE_BEHAVIOR_LOADER_H
#define SEQUENCE_BEHAVIOR_LOADER_H

#include "CompositeBehaviorLoader.h"

#include <EntityBehaviors/BehaviorTree/Composites/SequenceBehavior.h>

class SequenceBehaviorLoader : public CompositeBehaviorLoader
{
protected:
	
	virtual IBehavior<AIContext> *CreateComposite(const std::list<IBehavior<AIContext> *> &children) override
	{
		return new SequenceBehavior<AIContext>(children.begin(),children.end());
	}
	
public:
	
	SequenceBehaviorLoader(BehaviorManager &p_behavior_manager)
		:CompositeBehaviorLoader(p_behavior_manager,"SequenceBehavior")
	{}
	
	virtual ~SequenceBehaviorLoader() override
	{}
};

#endif // SEQUENCE_BEHAVIOR_LOADER_H
