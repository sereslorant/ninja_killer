#ifndef AI_CONTEXT_H
#define AI_CONTEXT_H

#include <Entities/VisibleObjects/Character.h>

#include "AIMovementController.h"

struct AIContext
{
	Character &character;
	AIMovementController &movement_controller;
	
	AIContext(Character &p_character,AIMovementController &p_movement_controller)
		:character(p_character),movement_controller(p_movement_controller)
	{}
};

#endif // AI_CONTEXT_H
