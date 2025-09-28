#include "lemlib/api.hpp" // IWYU pragma: keep
#include "autons.h"

int selectedAutonID = redLeft.getid();
int maxAutonID = 4; //default auton ID, will be changed by auton selector in future

//returns the selected auton ID for use in main.cpp
static int getSelectedAutonID(){return selectedAutonID;}

//code for button presses on the lcd screen
static void onLeftButton(){
selectedAutonID--;
if (selectedAutonID <= 0){selectedAutonID = maxAutonID;}
}

//code for button presses on the lcd screen
static void onRightButton(){
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

			pros::lcd::print(4, "Auton: %s", idToName(selectedAutonID));
            pros::lcd::print(6, "Left motor temp:  %ic (55c 1/2 power)", getLeftMotorTemp()); // selected auton name
            pros::lcd::print(7, "Right motor temp: %ic (55c 1/2 power)", getRightMotorTemp()); // selected auton name
            pros::lcd::register_btn0_cb(onLeftButton);
            pros::lcd::register_btn2_cb(onRightButton);
        
        // delay to save resources (do not delete will eat resources)
        pros::delay(50);
        }
}