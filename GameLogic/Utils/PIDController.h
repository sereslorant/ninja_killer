#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

class PIDController
{
private:
	float proportional;
	float prev_error_1_prop;
	float prev_error_2_prop;
	float prev_signal_1_prop;
	float prev_signal_2_prop;
	
	
	float prev_error[2] = {0.0,0.0};
	float prev_signal[2] = {0.0,0.0};
	
public:
	
	float GetSignal(float error)
	{
		float signal = proportional * error - prev_error_1_prop * prev_error[0] + prev_error_2_prop * prev_error[1] +
											prev_signal_1_prop * prev_signal[0] - prev_signal_2_prop * prev_signal[1];
		
		prev_error[1] = prev_error[0];
		prev_error[0] = error;
		
		prev_signal[1] = prev_signal[0];
		prev_signal[0] = signal;
		
		return signal;
	}
	
	PIDController(float p_proportional,float p_ti_exp,float p_td1_exp,float p_td2_exp)
		:proportional(p_proportional),
		prev_error_1_prop(p_proportional * (std::exp(-p_ti_exp) + std::exp(-p_td1_exp))),
		prev_error_2_prop(p_proportional * std::exp(-p_ti_exp) * std::exp(-p_td1_exp)),
		prev_signal_1_prop(1.0 + std::exp(-p_td2_exp)),
		prev_signal_2_prop( std::exp(-p_td2_exp))
	{}
};

#endif // PID_CONTROLLER_H
