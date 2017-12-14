#ifndef PARALLEL_BEHAVIOR_H
#define PARALLEL_BEHAVIOR_H

#include "CompositeBehaviorBase.h"

template<class ContextType_T>
class ParallelBehavior : public CompositeBehaviorBase<ContextType_T>
{
public:
	
	virtual BehaviorState Run(ContextType_T &context) override
	{
		bool found_not_successful = false;
		bool found_failed = false;
		
		for(IBehavior<ContextType_T> *child : this->children)
		{
			BehaviorState child_state = child->Run(context);
			
			if(child_state != SUCCEEDED)
			{
				found_not_successful = true;
				
				if(child_state == FAILED)
				{
					found_failed = true;
				}
			}
		}
		
		if(found_failed)
		{
			return FAILED;
		}
		else if(!found_not_successful)
		{
			return SUCCEEDED;
		}
		else
		{
			return RUNNING;
		}
	}
	
	ParallelBehavior(std::initializer_list<IBehavior<ContextType_T> *> p_children)
		:CompositeBehaviorBase<ContextType_T>(p_children)
	{}
	
	template<class Iterator_T>
	ParallelBehavior(Iterator_T begin,Iterator_T end)
		:CompositeBehaviorBase<ContextType_T>(begin,end)
	{}
	
	virtual ~ParallelBehavior() override
	{}
};

#endif // PARALLEL_BEHAVIOR_H
