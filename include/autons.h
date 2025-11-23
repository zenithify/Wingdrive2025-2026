#include <string>
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "autonFunctions.h"
#include "lemlib-tarball/api.hpp"
int timer = 0;
static int getTimer(){return timer;}
// Replace my_paths.txt with your actual filename
// "." is replaced with "_" to overcome c++ limitations
ASSET(autontest1_txt);
ASSET(blueleft_txt);
// Create the decoder
lemlib_tarball::Decoder decoderAutonTest1(autontest1_txt);
lemlib_tarball::Decoder decoderBlueLeft(blueleft_txt);

//for use in auton adjuster in screen.h
bool oneblock = true;
static void changeOneBlock(){oneblock = !oneblock;}

//creates an auton class to store auton names and ids for future auton selector implimentation
class auton {
public: 
std::string name;
int id;

//creating the getid() method to return the id of the auton object
int getid(){return id;}

//creating the getname() method to return the name of the auton object
std::string getname(){return name;}

//constructor overloads
auton(std::string name){
this->name = name;
}

auton(int id){
this->id = id;
}

auton(int id, std::string name){
this->name = name;
this->id = id;
}
};

//create auton objects here
auton example           (0, "Example");
auton redLeft           (1, "Red Left / Blue Right");
auton blueLeftElims2    (2, "Blue Left / Red Right: Elims");
auton blueLeftQuals     (3, "Blue Left / Red Right: Quals");
auton SIGAWP            (4,"Sig AWP");
auton SkillsSafe        (5, "skills");
auton SkillsHailMary    (6, "skills hail mary");
auton blueLeftElims     (7, "Blue Left / Red Right: Elims");
auton blueLeftSAWP      (8, "Blue Left / Red Right: Solo AWP");



//gets name from and ID
static std::string idToName(int id){
//add if statements here for autos    
if (id == example.getid())       {return example.getname();}
if (id == blueLeftElims.getid()) {return blueLeftElims.getname();}
if (id == blueLeftQuals.getid()) {return blueLeftQuals.getname();}
if (id == blueLeftSAWP.getid())  {return blueLeftSAWP.getname();}
if (id == redLeft.getid())       {return redLeft.getname();}
if (id == SkillsSafe.getid())    {return SkillsSafe.getname();}
if (id == SkillsHailMary.getid()) {return SkillsHailMary.getname();}
if (id == blueLeftElims2.getid()) {return blueLeftElims2.getname();}
if (id == SIGAWP.getid()) {return SIGAWP.getname();}
else {return "";}
}


// Create a decoder for the tarball

// a method that runs off of an integer id for easy future implimentation of an auton selector
static void runAuto(int id){
    
    //example of creating a auton routine based on the example auton abject created above
    if (id == example.getid()){
    blockCounter(4, 30000);
    }
    else if (id == blueLeftQuals.getid()){
    
    chassis.setPose(0, 0, 250);

    // gets blocks from the middle
    frontStage.move(127);
    chassis.moveToPoint(-29, -8, 1000,{.maxSpeed =  70});

    //get blocks from second middle goal
    chassis.turnToHeading(215, 2000,{},true);
    chassis.moveToPoint(-39, -31.5,  1000,{.maxSpeed =  70});

    //goes to middle goal and scores 4 blocks
    chassis.moveToPose(-44, 8, 135, 2000,{.forwards=false, .maxSpeed = 70}, false);

    hood.move(63);
    frontStage.move(127);
    midScore.set_value(true);
    pros::delay(500);
    hood.move(-127);
    frontStage.move(-127);
    pros::delay(100);
    hood.move(0);
    midScore.set_value(false);
    

frontStage.move(127);
 hood.move(0);
    //Goes to line up for match loader
    chassis.moveToPoint(-1.5, -30.5, 2000,{.maxSpeed = 50});
    chassis.turnToHeading(90, 2000,{},true);

    //drops little will and gets blocks out from match loader
    littleWill.set_value(true);
    chassis.moveToPoint(13.5, -30.5, 2000, {.maxSpeed = 50., .minSpeed = 50 });
    pros::delay(1000);
    frontStage.move(127);
    pros::delay(200);
    frontStage.move(0);

    //backs up and lines up for scoring
    frontStage.move(127);
    chassis.moveToPoint(-17, -31.5, 2000,{ .forwards = false, .maxSpeed =70}, false);
    frontStage.move(-127);
    pros::delay(100);
    frontStage.move(127);
    hood.move(127);
    pros::delay(3000);
    
    }
    else if (id == blueLeftSAWP.getid()){
    timer = pros::millis();
    chassis.setPose(0, 0, 250);

    // gets blocks from the middle
    frontStage.move(127);
    chassis.moveToPoint(-29, -8, 1000,{.maxSpeed =  90});

    chassis.turnToHeading(135, 500,{},true);

    //goes to middle goal and scores 4 blocks
    chassis.moveToPose(-43, 8, 135, 1000,{.forwards=false,  .maxSpeed = 90, .minSpeed = 50}, false);

    hood.move(63);
    frontStage.move(127);
    midScore.set_value(true);
    pros::delay(500);
    frontStage.move(-127);
    pros::delay(100);
    hood.move(0);
    midScore.set_value(false);
    

frontStage.move(127);
 hood.move(0);
    //Goes to line up for match loader
    chassis.moveToPoint(-1.5, -30, 2000,{.maxSpeed = 70});
    chassis.turnToHeading(90, 500,{},true);

    //drops little will and gets blocks out from match loader
    littleWill.set_value(true);
    chassis.moveToPoint(14, -30, 2000, {.maxSpeed = 70., .minSpeed = 60 });
    pros::delay(1250);
    frontStage.move(127);

    //backs up and lines up for scoring
    frontStage.move(127);
    chassis.moveToPoint(-17, -31.5, 2000,{ .forwards = false, .maxSpeed =70}, false);
    blockCounter(3, 2000);
    hood.move(0);
    //move to other side
    littleWill.set_value(false);
    frontStage.move(127);
    chassis.moveToPoint(-10, -31.5, 1000,{}, false);
    chassis.moveToPoint(-22, 33, 2000,{.maxSpeed = 100}, false);

    // lines up for scoring
    chassis.turnToHeading(45, 250,{},true);
    chassis.moveToPoint(-8, 69.5, 2000,{.maxSpeed = 90,}, false);
    chassis.turnToHeading(90, 500,{},true);
    chassis.moveToPoint(-30, 70, 2000,{.forwards= false,.maxSpeed = 90}, false);
    hood.move(127);
    frontStage.move(127);
    pros::delay(2000);
    timer = ((pros::millis() - timer)/1000);


    }
    else if (id == SkillsSafe.getid()){
        chassis.setPose(0, 0, 287.5);
        wing.set_value(true);
         littleWill.set_value(true);

        frontStage.move(127);
        //move to matchloader
        chassis.moveToPose(-2, 33.5, 0, 2000,{},false);
        //gets blocks out from match loader
        chassis.turnToHeading(90, 2000);
        chassis.moveToPoint(15, 33.5, 1500, { .maxSpeed = 70, .minSpeed = 60},false);
        pros::delay(2500);

        // move to tube and score
        chassis.moveToPoint(-19, 35.5, 2000,{.forwards = false, .maxSpeed =70}, false);
        frontStage.move(-127);
        pros::delay(150);
        hood.move(127);
        frontStage.move(127);
        pros::delay(2500);

        //move to 2nd matchloader
        chassis.moveToPoint(-1, 34.5, 2000,{.maxSpeed = 90,}, true);
        chassis.turnToHeading(180, 1000);
        chassis.moveToPoint(-1, -61, 3000,{.maxSpeed = 90,}, false);
        chassis.turnToHeading(90,2000);
        hood.move(0);
        chassis.moveToPoint(24, -61, 2000,{.maxSpeed = 70, .minSpeed = 60},false);
        pros::delay(2500);
        
        // go to second tube and score
        chassis.moveToPoint(-15.5, -60, 2000,{.forwards= false, .maxSpeed = 70}, false);
        frontStage.move(-127);
        pros::delay(150);
        hood.move(127);
        frontStage.move(127);
        pros::delay(2500);
        
        // go to 3rd match loader
        chassis.moveToPoint(5, -58, 2000,{.maxSpeed = 90, .earlyExitRange = 2}, true);
        chassis.turnToHeading(315, 500);
        littleWill.set_value(false);
        chassis.moveToPoint(-14, -42,2000,{.maxSpeed = 90, .minSpeed = 50, .earlyExitRange = 2}, false);
         chassis.turnToHeading(270, 500);
        frontStage.move(127);
        chassis.moveToPoint(-70, -42, 1500,{.maxSpeed = 90}, true);
        chassis.moveToPoint(-86, -53, 2000,{.maxSpeed = 70}, false);
        chassis.turnToHeading(270, 500);
        hood.move (0);

        // get blocks out of 3rd match loader
        littleWill.set_value(true);
        chassis.moveToPoint(-102, -53, 2000,{ .maxSpeed = 70, .minSpeed = 50}, true);
        pros::delay(2500);

        //score in long tube again
        chassis.moveToPoint(-70, -54, 2000,{.forwards= false, .maxSpeed = 70}, false);
        frontStage.move(-127);
        pros::delay(150);
        hood.move(127);
        frontStage.move(127);
        pros::delay(2500);

        //move to last match loader
        chassis.moveToPoint(-84, -54, 3000,{.maxSpeed = 90, . earlyExitRange = 4}, true);
        chassis.turnToHeading(0, 2000);
        chassis.moveToPoint(-84, 37.5, 3000, {.maxSpeed = 90}, false);
        chassis.turnToHeading(270, 500);
        

        //get blocks out of last match loader
        hood.move(0);
        chassis.moveToPoint(-102, 37.5, 2000, {.maxSpeed = 70, .minSpeed = 50}, false);
        pros::delay(2000);

        // score in last tube
        chassis.moveToPoint(-70, 37, 1500, {.forwards = false, .maxSpeed = 70, .minSpeed = 50}, false);
        hood.move(127);
        pros::delay(2000);

        // move to park
        littleWill.set_value(false);
        frontStage.move(127);
        chassis.moveToPoint(-80, 36, 3000, {.maxSpeed = 90, .minSpeed = 50, .earlyExitRange = 4}, false);
        chassis.moveToPoint(-70, 12, 3000, {.maxSpeed = 100, .minSpeed = 60, .earlyExitRange = 6}, false);
        chassis.moveToPoint(-45, 12, 3000, {.maxSpeed = 100, .minSpeed = 60, .earlyExitRange = 6}, false);
        chassis.moveToPoint(0, -21, 4000, {.maxSpeed = 90}, false);
        chassis.turnToHeading(90, 2000,{}, false);
        odompickup.set_value(true);
        leftMotors.move(100);
        rightMotors.move(100);

    }
    else if (id == SkillsHailMary.getid()) {
    
        chassis.setPose(0, 0, 287.5);
        wing.set_value(true);
         littleWill.set_value(true);

        frontStage.move(127);
        //move to matchloader
        chassis.moveToPose(-2, 34, 0, 2000,{},false);
        //gets blocks out from match loader
        chassis.turnToHeading(90, 2000);
        chassis.moveToPoint(15, 34.5, 1500, { .maxSpeed = 70, .minSpeed = 60},false);
        pros::delay(2500);

        // move to tube and score
        chassis.moveToPoint(-19, 35.5, 2000,{.forwards = false, .maxSpeed =70}, false);
        frontStage.move(-127);
        pros::delay(150);
        blockCounter(7, 2500);

        //move to 2nd matchloader
        chassis.moveToPoint(-1, 34.5, 2000,{.maxSpeed = 90,}, true);
        chassis.turnToHeading(180, 2000);
        chassis.moveToPoint(-1, -61, 3000,{.maxSpeed = 90,}, false);
        chassis.turnToHeading(90,2000);
        hood.move(0);
        chassis.moveToPoint(24, -61, 2000,{.maxSpeed = 70, .minSpeed = 60},false);
        pros::delay(2500);
        
        // go to second tube and score
        chassis.moveToPoint(-14, -60.5, 2000,{.forwards= false, .maxSpeed = 70}, false);
        frontStage.move(-127);
        pros::delay(200);
        blockCounter(6, 2500);
        
        // go to 3rd match loader
        chassis.moveToPoint(5, -58, 2000,{.maxSpeed = 90, .earlyExitRange = 2}, true);
        chassis.turnToHeading(315, 2000);
        littleWill.set_value(false);
        chassis.moveToPose(-42, -45, 270, 2000,{.maxSpeed = 90, .minSpeed = 50, .earlyExitRange = 2}, false);
        frontStage.move(127);
        chassis.moveToPoint(-70, -47, 1250,{.maxSpeed = 90}, true);
        chassis.moveToPoint(-86, -60.5, 2000,{.maxSpeed = 70}, false);
        chassis.turnToHeading(270, 2000);
        hood.move (0);

        // get blocks out of 3rd match loader
        littleWill.set_value(true);
        chassis.moveToPoint(-99, -60.5, 2000,{ .maxSpeed = 70, .minSpeed = 50}, true);
        blockCounter(3, 2500);

        //score in long tube again
        chassis.moveToPoint(-70, -62.5, 2000,{.forwards= false, .maxSpeed = 70}, false);
        frontStage.move(-127);
        pros::delay(200);
        blockCounter(6, 2500);

        //move to last match loader
        chassis.moveToPoint(-84, -62.5, 3000,{.maxSpeed = 90, . earlyExitRange = 4}, true);
        chassis.turnToHeading(0, 2000);
        chassis.moveToPoint(-84, 34, 3000, {.maxSpeed = 90}, false);
        chassis.turnToHeading(270, 2000);
        hood.move(127);

        //get blocks out of last match loader
        chassis.moveToPoint(-99, 34, 2500, {.maxSpeed = 70, .minSpeed = 50}, false);
        blockCounter(3, 2500);

        // score in the long tube again (last)
        chassis.moveToPoint(-70, 34.5, 3000, {.forwards= false, .maxSpeed = 70}, false);
        frontStage.move(-127);
        pros::delay(100);
        hood.move(127);
        frontStage.move(127);
        blockCounter(3, 2500);

        // move to park
        littleWill.set_value(false);
        frontStage.move(127);
        chassis.moveToPoint(-78, 34, 3000, { .maxSpeed = 90, .minSpeed = 50, .earlyExitRange = 4}, false);
        chassis.moveToPoint(-50, 16, 3000, {.maxSpeed = 100, .minSpeed = 60, .earlyExitRange = 6}, false);
        chassis.moveToPoint(2, -14, 4000, {.maxSpeed = 90}, false);
        chassis.turnToHeading(90, 2000,{}, false);
        odompickup.set_value(true);
        leftMotors.move(100);
        rightMotors.move(100);

    }
    else if (id == blueLeftElims2.getid()){
    chassis.setPose(0, 0, 250);

    // gets blocks from the middle
    frontStage.move(127);
    chassis.moveToPoint(-29, -10, 2000,{.maxSpeed =  90});

    //get blocks from second middle
    chassis.turnToHeading(215, 1000,{},true);
    chassis.moveToPoint(-39, -31,  2000,{.maxSpeed =  70});

    // go to goal
    chassis.moveToPoint(-29, -8, 1000,{.forwards = false, .maxSpeed =  90});
    chassis.turnToHeading(135, 2000);

    //Go line up for goal
    chassis.moveToPoint(-1.5, -33, 2000,{ .maxSpeed = 90,});
    chassis.turnToHeading(90, 1000,{},true);

    //backs up and lines up for scoring
    frontStage.move(127);
    chassis.moveToPoint(-19, -33, 1000,{ .forwards = false, .maxSpeed =70}, false);
    frontStage.move(-127);
    pros::delay(50);
    frontStage.move(127);
    hood.move(127);
    pros::delay(2000);
    hood.move(0);

    //drops little will and gets blocks out from match loader
    littleWill.set_value(true);
    chassis.moveToPoint(14, -30.5, 2000, {.maxSpeed = 60, .minSpeed = 50});
    pros::delay(1500);
    frontStage.move(127);
    pros::delay(200);
    frontStage.move(0);

    //backs up and lines up for scoring
    frontStage.move(127);
    chassis.moveToPoint(-19, -32, 1000,{ .forwards = false, .maxSpeed =70}, false);
    frontStage.move(-127);
    pros::delay(100);
    frontStage.move(127);
    hood.move(127);
    pros::delay(5000);
    
    }
    else if( id == redLeft.getid()){
    chassis.setPose(0, 0, 290);

    // gets blocks from the middle
    frontStage.move(127);
    chassis.moveToPoint(-29, 8, 2000,{.maxSpeed =  90});

    //get blocks from second middle
    chassis.turnToHeading(315, 1000,{},true);
    chassis.moveToPoint(-41, 31,  2000,{.maxSpeed =  70});

    // go to goal
    chassis.moveToPoint(-29, 8, 2000,{.forwards = false, .maxSpeed =  90});
    chassis.turnToHeading(45, 2000,{},false);

    //Go line up for goal
    chassis.moveToPoint(-1.5, 35.5, 2000,{ .maxSpeed = 90,});
    chassis.turnToHeading(90, 1000,{},true);

    //backs up and lines up for scoring
    frontStage.move(127);
    chassis.moveToPoint(-19, 35.5, 2000,{ .forwards = false, .maxSpeed =70}, false);
    frontStage.move(-127);
    pros::delay(50);
    frontStage.move(127);
    hood.move(127);
    pros::delay(1000);
    hood.move(0);

    //drops little will and gets blocks out from match loader
    littleWill.set_value(true);
    chassis.moveToPoint(14, 32.5, 2000, {.maxSpeed = 60, .minSpeed = 50});
    pros::delay(1500);
    frontStage.move(127);
    pros::delay(200);
    frontStage.move(0);

    //backs up and lines up for scoring
    frontStage.move(127);
    chassis.moveToPoint(-19, 35.5, 2000,{ .forwards = false, .maxSpeed =70}, false);
    frontStage.move(-127);
    pros::delay(100);
    frontStage.move(127);
    hood.move(127);
    pros::delay(5000);
    }
    else if( id == SIGAWP.getid()){
    timer = pros::millis();
    chassis.setPose(0,0,0);
    littleWill.set_value(true);
    frontStage.move(127);
    chassis.moveToPoint(0, 34.5, 1500,{.maxSpeed =  70});
    chassis.turnToHeading(90, 500);
    chassis.moveToPoint(15, 35, 1000,{.maxSpeed =  90, .minSpeed=60});
    pros::delay(1000);
    chassis.moveToPoint(-17, 35, 1500,{.forwards= false, .maxSpeed =  90,}, false);
    hood.move(127);
    pros::delay(1250);
    hood.move(127);
    chassis.moveToPoint(-6, 35, 1500,{ .maxSpeed =  90}, false);
    littleWill.set_value(false);
    chassis.turnToHeading(215, 250);
    chassis.moveToPoint(-17, 8, 1500,{.maxSpeed =  90},false);
    hood.move(0);
    frontStage.move(127);
    chassis.turnToHeading(180, 250,{},false);
    littleWill.set_value(false);
    chassis.moveToPoint(-17, -38, 2000,{.maxSpeed =  90, .earlyExitRange=1}, false);
    chassis.moveToPoint(-34, -24, 1000,{.forwards=false, .maxSpeed =  90}, false);
    midScore.set_value(true);
    hood.move(63);
    frontStage.move(127);
    pros::delay(500);
    frontStage.move(127);
    hood.move(-63);
    midScore.set_value(false);
    chassis.moveToPoint(5, -61, 2000,{.maxSpeed =  90});
    hood.move(0);
    chassis.turnToHeading(90, 250,{},false);
    chassis.moveToPoint(-17, -60, 1000,{.forwards= false, .maxSpeed =  90}, false);
    hood.move(127);
    pros::delay(2000);
    timer = ((pros::millis() - timer)/1000);
    }

    
    //default auton code if no id matches
    else {pros::lcd::print(7, "No matching auton ID check selected auton ID number");}
}