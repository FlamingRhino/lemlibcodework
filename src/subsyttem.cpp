#include "chassisstuff.cpp"

inline pros::Motor intake2(7);
 inline pros::Motor l_arm(8);
 inline pros::Motor r_arm(-3);
 inline pros::Optical Color(21);
 inline pros::adi::Pneumatics mogoal('a', false);         
 inline pros::adi::Pneumatics donker('b', false);         
 inline pros::adi::Pneumatics Sorter('h', false);   
 inline pros::Controller master(pros::E_CONTROLLER_MASTER);      
