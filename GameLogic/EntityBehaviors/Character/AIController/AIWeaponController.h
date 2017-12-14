#ifndef AI_WEAPON_CONTROLLER_H
#define AI_WEAPON_CONTROLLER_H

#include <Entities/ShootingObject.h>

class AIWeaponController : public IWeaponController
{
private:
	bool aiming = false;
	bool shooting = false;
	bool melee = false;
	
public:
	
	virtual bool IsAiming() const override
	{
		return aiming;
	}
	
	virtual bool IsShooting() const override
	{
		return shooting;
	}
	
	virtual bool IsMelee() const override
	{
		return melee;
	}
	
	void SetState(bool new_aiming,bool new_shooting,bool new_melee)
	{
		aiming = new_aiming;
		shooting = new_shooting;
		melee = new_melee;
	}
	
	AIWeaponController()
	{}
	
	virtual ~AIWeaponController() override
	{}
};

#endif // AI_WEAPON_CONTROLLER_H
