#ifndef ENHANCED_CONTROLLER_H
#define ENHANCED_CONTROLLER_H

#include "ControllerDecorator.h"

class EnhancedController : public ControllerDecorator
{
public:
	
	bool NotMovingLongitudinally() const
	{
		return	( wrapped_controller.MoveForward() &&  wrapped_controller.MoveBackward()) ||
				(!wrapped_controller.MoveForward() && !wrapped_controller.MoveBackward());
	}
	
	bool NotMovingLaterally() const
	{
		return	( wrapped_controller.MoveLeft() &&  wrapped_controller.MoveRight()) ||
				(!wrapped_controller.MoveLeft() && !wrapped_controller.MoveRight());
	}
	
	bool Moving() const
	{
		return !NotMoving();
	}
	
	bool NotMoving() const
	{
		return NotMovingLaterally() && NotMovingLongitudinally();
	}
	
	EnhancedController(const IController &controller)
		:ControllerDecorator(controller)
	{}
};

#endif // ENHANCED_CONTROLLER_H
