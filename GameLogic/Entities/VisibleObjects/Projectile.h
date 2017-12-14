#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "VisibleObject.h"

#include <Entities/ICollisionCallback.h>

class Projectile : public IEntity, public ICollisionCallback
{
protected:
	VisibleObject visible_object;
	
	bool active = true;
	unsigned int species;
	
	unsigned int num_survivable_collisions = 3;
	
public:
	
	virtual unsigned int GetSpecies() override
	{
		return species;
	}
	
	virtual void TakeDamage(float damage) override
	{}
	
	virtual void AcceptCollision(ICollisionCallback *callback) override
	{
		if(active && callback != nullptr /*&& callback->GetSpecies() != species*/)
		{
			callback->TakeDamage(50.0);
			active = false;
		}
		
		if(active && num_survivable_collisions > 0)
			{num_survivable_collisions--;}
		else
		{
			//if(active)
			//	{std::cout << "died" << std::endl;}
			active = false;
		}
	}
	
	virtual void Step() override
	{
		visible_object.Step();
	}
	
	void AddObserver(IVisibleObserver *new_observer)
	{
		visible_object.AddObserver(new_observer);
	}
	
	Projectile(IVisibleObjectState *p_visible_state,const std::string &p_label,unsigned int p_species)
		:visible_object(p_visible_state,p_label),species(p_species)
	{}
	
	virtual ~Projectile() override
	{
		std::cout << "Projectile destroyed" << std::endl;
	}
};

#endif // PROJECTILE_H
