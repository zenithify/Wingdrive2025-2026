#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/motors.hpp"

//create motors and sensors here
pros::Motor           frontStage    (-13, pros::MotorGearset::blue); // front intake motor
pros::Motor           hood          (18, pros::MotorGearset::blue); // hood motor
pros::adi::DigitalOut littleWill    ('A',false); //piston for the little will mechanism
pros::adi::DigitalOut midScore      ('A',false);
pros::Optical         blockColor    (3); // optical sensor on port 3
pros:: Distance       blockDistance (4); // distance sensor on port 4
pros:: Distance       DR (5);
pros:: Distance       DL (6);
pros:: Distance       DFR (7);
pros:: Distance       DFL (8);
pros:: Distance       DB (9);

// controller
pros::Controller controller (pros::E_CONTROLLER_MASTER);

//bellow is all for chassis/odom


// motor groups for chassis
pros::MotorGroup leftMotors  ({-2, -11, -12},pros::MotorGearset::blue); // left motor group - ports 3 (reversed), 4, 5 (reversed)
pros::MotorGroup rightMotors ({10, 19, 17}, pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)

// Inertial Sensor on port 10
pros::Imu imu (10);

// tracking wheel encoders
pros::Rotation horizontalEnc (20);
pros::Rotation verticalEnc   (-11);

//tracking wheels
lemlib::TrackingWheel horizontal (&horizontalEnc, lemlib::Omniwheel::NEW_275, -5.75);
lemlib::TrackingWheel vertical   (&verticalEnc, lemlib::Omniwheel::NEW_275, -2.5);

// drivetrain settings
lemlib::Drivetrain         drivetrain        (	 &leftMotors, // left motor group
                              	                &rightMotors, // right motor group
                              	                 10, // 10 inch track width
                                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              			                450, // drivetrain rpm is 360
                                            2 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController  (			  10, // proportional gain (kP)
                                            			  0, // integral gain (kI)
                                            			  3, // derivative gain (kD)
                                            	 3, // anti windup
                                            	  1, // small error range, in inches
                                           100, // small error range timeout, in milliseconds
                                            	  3, // large error range, in inches
                                           500, // large error range timeout, in milliseconds
                                            			20 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController (			  2, // proportional gain (kP)
                                             			  0, // integral gain (kI)
                                             			  10, // derivative gain (kD)
                                             	 3, // anti windup
                                             	  1, // small error range, in degrees
                                           100, // small error range timeout, in milliseconds
                                             	  3, // large error range, in degrees
                                           500, // large error range timeout, in milliseconds
                                             		    0 // maximum acceleration (slew)
);

// sensors for odometry
lemlib::OdomSensors        sensors           (     &vertical, // vertical tracking wheel
                              nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            		&imu // inertial sensor
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve     throttleCurve     (      3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                         1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve     steerCurve        (      3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                      1.019 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis (drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);