#ifndef AI_MOVEMENT_CONTROLLER_H
#define AI_MOVEMENT_CONTROLLER_H

#include <Entities/MovingObject.h>

class AIMovementController : public IMovementController
{
private:
	IControllable &controllable;
	TargetMovementState target_state = {};
	
public:
	
	virtual bool IsMoving() override
	{
		return target_state.velocity.length2() > 1e-1;
	}
	
	void SetVelocity(const btVector3 &direction)
	{
		target_state.velocity = direction;
		
		if(target_state.velocity.length2() > 1.0)
		{
			target_state.velocity.normalize();
		}
	}
	
	void SetYaw(float yaw)
	{
		target_state.yaw = yaw;
	}
	
	virtual TargetMovementState CalculateTargetState() override
	{
		return target_state;
	}
	
	AIMovementController(IControllable &p_controllable)
		:controllable(p_controllable)
	{}
	
	virtual ~AIMovementController() override
	{}
};

#endif // AI_MOVEMENT_CONTROLLER_H
