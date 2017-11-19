#ifndef PI_CONTROLLER_H
#define PI_CONTROLLER_H

class PIController
{
private:
	float proportional;
	float integrator;
	
	float prev_error = 0.0;
	
public:
	
	float GetSignal(float error)
	{
		float signal = proportional * error - integrator * prev_error;
		
		prev_error = error;
		
		return signal;
	}
	
	PIController(float p_proportional,float p_t_exp)
		:proportional(p_proportional),integrator(p_proportional * std::exp(-p_t_exp))
	{}
};

#endif // PI_CONTROLLER_H
