#ifndef SIMPLE_CONTROLLER_REPOSITORY_H
#define SIMPLE_CONTROLLER_REPOSITORY_H

#include <IController.h>

#include <vector>
#include <algorithm>

class SimpleControllerRepository : public IControllerRepository
{
private:
	std::vector <IController *> controllers;
	
public:
	
	virtual unsigned int GetNumControllers() const override
	{
		return controllers.size();
	}
	
	virtual IController *GetController(unsigned int id) const override
	{
		if(id < controllers.size())
			{return controllers[id];}
		
		return nullptr;
	}
	
	void AddController(IController *newController)
	{
		controllers.push_back(newController);
	}
	
	void RemoveController(IController *controllerToRemove)
	{
		std::remove(controllers.begin(),controllers.end(),controllerToRemove);
	}
	
	SimpleControllerRepository()
	{}
	
	virtual ~SimpleControllerRepository() override
	{}
};

#endif // SIMPLE_CONTROLLER_REPOSITORY_H
