#ifndef LIAR_BEHAVIOR_H
#define LIAR_BEHAVIOR_H

#include "ProxyBehavior.h"

template<class ContextType_T>
class LiarBehavior : public ProxyBehavior<ContextType_T>
{
protected:
	BehaviorState value;
	
public:
	
	virtual BehaviorState Run(ContextType_T &context) override
	{
		ProxyBehavior<ContextType_T>::Run(context);
		
		return value;
	}
	
	LiarBehavior(BehaviorState p_value)
		:value(p_value)
	{}
	
	LiarBehavior(IBehavior<ContextType_T> *p_wrapped_behavior,BehaviorState p_value)
		:ProxyBehavior<ContextType_T>(p_wrapped_behavior),value(p_value)
	{}
	
	virtual ~LiarBehavior() override
	{}
};

#endif // LIAR_BEHAVIOR_H
