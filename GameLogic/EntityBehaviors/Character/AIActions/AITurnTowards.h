#ifndef AI_TURN_TOWARDS_H
#define AI_TURN_TOWARDS_H

#include <EntityBehaviors/BehaviorTree/IBehavior.h>
#include <EntityBehaviors/Character/AIController/AIContext.h>
#include <EntityBehaviors/IPointOfInterest.h>

class AITurnTowards : public IBehavior<AIContext>
{
private:
	IPointOfInterest &turn_towards_position;
	float epsilon;
	
public:
	
	virtual BehaviorState Run(AIContext &context) override
	{
		const btVector3 ideal_forward	= btVector3( 0.0,0.0,1.0);
		const btVector3 ideal_left		= btVector3(1.0,0.0,0.0);
		
		btVector3 dir = turn_towards_position.GetPosition() - context.character.GetPosition();
		if(dir.length2() > 1.0)
			{dir.normalize();}
		
		float angle = acos(ideal_forward.dot(dir));
		if(ideal_left.dot(dir) < 0.0)
		{
			angle *= -1.0;
		}
		
		angle = TransformAngle(angle);
		
		if(std::abs(angle - context.character.GetYaw()) > epsilon)
		{
			context.movement_controller.SetYaw(angle);
			
			return RUNNING;
		}
		
		return SUCCEEDED;
	}
	
	AITurnTowards(IPointOfInterest &p_turn_towards_position,float p_epsilon)
		:turn_towards_position(p_turn_towards_position),epsilon(p_epsilon)
	{}
	
	virtual ~AITurnTowards() override
	{}
};

#endif // AI_TURN_TOWARDS_H
