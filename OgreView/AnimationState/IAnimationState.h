#ifndef IANIMATION_STATE_H
#define IANIMATION_STATE_H

#include <list>
#include <string>

class IAnimationState
{
public:
	
	virtual IAnimationState *Clone(std::list<std::unique_ptr<IAnimationState> > &children) const = 0;
	
	virtual void UpdateState(const std::string &event) = 0;
	
	virtual const std::string &GetAnimationName() const = 0;
	
	IAnimationState()
	{}
	virtual ~IAnimationState()
	{}
};

#endif // IANIMATION_STATE_H
