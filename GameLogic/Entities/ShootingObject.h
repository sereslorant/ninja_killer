#ifndef SHOOTING_OBJECT_H
#define SHOOTING_OBJECT_H

class IWeaponController
{
public:
	virtual bool IsAiming() const = 0;
	virtual bool IsShooting() const = 0;
	
	IWeaponController()
	{}
	
	virtual ~IWeaponController()
	{}
};

class ShootingObject
{
private:
	IWeaponController *controller;
	
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
	
	void SetController(IWeaponController *new_controller)
	{
		controller = new_controller;
	}
	
	void Step()
	{
		//
	}
	
	ShootingObject()
	{}
};

#endif // SHOOTING_OBJECT_H
