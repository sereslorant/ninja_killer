#ifndef AI_MOVEMENT_CONTROLLER_H
#define AI_MOVEMENT_CONTROLLER_H

#include <Entities/MovingObject.h>

class AIMovementController : public IMovementController
{
private:
	MovementState target_state = {};
	
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
	
	virtual MovementState CalculateTargetState(const MovementState &current_state) override
	{
		return target_state;
	}
	
	AIMovementController()
	{}
	
	virtual ~AIMovementController() override
	{}
};

#endif // AI_MOVEMENT_CONTROLLER_H
