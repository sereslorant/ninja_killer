#ifndef TRACK_CHARACTER_BEHAVIOR_H
#define TRACK_CHARACTER_BEHAVIOR_H

#include "PointAroundCharacter.h"
#include "CharacterLookAtPoint.h"

#include "../CameraMove.h"
#include "../CameraLookAt.h"

#include <EntityBehaviors/BehaviorTree/Composites/ParallelBehavior.h>

class TrackCharacterBehavior : public IBehavior<CameraContext>
{
public:
	PointAroundCharacter point_above_shoulder;
	CharacterLookAtPoint look_at_point;
	
private:
	CameraMove follow_character;
	CameraLookAt look_where_character_looks;
	
	ParallelBehavior<CameraContext> follow_and_lookat;
	
public:
	
	virtual BehaviorState Run(CameraContext &context) override
	{
		return follow_and_lookat.Run(context);
	}
	
	TrackCharacterBehavior(/*Camera &p_camera,*/Character &p_character)
		:point_above_shoulder(p_character,0.0 + PI/2.0 + 3.0*PI/8.0,17.5,7.0),look_at_point(p_character),
		follow_character(/*p_camera,*/point_above_shoulder),look_where_character_looks(/*p_camera,*/look_at_point),
		follow_and_lookat({{&follow_character,&look_where_character_looks}})
	{}
	
	virtual ~TrackCharacterBehavior() override
	{}
};

#endif // TRACK_CHARACTER_BEHAVIOR_H
