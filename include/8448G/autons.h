#include "main.h"
#include <string>
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "autonFunctions.h"
#include "lemlib-tarball/api.hpp"
//creates an auton class to store auton names and ids for future auton selector implimentation
class auton {
public: 
std::string name;
int id;

//creating the getid() method to return the id of the auton object
int getid(){
return id;
}

//creating the getname() method to return the name of the auton object
std::string getname(){
return name;
}

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
auton example(0, "Example");

//gets name from and ID
static std::string idToName(int id){
    
if (id == example.getid()){return example.getname();}

else {return "";}
}


// Create a decoder for the tarball

// a method that runs off of an integer id for easy future implimentation of an auton selector
static void runAuto(int id){
    
    //example of creating a auton routine based on the example auton abject created above
    if (id == example.getid()){
    chassis.setPose(0, 0, 0);
    }
    
    
//default auton code if no id matches
else {pros::lcd::print(7, "No matching auton ID check selected auton ID number");}
}