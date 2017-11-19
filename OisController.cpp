
#include "OisController.h"

void OisController::UpdateInput()
{
	keyboard->capture();
	
	moveForward		= keyboard->isKeyDown(OIS::KC_UP);
	moveBackward	= keyboard->isKeyDown(OIS::KC_DOWN);
	moveLeft		= keyboard->isKeyDown(OIS::KC_LEFT);
	moveRight		= keyboard->isKeyDown(OIS::KC_RIGHT);
	
	mouse->capture();
	
	const OIS::MouseState &mouseState = mouse->getMouseState();
	
	aim = mouseState.buttonDown(OIS::MB_Right);
	shoot = mouseState.buttonDown(OIS::MB_Left);
	
	float dyaw = mouseState.X.rel * mouse_sensitivity;
	yaw = yaw - dyaw;
	
	if(yaw > 180.0)
		{yaw -= 360.0;}
	
	if(yaw < -180.0)
		{yaw += 360.0;}
	
	//if(yaw < 0.0)
	//	{yaw += 360.0;}
	
	float dpitch = mouseState.Y.rel * mouse_sensitivity;
	pitch = pitch + dpitch;
	if(pitch < -90.0)
		{pitch = -90;}
		
	if(pitch > 90.0)
		{pitch =  90;}
}
