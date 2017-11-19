#ifndef CHARACTER_H
#define CHARACTER_H

#include "VisibleObject.h"

#include <Entities/MovingObject.h>
#include <Entities/LookingObject.h>
#include <Entities/ShootingObject.h>

#include <iostream>

class Character : public IEntity
{
protected:
	VisibleObject visible_object;
	MovingObject moving_object;
	LookingObject looking_object;
	ShootingObject shooting_object;
	
	std::list<ICharacterObserver *> char_observers;
	
public:
	
	const btVector3 &GetPosition() const
	{
		return visible_object.GetPosition();
	}
	
	const btQuaternion &GetOrientation() const
	{
		return visible_object.GetOrientation();
	}
	
	float GetYaw()
	{
		return moving_object.GetYaw();
	}
	
	const btQuaternion &GetLookOrientation()
	{
		return looking_object.GetLookOrientation();
	}
	
	void SetMovementController(IMovementController *movement_controller)
	{
		moving_object.SetController(movement_controller);
	}
	
	void SetLookController(ILookController *look_controller)
	{
		looking_object.SetController(look_controller);
	}
	
	void SetWeaponController(IWeaponController *weapon_controller)
	{
		shooting_object.SetController(weapon_controller);
	}
	
	virtual void Step() override
	{
		moving_object.Step();
		looking_object.Step();
		
		visible_object.Step();
		
		for(ICharacterObserver *observer : char_observers)
		{
			if(shooting_object.IsAiming())
			{
				observer->OnAiming();
			}
			else
			{
				observer->OnAimReleased();
			}
			
			if(shooting_object.IsShooting())
			{
				observer->OnShooting();
			}
			else
			{
				observer->OnShootingReleased();
			}
			
			if(moving_object.IsMoving())
			{
				observer->OnMoving();
			}
			else
			{
				observer->OnStanding();
			}
		}
	}
	
	void AddObserver(ICharacterObserver *new_observer)
	{
		char_observers.push_back(new_observer);
		visible_object.AddObserver(new_observer);
	}
	
	Character(IVisibleObjectState *p_visible_state,const std::string &p_label,
				IControllable *p_state)
		:visible_object(p_visible_state,p_label),moving_object(p_state)
	{}
	
	virtual ~Character() override
	{
		std::cout << "Character destroyed" << std::endl;
	}
};

#endif // CHARACTER_H
