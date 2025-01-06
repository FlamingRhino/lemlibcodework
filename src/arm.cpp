#include "mycolorsorter.cpp"

inline lemlib::PID arm_pid(0.45, 0, 0);
inline float target = 0;
inline float output = arm_pid.update(target - l_arm.get_position());

inline void armpidthing(){
    
    while (true) {
        output = arm_pid.update(target - l_arm.get_position());
		l_arm.move(output);
		r_arm.move(output);

    }
    
    



}

