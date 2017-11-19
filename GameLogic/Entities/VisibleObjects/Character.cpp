
#include "Character.h"

#include <LinearMath/btTransform.h>
/*
void Character::Step()
{
	movement_controller.ApplyControls();
	look_controller.ApplyControls();
	
	for(ICharacterObserver *observer : char_observers)
	{
		observer->OnPositionChanged(state->GetPosition().x(),state->GetPosition().y(),state->GetPosition().z());
		observer->OnOrientationChanged(state->GetOrientation().w(),state->GetOrientation().x(),state->GetOrientation().y(),state->GetOrientation().z());
		
		if(controller.Aim())
		{
			observer->OnAiming();
		}
		else
		{
			observer->OnAimReleased();
		}
		
		if(controller.Shoot())
		{
			observer->OnShooting();
		}
		else
		{
			observer->OnShootingReleased();
		}
		
		if(controller.Moving())
		{
			observer->OnMoving();
		}
		else
		{
			observer->OnStanding();
		}
	}
}
*/
