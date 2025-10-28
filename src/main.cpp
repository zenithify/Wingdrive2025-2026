//includes
#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/misc.h"

//important varibles for the beginning of the code insure color sort is off the color set to the correct starting color and the selectedAutonID is getting the corect auton
bool sort = false; //false = off, true = on
bool color = false; //false = red, true = blue
bool skills = false;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * blocks All other competition modes so keep execution time low.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    // runs tast in screen.h to display robot location and selected auton on brain screen
    pros::Task screenTask(screenRunner);
}


// Runs while the robot is disabled
void disabled() {

}


//runs after initialize if the robot is connected to field control
void competition_initialize() {
}



// Runs during auto (you should not have to touch this function unless there is a major issue with the runAuto() method in autons.h)
//autonomous codes are coded in autons.h and run here
void autonomous() {runAuto(getSelectedAutonID());} //running auton code with the ID stored in screen.h

// Runs in driver control
void opcontrol() {
    sort = true; //starts color sort on for driver control
    odompickup.set_value(true);
    if(skills){ littleWill.set_value(true);}
    wing.set_value(true);
    // main driver control loop
    while (true) {
        
		// get joystick positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        // move the chassis with curvature drive
        chassis.tank(leftY, rightY);

        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
            printf ("started");
            odompickup.set_value(false);
            runAuto(getSelectedAutonID());}
			
        //forces overide to be off to spin intakes then looks for controler inputs to run intakes (method in driverFunctions.h)
		intakeControl();
        
        //flips the little will up or down depending on its current state (method in driverFunctions.h)
        littleWillFlip();
        //flips the wing descore up or down depending on its current state (method in driverFunctions.h)   
        wingFlip();
        //flips the middle goal score piston up or down depending on its current state (method in driverFunctions.h)
        middleGoalScoreFlip();

	// delay to save resources (do not delete will eat resources)
    pros::delay(10);
    
	}	
}