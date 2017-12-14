#ifndef SHOOTING_OBJECT_H
#define SHOOTING_OBJECT_H

class IWeaponController
{
public:
	virtual bool IsAiming() const = 0;
	virtual bool IsShooting() const = 0;
	
	virtual bool IsMelee() const = 0;
	
	IWeaponController()
	{}
	
	virtual ~IWeaponController()
	{}
};

class IProjectileFactory
{
public:
	virtual void SpawnBullet(const btVector3 &position,const btVector3 &velocity,float radius,unsigned int species) = 0;
	virtual void Melee(const btVector3 &position,const btVector3 &velocity,float damage,unsigned int species) = 0;
	
	IProjectileFactory()
	{}
	virtual ~IProjectileFactory()
	{}
};

class IWeaponState
{
public:
	virtual btVector3 GetMuzzlePosition() = 0;
	virtual btVector3 GetMuzzleDirection() = 0;
	
	IWeaponState()
	{}
	virtual ~IWeaponState()
	{}
};

class ShootingObject
{
private:
	IWeaponState &weapon_state;
	IProjectileFactory &projectile_factory;
	
	unsigned int species;
	
	IWeaponController *controller;
	
	const unsigned int max_cycles = 7;
	unsigned int current_cycles = 0;
	
	const unsigned int max_melee_cycles = 15;
	unsigned int current_melee_cycles = 0;
	
public:
	
	bool IsAiming() const
	{
		if(controller != nullptr)
		{
			return controller->IsAiming();
		}
		
		return false;
	}
	
	bool IsShooting() const
	{
		if(controller != nullptr)
		{
			return controller->IsShooting();
		}
		
		return false;
	}
	
	bool IsMelee() const
	{
		if(controller != nullptr)
		{
			return controller->IsMelee();
		}
		
		return false;
	}
	
	void SetController(IWeaponController *new_controller)
	{
		controller = new_controller;
	}
	
	void Step()
	{
		if(current_cycles < max_cycles)
		{
			current_cycles++;
		}
		
		if(current_melee_cycles < max_melee_cycles)
		{
			current_melee_cycles++;
		}
		
		if(IsShooting() && (current_cycles >= max_cycles))
		{
			projectile_factory.SpawnBullet(weapon_state.GetMuzzlePosition(),250.0 * weapon_state.GetMuzzleDirection(),0.75,species);
			current_cycles = 0;
		}
		
		if(IsMelee() && (current_melee_cycles >= max_melee_cycles))
		{
			projectile_factory.Melee(weapon_state.GetMuzzlePosition(),15.0 * weapon_state.GetMuzzleDirection(),50,species);
			current_melee_cycles = 0;
		}
	}
	
	ShootingObject(IWeaponState &p_weapon_state,IProjectileFactory &p_projectile_factory,unsigned int p_species)
		:weapon_state(p_weapon_state),projectile_factory(p_projectile_factory),species(p_species)
	{}
};

#endif // SHOOTING_OBJECT_H
