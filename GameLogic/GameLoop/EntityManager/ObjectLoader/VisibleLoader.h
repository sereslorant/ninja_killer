#ifndef VISIBLE_LOADER_H
#define VISIBLE_LOADER_H

#include <Entities/VisibleObjects/VisibleObject.h>

#include <lJSON/lJSON_Util.h>

class VisibleLoader
{
private:
	std::string label;
	
public:
	
	const std::string &GetLabel()
	{
		return label;
	}
	
	void Load(const liJSON_Object *object)
	{
		label = ToConstString(object->GetVariable("label"))->GetValue();
	}
	
	VisibleObject *Build(IVisibleObjectState *state)
	{
		return new VisibleObject(state,label);
	}
	
	VisibleLoader()
	{}
};

#endif // VISIBLE_LOADER_H
