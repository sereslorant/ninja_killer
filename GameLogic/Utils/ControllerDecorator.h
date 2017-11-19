#ifndef CONTROLLER_DECORATOR_H
#define CONTROLLER_DECORATOR_H

#include <IController.h>

class ControllerDecorator : public IController
{
protected:
	const IController &wrapped_controller;
	
public:
	
	virtual bool MoveForward() const override
	{
		return wrapped_controller.MoveForward();
	}
	
	virtual bool MoveBackward() const override
	{
		return wrapped_controller.MoveBackward();
	}
	
	virtual bool MoveLeft() const override
	{
		return wrapped_controller.MoveLeft();
	}
	
	virtual bool MoveRight() const override
	{
		return wrapped_controller.MoveRight();
	}
	
	virtual bool Aim() const override
	{
		return wrapped_controller.Aim();
	}
	
	virtual bool Shoot() const override
	{
		return wrapped_controller.Shoot();
	}
	
	virtual float GetYaw() const override
	{
		return wrapped_controller.GetYaw();
	}
	
	virtual float GetPitch() const override
	{
		return wrapped_controller.GetPitch();
	}
	
	ControllerDecorator(const IController &controller)
		:wrapped_controller(controller)
	{}
};

#endif // CONTROLLER_DECORATOR_H
