#ifndef AI_FOLLOW_BEHAVIOR_H
#define AI_FOLLOW_BEHAVIOR_H

#include <EntityBehaviors/Camera/CharacterTracking/PointAroundCharacter.h>
#include <EntityBehaviors/Camera/CharacterTracking/CharacterLookAtPoint.h>

#include "AIGoto.h"

class AIFollowCharacter : public IBehavior<AIContext>
{
private:
	PointAroundCharacter followed_character_point;
	AIGoto goto_behavior;
	
public:
	
	virtual BehaviorState Run(AIContext &context) override
	{
		return goto_behavior.Run(context);
	}
	
	AIFollowCharacter(Character &p_followed_character,float p_radius)
		:followed_character_point(p_followed_character,0.0,0.0,0.0),
		 goto_behavior(followed_character_point,p_radius)
	{}
	
	virtual ~AIFollowCharacter() override
	{}
};

#endif // 
