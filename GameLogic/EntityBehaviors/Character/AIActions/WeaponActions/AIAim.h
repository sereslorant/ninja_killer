#ifndef AI_AIM_H
#define AI_AIM_H

#include <EntityBehaviors/BehaviorTree/IBehavior.h>
#include <EntityBehaviors/Character/AIController/AIContext.h>

class AIAim : public IBehavior<AIContext>
{
public:
	
	virtual BehaviorState Run(AIContext &context) override
	{
		context.weapon_controller.SetState(
			true,
			context.weapon_controller.IsShooting(),
			context.weapon_controller.IsMelee()
		);
		
		return SUCCEEDED;
	}
	
	AIAim()
	{}
	
	virtual ~AIAim() override
	{}
};

#endif // AI_AIM_H
