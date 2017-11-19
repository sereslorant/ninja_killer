#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H

#include <LinearMath/btVector3.h>

#include <Utils/PIController.h>
#include <Utils/AngleUtils.h>

#include <memory>

class IControllable
{
public:
	
	virtual const btVector3 &GetVelocity() = 0;
	virtual float GetYaw() = 0;
	
	virtual void ApplyForce(const btVector3 &direction) = 0;
	virtual void SetOrientation(const btVector3 &d_axis,btScalar d_orientation) = 0;
	
	IControllable()
	{}
	
	virtual ~IControllable()
	{}
};

struct TargetMovementState
{
	btVector3 velocity;
	btScalar yaw;
};

class IMovementController
{
public:
	
	virtual bool IsMoving() = 0;
	
	virtual TargetMovementState CalculateTargetState() = 0;
	
	IMovementController()
	{}
	
	virtual ~IMovementController()
	{}
};

class MovingObject
{
protected:
	std::unique_ptr<IControllable> object_state;
	
	PIController vel_x_controller;
	PIController vel_z_controller;
	
	PIController yaw_controller;
	
	float speed = 50.0;
	
	IMovementController *controller = nullptr;
	
public:
	
	bool IsMoving()
	{
		if(controller != nullptr)
		{
			return controller->IsMoving();
		}
		
		return false;
	}
	
	float GetYaw()
	{
		return object_state->GetYaw();
	}
	
	virtual void Step()
	{
		if(controller == nullptr)
			{return;}
		
		TargetMovementState target_state = controller->CalculateTargetState();
		
		target_state.velocity *= speed;
		
		float vel_error_x = target_state.velocity[0] - object_state->GetVelocity()[0];
		float vel_error_z = target_state.velocity[2] - object_state->GetVelocity()[2];
		object_state->ApplyForce({vel_x_controller.GetSignal(vel_error_x),0.0,vel_z_controller.GetSignal(vel_error_z)});
		
		float yaw_error = GetDeltaAngle(object_state->GetYaw(),target_state.yaw);
		float yaw_signal = yaw_controller.GetSignal(yaw_error);
		object_state->SetOrientation({0.0,1.0,0.0},yaw_signal);
	}
	
	void SetController(IMovementController *new_controller)
	{
		controller = new_controller;
		
	}
	
	MovingObject(IControllable *p_controllable)
		:object_state(p_controllable),
			vel_x_controller(75.0,(1.0/60.0)/(1.0/30.0)),
			vel_z_controller(75.0,(1.0/60.0)/(1.0/30.0)),
			yaw_controller(50.0,(1.0/60.0)/(1.0/50.0))
	{}
};

#endif // MOVING_OBJECT_H
