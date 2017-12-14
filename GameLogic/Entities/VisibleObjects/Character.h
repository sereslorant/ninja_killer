#ifndef CHARACTER_H
#define CHARACTER_H

#include "VisibleObject.h"

#include <Entities/ICollisionCallback.h>

#include <Entities/MovingObject.h>
#include <Entities/LookingObject.h>
#include <Entities/ShootingObject.h>

#include <iostream>

class WeaponState : public IWeaponState
{
private:
	IVisibleObjectState &visible_state;
	LookingObject &looking_object;
	
public:
	virtual btVector3 GetMuzzlePosition() override
	{
		return visible_state.GetPosition() + btVector3(0.0,6.0,0.0) + 7.0*looking_object.GetLookDirection();
	}
	
	virtual btVector3 GetMuzzleDirection() override
	{
		return looking_object.GetLookDirection();
	}
	
	WeaponState(IVisibleObjectState &p_visible_state,LookingObject &p_looking_object)
		:visible_state(p_visible_state),looking_object(p_looking_object)
	{}
	virtual ~WeaponState() override
	{}
};

class Character : public IEntity, public ICollisionCallback
{
protected:
	
	VisibleObject visible_object;
	MovingObject moving_object;
	LookingObject looking_object;
	WeaponState weapon_state;
	ShootingObject shooting_object;
	
	float health = 1000.0;
	unsigned int species;
	
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
	
	virtual unsigned int GetSpecies() override
	{
		return species;
	}
	
	virtual void TakeDamage(float damage) override
	{
		std::cout << "Character taken damage " << damage << std::endl;
		health -= damage;
	}
	
	virtual void AcceptCollision(ICollisionCallback *callback) override
	{}
	
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
		if(health > 0.0)
		{
			moving_object.Step();
			shooting_object.Step();
		}
		
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
			
			if(shooting_object.IsMelee())
			{
				observer->OnMelee();
			}
			else
			{
				observer->OnMeleeReleased();
			}
			
			if(moving_object.IsMoving())
			{
				observer->OnMoving();
			}
			else
			{
				observer->OnStanding();
			}
			
			if(health <= 0.0)
			{
				observer->OnDying();
			}
		}
	}
	
	void AddObserver(ICharacterObserver *new_observer)
	{
		char_observers.push_back(new_observer);
		visible_object.AddObserver(new_observer);
	}
	
	Character(IVisibleObjectState *p_visible_state,const std::string &p_label,
				IControllable *p_state,unsigned int p_species,IProjectileFactory &p_projectile_factory)
		:visible_object(p_visible_state,p_label),moving_object(p_state),weapon_state(*p_visible_state,looking_object),shooting_object(weapon_state,p_projectile_factory,p_species),species(p_species)
	{}
	
	virtual ~Character() override
	{
		std::cout << "Character destroyed" << std::endl;
	}
};

#endif // CHARACTER_H
