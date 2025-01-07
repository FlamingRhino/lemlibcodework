
#include "pros/misc.h"
#include "auton.cpp"



rd::Selector selector({
    {"red signature event awp auton", sigawp},
    {"Simple auton", goalrush},
    {"Good auton", skills},
});

//console thing
rd::Console console;




void initialize() {
    chassis.calibrate(); // calibrate sensors
    // print position to brain screen
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    pros::Task colorTASK(colortask);
	pros::Task armTASK(armpidthing);
	Color.set_led_pwm(100);


	selector.on_select([](std::optional<rd::Selector::routine_t> routine) {
		if (routine == std::nullopt) {
			std::cout << "No routine selected" << std::endl;
		} else {
			std::cout << "Selected Routine: " << routine.value().name << std::endl;
		}
	});


    };


/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

 
void autonomous() {

	selector.run_auton();

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
pros::Controller controller(pros::E_CONTROLLER_MASTER);

void opcontrol() {

    // loop forever
	 // autonomous();

	  int nickthing = 0;
	  int countthing = 0;

    while (true) {

		    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == 1){
      			intake2.move(127);
    		}
    			//intake revse
			 if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == 1){
   			   if (countthing <10){
				intake2.move(0);
			   }
				 if (countthing > 10) {
					intake2.move(-127);
			   }
			   countthing++;
    		}else{
				if (countthing > 0){
				countthing = 0;
				intake2.move(0);

				}
			}


		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
     	 mogoal.extend();
   		 }
   		 if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    	  mogoal.retract();
    	}
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
     	 donker.extend();
   		 }
   		 if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
    	  donker.retract();
    	}

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
			if (nickthing == 0){
				target = 275;
				nickthing = 1;
			} else{
				target = 1600;
				nickthing = 0;
			}
			
		}

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
			target = 10;
			nickthing = 0;
		}

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
			target = 1875;
	
		}

        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot
        chassis.arcade(leftY, rightX);

        // delay to save resources
        

		if(!pros::competition::is_connected()){
			if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT) & master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
				autonomous();
			}
		}

		pros::delay(25);

		}




}

