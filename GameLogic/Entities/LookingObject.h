#ifndef LOOKING_OBJECT_H
#define LOOKING_OBJECT_H

#include <LinearMath/btQuaternion.h>

class ILookController
{
public:
	virtual btQuaternion GetLookOrientation() = 0;
	
	ILookController()
	{}
	virtual ~ILookController()
	{}
};

class LookingObject
{
private:
	btQuaternion look_orientation = btQuaternion({0.0,1.0,0.0},0.0);
	
	ILookController *look_controller = nullptr;
	
public:
	
	const btQuaternion &GetLookOrientation()
	{
		return look_orientation;
	}
	
	void SetController(ILookController *new_controller)
	{
		look_controller = new_controller;
	}
	
	void Step()
	{
		if(look_controller != nullptr)
		{
			look_orientation = look_controller->GetLookOrientation();
		}
	}
	
	LookingObject()
	{}
};

#endif // LOOKING_OBJECT_H
