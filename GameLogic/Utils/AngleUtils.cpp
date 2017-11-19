
#include "AngleUtils.h"

#include <cmath>

float TransformAngle(float angle)
{
	if(angle > 2.0 * PI)
	{
		unsigned int div = angle / (2.0 * PI);
		return (angle - div * 2.0 * PI);
	}
	
	if(angle < 0.0)
	{
		unsigned int div = std::abs(angle / (2.0 * PI));
		return 2.0 * PI + (angle + div * 2.0 * PI);
	}
	
	return angle;
}

float GetDeltaAngle(float current_angle,float target_angle)
{
	current_angle = TransformAngle(current_angle);
	target_angle = TransformAngle(target_angle);
	
	float delta_angle = target_angle - current_angle;
	
	if(delta_angle > PI)
	{
		delta_angle = -2.0 * PI  + delta_angle;
	}
	
	if(delta_angle < -PI)
	{
		delta_angle = 2.0 * PI + delta_angle;
	}
	
	return delta_angle;
}
