#ifndef CHARACTER_LOOK_AT_POINT_H
#define CHARACTER_LOOK_AT_POINT_H

#include <Entities/VisibleObjects/Character.h>

#include <EntityBehaviors/IPointOfInterest.h>

#include <LinearMath/btTransform.h>

class CharacterLookAtPoint : public IPointOfInterest
{
private:
	Character &tracked_character;
	
public:
	
	virtual btVector3 GetPosition() override
	{
		btVector3 pos_z(0.0,0.0,1.0);
		
		return tracked_character.GetPosition() + btTransform(tracked_character.GetLookOrientation()) * pos_z * 500.0;
	}
	
	CharacterLookAtPoint(Character &p_tracked_character)
		:tracked_character(p_tracked_character)
	{}
	
	virtual ~CharacterLookAtPoint() override
	{}
};

#endif // CHARACTER_LOOK_AT_POINT_H
