#ifndef PLAYER_CAMERA_CONTROLLER_H
#define PLAYER_CAMERA_CONTROLLER_H

#include <EntityBehaviors/Camera/CharacterTracking/TrackCharacterBehavior.h>

class PlayerCameraController
{
private:
	Character &tracked_entity;
	Camera &camera;
	
	TrackCharacterBehavior track_character;
	
	EnhancedController controller;
	
public:
	
	void Step()
	{
		track_character.point_above_shoulder.SetAngle(-1.0 * controller.GetYaw() * PI/180.0 + PI/2.0 + 3.0*PI/8.0);
		
		CameraContext context(camera);
		
		track_character.Run(context);
	}
	
	PlayerCameraController(Character &p_tracked_entity,Camera &p_camera,const IController &p_controller)
		:tracked_entity(p_tracked_entity),camera(p_camera),track_character(/*p_camera,*/p_tracked_entity),controller(p_controller)
	{}
};

#endif // PLAYER_CAMERA_CONTROLLER_H
