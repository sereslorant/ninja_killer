#ifndef PROXY_BEHAVIOR_H
#define PROXY_BEHAVIOR_H

#include "../IBehavior.h"

template<class ContextType_T>
class ProxyBehavior : public IBehavior<ContextType_T>
{
protected:
	IBehavior<ContextType_T> *wrapped_behavior;
	
public:
	
	virtual BehaviorState Run(ContextType_T &context) override
	{
		if(wrapped_behavior != nullptr)
		{
			return wrapped_behavior->Run(context);
		}
		
		return FAILED;
	}
	
	ProxyBehavior(IBehavior<ContextType_T> *p_wrapped_behavior = nullptr)
		:wrapped_behavior(p_wrapped_behavior)
	{}
	
	virtual ~ProxyBehavior() override
	{}
};

#endif // PROXY_BEHAVIOR_H
