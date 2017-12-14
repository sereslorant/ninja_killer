#ifndef SEQUENCE_BEHAVIOR_H
#define SEQUENCE_BEHAVIOR_H

#include "CompositeBehaviorBase.h"

template<class ContextType_T>
class SequenceBehavior : public CompositeBehaviorBase<ContextType_T>
{
private:
	//unsigned int current_behavior = 0;
	
public:
	
	virtual BehaviorState Run(ContextType_T &context) override
	{
		unsigned int current_behavior = 0;
		if(context.GetBehaviorPath().size() != 0)
		{
			current_behavior = context.GetBehaviorPath().back();
			context.GetBehaviorPath().pop_back();
		}
		
		BehaviorState last_child_state = SUCCEEDED;
		for(;current_behavior < this->children.size();current_behavior++)
		{
			IBehavior<ContextType_T> *child = this->children[current_behavior];
			last_child_state = child->Run(context);
			
			if(last_child_state == FAILED)
			{
				current_behavior = 0;
				break;
			}
			
			if(last_child_state == RUNNING)
			{
				break;
			}
		}
		
		if(current_behavior == this->children.size())
		{
			//std::cout << "Back to begin: " << current_behavior << ";" << this->children.size() << std::endl;
			current_behavior = 0;
		}
		
		context.GetBehaviorPath().push_back(current_behavior);
		
		return last_child_state;
	}
	
	SequenceBehavior(std::initializer_list<IBehavior<ContextType_T> *> p_children)
		:CompositeBehaviorBase<ContextType_T>(p_children)
	{}
	
	template<class Iterator_T>
	SequenceBehavior(Iterator_T begin,Iterator_T end)
		:CompositeBehaviorBase<ContextType_T>(begin,end)
	{}
	
	virtual ~SequenceBehavior() override
	{}
};

#endif // SEQUENCE_BEHAVIOR_H
