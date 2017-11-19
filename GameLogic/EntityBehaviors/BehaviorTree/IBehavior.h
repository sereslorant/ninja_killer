#ifndef IBEHAVIOR_H
#define IBEHAVIOR_H

enum BehaviorState
{
	RUNNING,
	SUCCEEDED,
	FAILED,
};

template<class ContextType_T>
class IBehavior
{
public:
	
	virtual BehaviorState Run(ContextType_T &context) = 0;
	
	IBehavior()
	{}
	
	virtual ~IBehavior()
	{}
};

#endif // IBEHAVIOR_H
