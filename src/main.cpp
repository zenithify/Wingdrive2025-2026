//includes
#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/misc.h"
#include "pros/motors.hpp"
#include "8448G/autons.h"

//important varibles for the beginning of the code insure color sort is off the color set to the correct starting color and the selectedAutonID is getting the corect auton
bool sort = false; //false = off, true = on
bool color = false; //false = red, true = blue
int selectedAutonID = example.getid(); //default auton ID, will be changed by auton selector in future

//converts the ID to a name for display on the brain screen
std::string selectedAutonName =idToName(selectedAutonID);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * blocks All other competition modes so keep execution time low.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    // thread to for brain screen and position logging
    pros::Task screenTask([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());

			pros::lcd::print(3, "auton: %s", selectedAutonName); // heading
        // delay to save resources (do not delete will eat resources)
        pros::delay(50);
        }
    });
}


// Runs while the robot is disabled
void disabled() {

}


//runs after initialize if the robot is connected to field control
void competition_initialize() {
}



// Runs during auto (you should not have to touch this function unless there is a major issue with the runAuto() method in autons.h)
//autonomous codes are coded in autons.h and run here
void autonomous() {
   /**
	* runAuto("Right Side"); //example of running auton code named "Right Side"
	*to edit autos, go to autons.h
    */

    runAuto(selectedAutonID); //running auton code with the ID stored in selectedAutonID
}

// Runs in driver control
void opcontrol() {
    sort = true; //starts color sort on for driver control
    // main driver control loop
    while (true) {
        
		// get joystick positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        // move the chassis with curvature drive
        chassis.tank(leftY, rightY);
			
        //forces overide to be off to spin intakes then looks for controler inputs to run intakes (method in driverFunctions.h)
		if(overide == false){intakeControl();}
        
        //flips the little will up or down depending on its current state (method in driverFunctions.h)
        littleWillFlip();

	// delay to save resources (do not delete will eat resources)
    pros::delay(10);
	}	
}