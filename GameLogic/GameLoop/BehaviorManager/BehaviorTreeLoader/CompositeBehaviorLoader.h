#ifndef COMPOSITE_BEHAVIOR_LOADER_H
#define COMPOSITE_BEHAVIOR_LOADER_H


#include <GameLoop/BehaviorManager/BehaviorLoaderBase.h>

class CompositeBehaviorLoader : public BehaviorLoaderBase
{
protected:
	
	virtual IBehavior<AIContext> *CreateComposite(const std::list<IBehavior<AIContext> *> &children) = 0;
	
public:
	
	virtual IBehavior<AIContext> *LoadBehavior(const liJSON_Object *object) override
	{
		const liJSON_Array *child_array = ToConstArray(object->GetVariable("Children"));
		
		std::list<IBehavior<AIContext> *> children;
		if(child_array != nullptr)
		{
			for(int i=0;i < child_array->Size();i++)
			{
				const liJSON_Object *child_object = ToConstObject(child_array->GetElement(i));
				
				if(child_object != nullptr)
				{
					children.push_back(behavior_manager.LoadBehavior(child_object));
				}
			}
		}
		
		//std::cout << "Loading composite with children: " << child_array->Size() << std::endl;
		
		return CreateComposite(children);
	}
	
	CompositeBehaviorLoader(BehaviorManager &p_behavior_manager,const std::string &type)
		:BehaviorLoaderBase(p_behavior_manager,type)
	{}
	
	virtual ~CompositeBehaviorLoader() override
	{}
};

#endif // COMPOSITE_BEHAVIOR_LOADER_H
