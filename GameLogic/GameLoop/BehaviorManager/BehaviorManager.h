#ifndef BEHAVIOR_MANAGER_H
#define BEHAVIOR_MANAGER_H

#include <EntityBehaviors/BehaviorTree/IBehavior.h>
#include <EntityBehaviors/Character/AIController/AIContext.h>

#include <lJSON/lJSON_Util.h>

class IBehaviorLoader
{
public:
	virtual IBehavior<AIContext> *LoadBehavior(const liJSON_Object *object) = 0;
	
	IBehaviorLoader()
	{}
	
	virtual ~IBehaviorLoader()
	{}
};

#include <EntityBehaviors/BehaviorTree/Decorators/ProxyBehavior.h>

#include <list>
#include <map>


#include <fstream>

class BehaviorManager
{
private:
	std::list<std::unique_ptr<IBehavior<AIContext> > > owned_behaviors;
	std::map<std::string,ProxyBehavior<AIContext> > behaviors;
	
	std::map<std::string,std::unique_ptr<IBehaviorLoader> > behavior_loaders;
	
public:
	
	IBehavior<AIContext> *GetBehavior(const std::string &name)
	{
		return &behaviors[name];
	}
	
	IBehavior<AIContext> *LoadBehavior(const liJSON_Object *object)
	{
		const std::string &type = ToConstString(object->GetVariable("Type"))->GetValue();
		
		auto I = behavior_loaders.find(type);
		if(I != behavior_loaders.end())
		{
			IBehavior<AIContext> *new_behavior = I->second->LoadBehavior(object);
			owned_behaviors.emplace_back(new_behavior);
			
			return new_behavior;
		}
		
		return nullptr;
	}
	
	void LoadBehaviors()
	{
		std::map<std::string,std::string> behavior_manifest =
		{
			{"squadmate_behavior","Content/Behaviors/Squadmate.json"}
		};
		
		for(auto &entry : behavior_manifest)
		{
			std::ifstream fin(entry.second);
			
			liJSON_Value *value;
			lJSON_Util::Parse(fin,value);
			
			const liJSON_Object *root = ToConstObject(value);
			if(root != nullptr)
			{
				IBehavior<AIContext> *behavior = LoadBehavior(root);
				behaviors[entry.first] = ProxyBehavior<AIContext>(behavior);
				
				owned_behaviors.emplace_back(behavior);
			}
			
			delete value;
		}
	}
	
	void AddBehaviorLoader(const std::string &type,IBehaviorLoader *behavior_loader)
	{
		behavior_loaders[type] = std::unique_ptr<IBehaviorLoader>(behavior_loader);
	}
	
	BehaviorManager()
	{}
};

#endif // BEHAVIOR_MANAGER_H
