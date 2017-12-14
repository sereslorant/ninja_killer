#ifndef ANIMATION_STATE_BASE_H
#define ANIMATION_STATE_BASE_H

#include "IAnimationState.h"

#include <map>

class AnimationStateBase;

using AnimationStateMap = std::map<std::string,AnimationStateBase *>;

class AnimationStateBase : public IAnimationState
{
private:
	std::string name;
	AnimationStateMap next_states;
	
public:
	
	virtual IAnimationState *Clone(std::list<std::unique_ptr<IAnimationState> > &children) const
	{
		return CloneInternal(children);
	}
	
	virtual AnimationStateBase *CloneInternal(std::list<std::unique_ptr<IAnimationState> > &children) const = 0;
	
	const std::string &GetName() const
	{
		return name;
	}
	
	AnimationStateBase *GetNextState(const std::string &event)
	{
		auto I = next_states.find(event);
		if(I != next_states.end())
		{
			return I->second;
		}
		
		return this;
	}
	
	void ForeachNextState(std::function<void(const std::string &,AnimationStateBase *)> operation)
	{
		for(auto &next_state : next_states)
		{
			operation(next_state.first,next_state.second);
		}
	}
	
	void AddNextState(const std::string &event,AnimationStateBase *next_state)
	{
		next_states[event] = next_state;
	}
	
	AnimationStateBase(const std::string &p_name)
		:name(p_name)
	{}
};

#endif // ANIMATION_STATE_BASE_H
