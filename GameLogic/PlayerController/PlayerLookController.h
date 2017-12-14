#ifndef PLAYER_LOOK_CONTROLLER_H
#define PLAYER_LOOK_CONTROLLER_H

#include <Entities/LookingObject.h>

#include <Utils/EnhancedController.h>

class PlayerLookController : public ILookController
{
private:
	//btQuaternion look_orientation = btQuaternion({0.0,1.0,0.0},0.0);
	
	EnhancedController controller;
	
public:
	
	virtual btQuaternion GetLookOrientation() override
	{
		btQuaternion rot_pitch({1.0,0.0,0.0},controller.GetPitch() * PI / 180.0);
		btQuaternion rot_yaw({0.0,1.0,0.0},controller.GetYaw() * PI / 180.0);
		
		return rot_yaw * rot_pitch;
	}
	
	PlayerLookController(const IController &p_controller)
		:controller(p_controller)
	{}
};

#endif // PLAYER_LOOK_CONTROLLER_H
