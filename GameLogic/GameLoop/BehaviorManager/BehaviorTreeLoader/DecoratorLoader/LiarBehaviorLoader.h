#ifndef LIAR_BEHAVIOR_LOADER_H
#define LIAR_BEHAVIOR_LOADER_H

#include "DecoratorBehaviorLoader.h"

#include <EntityBehaviors/BehaviorTree/Decorators/LiarBehavior.h>

class LiarBehaviorLoader : public DecoratorBehaviorLoader
{
protected:
	
	virtual IBehavior<AIContext> *CreateDecorator(IBehavior<AIContext> *child,const liJSON_Object *object) override
	{
		BehaviorState state = FAILED;
		std::string loaded_state = ToConstString(object->GetVariable("State"))->GetValue();
		if(loaded_state == "RUNNING")
			{state = RUNNING;}
		if(loaded_state == "SUCCEEDED")
			{state = SUCCEEDED;}
		if(loaded_state == "FAILED")
			{state = FAILED;}
		
		//std::cout << "Liar loaded: " << loaded_state << std::endl;
		
		return new LiarBehavior<AIContext>(child,state);
	}
	
public:
	
	LiarBehaviorLoader(BehaviorManager &p_behavior_manager)
		:DecoratorBehaviorLoader(p_behavior_manager,"LiarBehavior")
	{}
	
	virtual ~LiarBehaviorLoader() override
	{}
};

#endif // LIAR_BEHAVIOR_LOADER_H
