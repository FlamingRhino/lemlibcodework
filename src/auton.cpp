#include "arm.cpp"

//Assets
ASSET(jerryio_txt);
ASSET(statesigwinp_txt);
ASSET(sigawppath1_txt);
ASSET(sigawppath2_txt);
ASSET(sigawppath3_txt);
ASSET(sigawppath4_txt);


inline void sigawp(){
    chassis.setPose(-61, 13, 30);
    target = 1875;
    pros::delay(200);
    target = 20;
    chassis.follow(sigawppath1_txt, 15 , 8000, true);
    mogoal.extend();
    intake2.move(127);
    chassis.follow(sigawppath2_txt, 15 , 8000);
    mogoal.retract();
    chassis.follow(sigawppath3_txt, 15 , 8000, false);
    mogoal.extend();
    chassis.follow(sigawppath4_txt, 15 , 8000);
}

inline void goalrush(){
    
}

inline void skills(){
    
}

