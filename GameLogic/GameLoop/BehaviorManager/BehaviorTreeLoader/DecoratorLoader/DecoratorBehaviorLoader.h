#ifndef DECORATOR_BEHAVIOR_LOADER_H
#define DECORATOR_BEHAVIOR_LOADER_H

#include <GameLoop/BehaviorManager/BehaviorLoaderBase.h>

class DecoratorBehaviorLoader : public BehaviorLoaderBase
{
protected:
	
	virtual IBehavior<AIContext> *CreateDecorator(IBehavior<AIContext> *child,const liJSON_Object *object) = 0;
	
public:
	
	virtual IBehavior<AIContext> *LoadBehavior(const liJSON_Object *object) override
	{
		const liJSON_Object *child_object = ToConstObject(object->GetVariable("Child"));
		
		IBehavior<AIContext> *child = nullptr;
		if(child_object != nullptr)
		{
			child = behavior_manager.LoadBehavior(child_object);
		}
		
		//std::cout << "Loading decorator with child: " << child << std::endl;
		
		return CreateDecorator(child,object);
	}
	
	DecoratorBehaviorLoader(BehaviorManager &p_behavior_manager,const std::string &type)
		:BehaviorLoaderBase(p_behavior_manager,type)
	{}
	
	virtual ~DecoratorBehaviorLoader() override
	{}
};

#endif // DECORATOR_BEHAVIOR_LOADER_H
