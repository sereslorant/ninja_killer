#ifndef VISIBLE_OBJECT_H
#define VISIBLE_OBJECT_H

#include <LinearMath/btVector3.h>
#include <LinearMath/btQuaternion.h>

class IVisibleObjectState
{
public:
	
	virtual const btVector3 &GetPosition() = 0;
	virtual const btQuaternion &GetOrientation() = 0;
	
	IVisibleObjectState()
	{}
	
	virtual ~IVisibleObjectState()
	{}
};

#include <IGameObserver.h>

#include <Entities/IEntity.h>

#include <memory>
#include <list>

#include <iostream>

class VisibleObject : public IEntity
{
protected:
	std::unique_ptr<IVisibleObjectState> state;
	
	std::string label;
	
	std::list<IVisibleObserver *> observers;
	
public:
	
	const btVector3 &GetPosition() const
	{
		return state->GetPosition();
	}
	
	const btQuaternion &GetOrientation() const
	{
		return state->GetOrientation();
	}
	
	const std::string &GetLabel() const
	{
		return label;
	}
	
	void SetLabel(const std::string &new_label)
	{
		label = new_label;
		
		for(IVisibleObserver *observer : observers)
			{observer->OnLabelChanged(label);}
	}
	
	void AddObserver(IVisibleObserver *new_observer)
	{
		observers.push_back(new_observer);
		
		new_observer->OnLabelChanged(label);
	}
	
	virtual void Step() override
	{
		for(IVisibleObserver *observer : observers)
		{
			observer->OnPositionChanged(state->GetPosition().x(),state->GetPosition().y(),state->GetPosition().z());
			observer->OnOrientationChanged(state->GetOrientation().w(),state->GetOrientation().x(),state->GetOrientation().y(),state->GetOrientation().z());
		}
	}
	
	VisibleObject(IVisibleObjectState *p_state,const std::string &p_label)
		:state(p_state),label(p_label)
	{}
	
	virtual ~VisibleObject() override
	{
		std::cout << "Visible destroyed" << std::endl;
	}
};

#endif // VISIBLE_OBJECT_H
