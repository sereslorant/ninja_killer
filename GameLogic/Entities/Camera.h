#ifndef CAMERA_H
#define CAMERA_H

#include <LinearMath/btVector3.h>
#include <LinearMath/btQuaternion.h>

#include <IGameObserver.h>

#include <list>

class Camera
{
private:
	btVector3		position	= btVector3(0.0,0.0,0.0);
	btVector3		look_at		= btVector3(0.0,1.0,0.0);
	
	std::list<ICameraObserver *> observers;
	
public:
	
	void AddObserver(ICameraObserver *new_observer)
	{
		observers.push_back(new_observer);
	}
	
	void SetPosition(const btVector3 &new_position)
	{
		position = new_position;
	}
	
	void SetLookAt(const btVector3 &new_look_at)
	{
		look_at = new_look_at;
	}
	/*
	void SetOrientation(const btQuaternion &new_orientation)
	{
		orientation = new_orientation;
	}
	*/
	void Step()
	{
		
		for(ICameraObserver *observer : observers)
		{
			observer->OnPositionChanged(position.x(),position.y(),position.z());
			observer->OnLookAtChanged(look_at.x(),look_at.y(),look_at.z());
			//observer->OnOrientationChanged(orientation.w(),orientation.x(),orientation.y(),orientation.z());
		}
		
	}
	
	Camera()
	{}
};

#endif // CAMERA_H
