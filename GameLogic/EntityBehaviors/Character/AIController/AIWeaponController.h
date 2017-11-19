#ifndef AI_WEAPON_CONTROLLER_H
#define AI_WEAPON_CONTROLLER_H

#include <Entities/ShootingObject.h>

class AIWeaponController : public IWeaponController
{
public:
	
	virtual bool IsAiming() const override
	{
		return true;
	}
	
	virtual bool IsShooting() const override
	{
		return false;
	}
	
	AIWeaponController()
	{}
	
	virtual ~AIWeaponController() override
	{}
};

#endif // AI_WEAPON_CONTROLLER_H
