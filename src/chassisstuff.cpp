#include "robodash/api.h"
#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep

pros::MotorGroup left_motor_group({-10, 9, -17}, pros::MotorGearset::blue); // left motors on ports 1, 2, 3
pros::MotorGroup right_motor_group({20, -19, 18}, pros::MotorGearset::blue); // right motors on ports 4, 5, 6
 


lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              11.85, // 10 inch track width
                              lemlib::Omniwheel::OLD_325, // using new 4" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

//Imu port
pros::Imu imu(5);

// horizontal tracking wheel encoder
//ros::Rotation horizontal_encoder(20);
// vertical tracking wheel encoder
//pros::adi::Encoder vertical_encoder('C', 'D', true);
// horizontal tracking wheel
//lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275, -5.75);
// vertical tracking wheel
//emlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_275, -2.5);

// odometry settings
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);




// lateral PID controller
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              5, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);


// angular PID controller
lemlib::ControllerSettings angular_controller(1.98, // proportional gain (kP)
                                              0.0005, // integral gain (kI)
                                              80, // derivative gain (kD)
                                              3, // anti windup
                                              2, // small error range, in degrees
                                              75, // small error range timeout, in milliseconds
                                              5, // large error range, in degrees
                                              400, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);


// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain,
                        lateral_controller,
                        angular_controller,
                        sensors,
                        &throttle_curve, 
                        &steer_curve
);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */