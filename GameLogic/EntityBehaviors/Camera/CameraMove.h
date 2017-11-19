#ifndef CAMERA_MOVE_H
#define CAMERA_MOVE_H

#include "CameraAction.h"

class CameraMove : public CameraAction
{
public:
	
	virtual BehaviorState Run(CameraContext &context) override
	{
		context.camera.SetPosition(point_of_interest.GetPosition());
		
		return SUCCEEDED;
	}
	
	CameraMove(/*Camera &p_camera,*/IPointOfInterest &p_point_of_interest)
		:CameraAction(/*p_camera,*/p_point_of_interest)
	{}
	
	virtual ~CameraMove() override
	{}
};

#endif // CAMERA_MOVE_H
