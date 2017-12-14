#ifndef PLAYER_WEAPON_CONTROLLER_H
#define PLAYER_WEAPON_CONTROLLER_H

#include <Entities/ShootingObject.h>

#include <Utils/EnhancedController.h>

class PlayerWeaponController : public IWeaponController
{
private:
	EnhancedController controller;
	
public:
	
	virtual bool IsAiming() const override
	{
		return controller.Aim();
	}
	
	virtual bool IsShooting() const override
	{
		return controller.Shoot();
	}
	
	virtual bool IsMelee() const override
	{
		return false;
	}
	
	PlayerWeaponController(const IController &p_controller)
		:controller(p_controller)
	{}
	
	virtual ~PlayerWeaponController() override
	{}
};

#endif // PLAYER_WEAPON_CONTROLLER_H
