#ifndef AI_TURN_TOWARDS_CHARACTE_H
#define AI_TURN_TOWARDS_CHARACTE_H

#include "AITurnTowards.h"

class AITurnTowardsCharacter : public IBehavior<AIContext>
{
private:
	PointAroundCharacter followed_character_point;
	AITurnTowards turn_towards;
	
public:
	
	virtual BehaviorState Run(AIContext &context) override
	{
		return turn_towards.Run(context);
	}
	
	AITurnTowardsCharacter(Character &p_followed_character,float p_epsilon)
		:followed_character_point(p_followed_character,0.0,0.0,0.0),
		 turn_towards(followed_character_point,p_epsilon)
	{}
	
	virtual ~AITurnTowardsCharacter() override
	{}
};

#endif // AI_TURN_TOWARDS_CHARACTE_H
