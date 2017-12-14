#ifndef PRIMITIVE_ANIMATION_STATE_H
#define PRIMITIVE_ANIMATION_STATE_H

#include "AnimationStateBase.h"

class PrimitiveAnimationState : public AnimationStateBase
{
private:
	std::string animation_name;
	
public:
	
	virtual AnimationStateBase *CloneInternal(std::list<std::unique_ptr<IAnimationState> > &children) const override
	{
		PrimitiveAnimationState *clone = new PrimitiveAnimationState(GetName(),animation_name);
		children.emplace_back(clone);
		
		return clone;
	}
	
	virtual void UpdateState(const std::string &event) override
	{}
	
	virtual const std::string &GetAnimationName() const override
	{
		return animation_name;
	}
	
	PrimitiveAnimationState(const std::string &p_name,const std::string &p_animation_name)
		:AnimationStateBase(p_name),animation_name(p_animation_name)
	{}
};

#endif // PRIMITIVE_ANIMATION_STATE_H
