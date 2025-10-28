#include "lemlib/api.hpp" // IWYU pragma: keep
#include "autons.h"
#include "liblvgl/llemu.hpp"

int selectedAutonID = redLeft2.getid();
int maxAutonID = 5; //default auton ID, will be changed by auton selector in future;

//returns the selected auton ID for use in main.cpp
static int getSelectedAutonID(){return selectedAutonID;}

//codes for button presses on the lcd screen
static void DecreaseAuton(){
selectedAutonID--;
if (selectedAutonID <= 0){selectedAutonID = maxAutonID;}
}

static void increaseAuton(){
selectedAutonID++;
if (selectedAutonID > maxAutonID){selectedAutonID = 1;}
}

static void screenRunner(){
            while (true) {
            
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // prints selected auton name to the brain screen
			pros::lcd::print(4, "Auton: %s", idToName(selectedAutonID));
            //prints motor temps to brain screen
            pros::lcd::print(6, "Left motors temp:  %ic", getLeftMotorTemp()); // selected auton name
            pros::lcd::print(7, "Right motors temp: %ic", getRightMotorTemp());
            //pros::lcd::print(6, "%i", getblockCount());
            //pros::lcd::print(7, "%i", blockDistance.get());
            //auton selector button code
            pros::lcd::register_btn0_cb(DecreaseAuton);
            pros::lcd::register_btn2_cb(increaseAuton);
            
        // delay to save resources (do not delete will eat resources)
        pros::delay(50);
        }
}