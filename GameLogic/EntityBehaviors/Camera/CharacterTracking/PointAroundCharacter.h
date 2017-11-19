#ifndef POINT_AROUND_CHARACTER_H
#define POINT_AROUND_CHARACTER_H

#include <Entities/VisibleObjects/Character.h>

#include <EntityBehaviors/IPointOfInterest.h>

#include <Utils/AngleUtils.h>

#include <LinearMath/btTransform.h>

class PointAroundCharacter : public IPointOfInterest
{
private:
	Character &tracked_character;
	
	float angle;
	float distance;
	float height;
	
public:
	
	float GetAngle()
	{
		return angle;
	}
	
	void SetAngle(float new_angle)
	{
		angle = TransformAngle(new_angle);
	}
	
	virtual btVector3 GetPosition() override
	{
		return tracked_character.GetPosition() + /*btTransform(tracked_character.GetOrientation()) **/ btVector3(distance * std::cos(angle + PI/2.0),height,distance * std::sin(angle + PI/2.0));
	}
	
	PointAroundCharacter(Character &p_tracked_character,float p_angle,float p_distance,float p_height)
		:tracked_character(p_tracked_character),angle(TransformAngle(p_angle)),distance(p_distance),height(p_height)
	{}
	
	virtual ~PointAroundCharacter() override
	{}
};

#endif // POINT_AROUND_CHARACTER_H
