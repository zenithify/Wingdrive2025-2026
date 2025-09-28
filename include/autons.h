#include <string>
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "autonFunctions.h"
#include "lemlib-tarball/api.hpp"

// Replace my_paths.txt with your actual filename
// "." is replaced with "_" to overcome c++ limitations
ASSET(autontest1_txt);
ASSET(blueleft_txt);
// Create the decoder
lemlib_tarball::Decoder decoderAutonTest1(autontest1_txt);
lemlib_tarball::Decoder decoderBlueLeft(blueleft_txt);


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
auton example       (0, "Example");
auton blueLeftElims (1, "Blue Left / Red Right: Elims");
auton blueLeftQuals (2, "Blue Left / Red Right: Quals");
auton blueLeftSAWP  (3, "Blue Left / Red Right: Solo AWP");
auton redLeft       (4, "Red Left / Blue Right");


//gets name from and ID
static std::string idToName(int id){
//add if statements here for autos    
if (id == example.getid())       {return example.getname();}
if (id == blueLeftElims.getid()) {return blueLeftElims.getname();}
if (id == blueLeftQuals.getid()) {return blueLeftQuals.getname();}
if (id == blueLeftSAWP.getid())  {return blueLeftSAWP.getname();}
if (id == redLeft.getid())       {return redLeft.getname();}

else {return "";}
}


// Create a decoder for the tarball

// a method that runs off of an integer id for easy future implimentation of an auton selector
static void runAuto(int id){
    
    //example of creating a auton routine based on the example auton abject created above
    if (id == example.getid()){
    chassis.setPose(0, 0, 0);
    chassis.follow(decoderAutonTest1["to mid blocks"], 15, 2000);
    chassis.follow(decoderAutonTest1["to match load"], 15, 2000);
    }
    else if (id == blueLeftElims.getid()){
    chassis.setPose(0, 0, 250);

    // gets blocks from the middle
    frontStage.move(127);
    chassis.moveToPoint(-29, -8, 2000,{.maxSpeed = 70});

    //Goes to line up for match loader
    chassis.turnToHeading(135, 1000);
    chassis.moveToPoint(-1.5, -30.5, 2000,{.maxSpeed = 50});
    chassis.turnToHeading(90, 2000,{},true);
 
    //drops little will and gets blocks out from match loader
    littleWill.set_value(true);
    chassis.moveToPoint(13.5, -30.5, 2000, {.maxSpeed = 60});
    pros::delay(2500);
    frontStage.move(-127);
    pros::delay(200);
    frontStage.move(0);

    //backs up and lines up for scoring
    chassis.moveToPose(-6, -32, 90, 2000,{.forwards = false, .maxSpeed =50}, false);
    frontStage.move(127);
    chassis.moveToPoint(-17, -32.5, 2000,{ .forwards = false, .maxSpeed =50}, false);
    hood.move(127);
    }
    else if (id == blueLeftQuals.getid()){
    
    chassis.setPose(0, 0, 250);\

    // gets blocks from the middle
    frontStage.move(127);
    chassis.moveToPoint(-29, -8, 1000,{.maxSpeed =  70});

    //goes to middle goal and scores
    chassis.turnToHeading(135, 2000);
    chassis.moveToPoint(-38, 4.5,2000,{.forwards=false, .maxSpeed = 70}, false);
    hood.move(63);
    frontStage.move(63);
    midScore.set_value(true);
    pros::delay(500);
    frontStage.move(-127);
    pros::delay(200);
    hood.move(0);
    midScore.set_value(false);
    frontStage.move(127);

    //Goes to line up for match loader
    chassis.moveToPoint(-1.5, -30.5, 2000,{.maxSpeed = 50});
    chassis.turnToHeading(90, 2000,{},true);

    //drops little will and gets blocks out from match loader
    littleWill.set_value(true);
    chassis.moveToPoint(13.5, -30.5, 2000, {.maxSpeed = 60});
    pros::delay(2500);
    frontStage.move(-127);
    pros::delay(200);
    frontStage.move(0);

    //backs up and lines up for scoring
    chassis.moveToPose(-6, -32, 90, 2000,{.forwards = false, .maxSpeed =50}, false);
    frontStage.move(127);
    chassis.moveToPoint(-17, -32.5, 2000,{ .forwards = false, .maxSpeed =50}, false);
    hood.move(127);




    }
    else if (id == blueLeftSAWP.getid()){

    }
    else if( id == redLeft.getid()){
    chassis.setPose(0, 0, 290);

    // gets blocks from the middle
    frontStage.move(127);
    chassis.moveToPoint(-29, 8, 2000,{.maxSpeed = 70});

    //Goes to line up for match loader
    chassis.turnToHeading(45, 1000);
    chassis.moveToPoint(-1.5, 30.5, 2000,{.maxSpeed = 50});
    chassis.turnToHeading(90, 2000,{},true);
 
    //drops little will and gets blocks out from match loader
    littleWill.set_value(true);
    chassis.moveToPoint(13.5, 30.5, 2000, {.maxSpeed = 60});
    pros::delay(2500);
    frontStage.move(-127);
    pros::delay(200);
    frontStage.move(0);

    //backs up and lines up for scoring
    chassis.moveToPose(-6, 32, 90, 2000,{.forwards = false, .maxSpeed =50}, false);
    frontStage.move(127);
    chassis.moveToPoint(-17, 32.5, 2000,{ .forwards = false, .maxSpeed =50}, false);
    hood.move(127);

    }

    
    //default auton code if no id matches
    else {pros::lcd::print(7, "No matching auton ID check selected auton ID number");}
}