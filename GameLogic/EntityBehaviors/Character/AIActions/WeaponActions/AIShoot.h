#ifndef AI_SHOOT_H
#define AI_SHOOT_H

#include <EntityBehaviors/BehaviorTree/IBehavior.h>
#include <EntityBehaviors/Character/AIController/AIContext.h>

class AIShoot : public IBehavior<AIContext>
{
public:
	
	virtual BehaviorState Run(AIContext &context) override
	{
		context.weapon_controller.SetState(
			context.weapon_controller.IsAiming(),
			true,
			context.weapon_controller.IsMelee()
		);
		
		return SUCCEEDED;
	}
	
	AIShoot()
	{}
	
	virtual ~AIShoot() override
	{}
};

#endif // AI_SHOOT_H
