#ifndef PLAYER_MOVEMENT_CONTROLLER_H
#define PLAYER_MOVEMENT_CONTROLLER_H

#include <Entities/MovingObject.h>

#include <Utils/EnhancedController.h>

#include <LinearMath/btTransform.h>

class PlayerMovementController : public IMovementController
{
protected:
	IControllable &controllable;
	EnhancedController controller;
	
public:
	
	virtual bool IsMoving() override
	{
		return controller.Moving();
	}
	
	virtual TargetMovementState CalculateTargetState() override
	{
		TargetMovementState result = {};
		
		btVector3 displacement(0.0,0.0,0.0);
		
		btQuaternion orientation({0.0,1.0,0.0},controllable.GetYaw());
		
		const btVector3 forward	= btTransform(orientation) * btVector3( 0.0,0.0,1.0);
		const btVector3 right	= btTransform(orientation) * btVector3(-1.0,0.0,0.0);
		
		if(controller.MoveForward())
		{
			displacement += forward;
		}
		if(controller.MoveBackward())
		{
			displacement -= forward;
		}
		if(controller.MoveLeft())
		{
			displacement -= right;
		}
		if(controller.MoveRight())
		{
			displacement += right;
		}
		
		if(controller.Moving())
		{
			displacement.normalize();
		}
		else
		{
			displacement = {0.0,0.0,0.0};
		}
		
		result.velocity	= displacement;
		
		if(controller.Moving() || controller.Aim())
		{
			result.yaw = controller.GetYaw() * PI/180.0;
		}
		else
		{
			result.yaw = controllable.GetYaw();
		}
		
		return result;
	}
	
	PlayerMovementController(IControllable &p_controllable,const IController &p_controller)
		:controllable(p_controllable),controller(p_controller)
	{}
	
	virtual ~PlayerMovementController() override
	{}
};

#endif // PLAYER_MOVEMENT_CONTROLLER_H
