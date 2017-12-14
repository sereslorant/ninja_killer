#ifndef AI_MELEE_H
#define AI_MELEE_H

#include <EntityBehaviors/BehaviorTree/IBehavior.h>
#include <EntityBehaviors/Character/AIController/AIContext.h>

class AIMelee : public IBehavior<AIContext>
{
public:
	
	virtual BehaviorState Run(AIContext &context) override
	{
		context.weapon_controller.SetState(
			context.weapon_controller.IsAiming(),
			context.weapon_controller.IsShooting(),
			true
		);
		
		return SUCCEEDED;
	}
	
	AIMelee()
	{}
	
	virtual ~AIMelee() override
	{}
};

#endif // AI_MELEE_H
