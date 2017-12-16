
#include <iostream>

#include <GameLogic/Utils/AngleUtils.h>

int main(int argc, char *argv[])
{
	std::cout << "Transform angle test:" << std::endl;
	
	{
		float test_angle = 2.0 * PI + PI/6.0;
		float expected = PI / 6.0;
		
		std::cout << expected << ";" << TransformAngle(test_angle) << std::endl;
	}
	
	{
		float test_angle = - PI/6.0;
		float expected = 2.0 * PI - PI / 6.0;
		
		std::cout << expected << ";" << TransformAngle(test_angle) << std::endl;
	}
	
	{
		float test_angle = -2.0 * PI - PI/6.0;
		float expected = 2.0 * PI - PI / 6.0;
		
		std::cout << expected << ";" << TransformAngle(test_angle) << std::endl;
	}
	
	{
		float test_angle = 6.0 * PI + PI/6.0;
		float expected = PI / 6.0;
		
		std::cout << expected << ";" << TransformAngle(test_angle) << std::endl;
	}
	
	std::cout << "Get delta angle test:" << std::endl;
	
	{
		float current_angle = PI / 4.0;
		float target_angle =  PI / 2.0;
		
		float expected = PI / 4.0;
		float delta_angle = GetDeltaAngle(current_angle,target_angle);
		
		std::cout << expected << ";" << delta_angle << std::endl;
	}
	
	{
		float current_angle = PI / 4.0;
		float target_angle = -PI / 6.0;
		
		float expected = -PI / 6.0 - PI / 4.0;
		float delta_angle = GetDeltaAngle(current_angle,target_angle);
		
		std::cout << expected << ";" << delta_angle << std::endl;
	}
	
	{
		float current_angle = -PI / 6.0;
		float target_angle = PI / 4.0;
		
		float expected = PI / 6.0 + PI / 4.0;
		float delta_angle = GetDeltaAngle(current_angle,target_angle);
		
		std::cout << expected << ";" << delta_angle << std::endl;
	}
	
	{
		float current_angle = PI;
		float target_angle = -PI / 6.0;
		
		float expected = PI - PI / 6.0;
		float delta_angle = GetDeltaAngle(current_angle,target_angle);
		
		std::cout << expected << ";" << delta_angle << std::endl;
	}
	
	{
		float current_angle = PI + PI/6.0;
		float target_angle = -PI / 6.0;
		
		float expected = PI - PI / 6.0 - PI/6.0;
		float delta_angle = GetDeltaAngle(current_angle,target_angle);
		
		std::cout << expected << ";" << delta_angle << std::endl;
	}
	
	return 0;
}
