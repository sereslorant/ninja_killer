#ifndef AI_LOOK_CONTROLLER_H
#define AI_LOOK_CONTROLLER_H

#include <Entities/LookingObject.h>

class AILookController : public ILookController
{
private:
	btQuaternion look_orientation = btQuaternion({0.0,1.0,0.0},0.0);
	
public:
	
	virtual btQuaternion GetLookOrientation() override
	{
		return look_orientation;
	}
	
	void SetLookDirection(const btVector3 &look_direction)
	{
		float dot = look_direction.dot({0.0,0.0,1.0});
		float angle = std::acos(dot);
		
		btVector3 axis = -1.0 * look_direction.cross({0.0,0.0,1.0});
		axis.normalize();
		
		look_orientation = {axis,angle};
	}
	
	AILookController()
	{}
};

#endif // AI_LOOK_CONTROLLER_H
