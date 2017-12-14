#ifndef AI_GOTO_BEHAVIOR_H
#define AI_GOTO_BEHAVIOR_H

#include <EntityBehaviors/BehaviorTree/IBehavior.h>
#include <EntityBehaviors/Character/AIController/AIContext.h>
#include <EntityBehaviors/IPointOfInterest.h>

class AIGoto : public IBehavior<AIContext>
{
private:
	IPointOfInterest &target_position;
	float radius;
	
public:
	
	virtual BehaviorState Run(AIContext &context) override
	{
		btVector3 dir = target_position.GetPosition() - context.self.GetPosition();
		if(dir.length2() > radius*radius)
		{
			context.movement_controller.SetVelocity(dir);
			
			return RUNNING;
		}
		
		context.movement_controller.SetVelocity({0.0,0.0,0.0});
		return SUCCEEDED;
	}
	
	AIGoto(IPointOfInterest &p_target_position,float p_radius)
		:target_position(p_target_position),radius(p_radius)
	{}
	
	virtual ~AIGoto() override
	{}
};

#endif // AI_GOTO_BEHAVIOR_H
