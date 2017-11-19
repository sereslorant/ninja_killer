#ifndef CAMERA_LOOK_AT_H
#define CAMERA_LOOK_AT_H

#include "CameraAction.h"

class CameraLookAt : public CameraAction
{
public:
	
	virtual BehaviorState Run(CameraContext &context) override
	{
		context.camera.SetLookAt(point_of_interest.GetPosition());
		
		return SUCCEEDED;
	}
	
	CameraLookAt(/*Camera &p_camera,*/IPointOfInterest &p_point_of_interest)
		:CameraAction(/*p_camera,*/p_point_of_interest)
	{}
	
	virtual ~CameraLookAt() override
	{}
};

#endif // CAMERA_LOOK_AT_H
