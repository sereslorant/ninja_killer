#ifndef COMPOSITE_BEHAVIOR_BASE_H
#define COMPOSITE_BEHAVIOR_BASE_H

#include "../IBehavior.h"

#include <vector>

template<class ContextType_T>
class CompositeBehaviorBase : public IBehavior<ContextType_T>
{
protected:
	std::vector<IBehavior<ContextType_T> *> children;
	
public:
	
	CompositeBehaviorBase(std::initializer_list<IBehavior<ContextType_T> *> p_children)
		:children(p_children)
	{}
	
	template<class Iterator_T>
	CompositeBehaviorBase(Iterator_T begin,Iterator_T end)
		:children(begin,end)
	{}
	
	virtual ~CompositeBehaviorBase() override
	{}
};

#endif // COMPOSITE_BEHAVIOR_BASE_H
