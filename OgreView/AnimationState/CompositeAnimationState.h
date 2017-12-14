#ifndef COMPOSITE_ANIMATION_STATE_H
#define COMPOSITE_ANIMATION_STATE_H

#include "AnimationStateBase.h"

class CompositeAnimationState : public AnimationStateBase
{
private:
	AnimationStateBase *current_state;
	
public:
	
	virtual AnimationStateBase *CloneInternal(std::list<std::unique_ptr<IAnimationState> > &children) const override
	{
		AnimationStateBase *initial_state = current_state->CloneInternal(children);
		std::map<std::string,AnimationStateBase *> children_clones = {{current_state->GetName(),initial_state}};
		
		std::list<AnimationStateBase *> children_to_process = {current_state};
		while(children_to_process.size() > 0)
		{
			AnimationStateBase *current_child = children_to_process.front();
			children_to_process.pop_front();
			
			AnimationStateBase *current_child_clone = children_clones[current_child->GetName()];
			
			current_child->ForeachNextState([&children,&children_clones,&children_to_process,&current_child_clone]
				(const std::string &event,AnimationStateBase *next_state)
				{
					AnimationStateBase *next_clone;
					auto I = children_clones.find(next_state->GetName());
					if(I == children_clones.end())
					{
						next_clone = next_state->CloneInternal(children);
						children_clones[next_clone->GetName()] = next_clone;
						
						children_to_process.push_back(next_state);
					}
					else
					{
						next_clone = I->second;
					}
					
					current_child_clone->AddNextState(event,next_clone);
				}
			);
		}
		
		CompositeAnimationState *clone = new CompositeAnimationState(GetName());
		children.emplace_back(clone);
		clone->SetInitialState(initial_state);
		
		return clone;
	}
	
	virtual void UpdateState(const std::string &event) override
	{
		current_state = current_state->GetNextState(event);
		current_state->UpdateState(event);
	}
	
	virtual const std::string &GetAnimationName() const override
	{
		return current_state->GetAnimationName();
	}
	
	void SetInitialState(AnimationStateBase *initial_state)
	{
		current_state = initial_state;
	}
	
	CompositeAnimationState(const std::string &p_name)
		:AnimationStateBase(p_name)
	{}
};

#endif // COMPOSITE_ANIMATION_STATE_H
