#ifndef OIS_CONTROLLER_H
#define OIS_CONTROLLER_H

#include <GameLogic/IController.h>

#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

class OisController : public IController
{
private:
	OIS::Keyboard	*keyboard;
	OIS::Mouse		*mouse;
	
	float mouse_sensitivity = 0.5;
	
	bool moveForward = false;
	bool moveBackward = false;
	bool moveLeft = false;
	bool moveRight = false;
	
	bool aim = false;
	bool shoot = false;
	
	float yaw	= 0.0;
	float pitch	= 0.0;
	
public:
	
	virtual bool MoveForward() const override
	{
		return moveForward;
	}
	
	virtual bool MoveBackward() const override
	{
		return moveBackward;
	}
	
	virtual bool MoveLeft() const override
	{
		return moveLeft;
	}
	
	virtual bool MoveRight() const override
	{
		return moveRight;
	}
	
	virtual bool Aim() const override
	{
		return aim;
	}
	
	virtual bool Shoot() const override
	{
		return shoot;
	}
	
	virtual float GetYaw() const override
	{
		return yaw;
	}
	
	virtual float GetPitch() const override
	{
		return pitch;
	}
	
	void UpdateInput();
	
	OisController(OIS::Keyboard *p_keyboard,OIS::Mouse *p_mouse)
		:keyboard(p_keyboard),mouse(p_mouse)
	{
		//
	}
	
	virtual ~OisController() override
	{
		//
	}
};

#endif // OIS_CONTROLLER_H
