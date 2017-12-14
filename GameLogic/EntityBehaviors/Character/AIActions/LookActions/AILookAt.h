#ifndef AI_LOOK_AT_BEHAVIOR_H
#define AI_LOOK_AT_BEHAVIOR_H

#include <EntityBehaviors/BehaviorTree/IBehavior.h>
#include <EntityBehaviors/Character/AIController/AIContext.h>
#include <EntityBehaviors/IPointOfInterest.h>

class AILookAt : public IBehavior<AIContext>
{
private:
	IPointOfInterest &target_position;
	
public:
	
	virtual BehaviorState Run(AIContext &context) override
	{
		btVector3 dir = target_position.GetPosition() - context.self.GetPosition();
		if(dir.length2() > 0.0)
		{
			dir.normalize();
			context.look_controller.SetLookDirection(dir);
			
			return SUCCEEDED;
		}
		
		context.look_controller.SetLookDirection({0.0,0.0,1.0});
		return FAILED;
	}
	
	AILookAt(IPointOfInterest &p_target_position)
		:target_position(p_target_position)
	{}
	
	virtual ~AILookAt() override
	{}
};

#endif // AI_LOOK_AT_BEHAVIOR_H
