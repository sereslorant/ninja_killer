#ifndef CAMERA_ACTION_H
#define CAMERA_ACTION_H

#include <Entities/Camera.h>

#include <EntityBehaviors/BehaviorTree/IBehavior.h>
#include <EntityBehaviors/IPointOfInterest.h>

struct CameraContext
{
	Camera &camera;
	
	CameraContext(Camera &p_camera)
		:camera(p_camera)
	{}
};

class CameraAction : public IBehavior<CameraContext>
{
protected:
	//Camera &camera;
	IPointOfInterest &point_of_interest;
	
public:
	
	CameraAction(/*Camera &p_camera,*/IPointOfInterest &p_point_of_interest)
		:/*camera(p_camera),*/point_of_interest(p_point_of_interest)
	{}
	
	virtual ~CameraAction() override
	{}
};

#endif // CAMERA_ACTION_H
