#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/misc.h"
#include "pros/motors.hpp"
#include "subsystems.h"

//intake control
static void intakeControl(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    hood.move(0);
    frontStage.move(127);
    midScore.set_value(false);
    }
    //score on high goal
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    hood.move(127);
    frontStage.move(127);
    midScore.set_value(false);
    } 
    // score mid goal
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    hood.move(63);
    frontStage.move(127);
    midScore.set_value(true);
    }
    //outtake/low goal
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    hood.move(-127);
    frontStage.move(-127);
    midScore.set_value(false);
    } 
    //stop
    else{
    hood.move(0);
    frontStage.move(0);
    midScore.set_value(false);
    }
}

static void littleWillFlip(){
static bool LW { false };
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
    littleWill.set_value(!LW);    //When false go to true and in reverse
    LW = !LW;    //Flip the toggle to match piston state
    }
    }

    static void wingFlip(){
static bool W { false };
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
    wing.set_value(!W);    //When false go to true and in reverse
    W = !W;    //Flip the toggle to match piston state
    }
}
    static void middleGoalScoreFlip(){
static bool MS { false };
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
    midScore.set_value(!MS);    //When false go to true and in reverse
    MS = !MS;    //Flip the toggle to match piston state
    }
}
    static void MGDescoreFlip(){
static bool MG { false };
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
    MGDescore.set_value(!MG);    //When false go to true and in reverse
    MG = !MG;    //Flip the toggle to match piston state
    }
}