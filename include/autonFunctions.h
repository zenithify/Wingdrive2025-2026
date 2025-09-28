#include "lemlib/api.hpp" // IWYU pragma: keep
#include "driverFunctions.h"


extern bool sort;
extern bool color;
bool driverOveride = false;

static void colorSort(){
    while(true){
    while(sort){
        if (color == true){
            if(blockColor.get_hue()>190 && blockColor.get_hue() < 260 && blockDistance.get()<20){
            driverOveride = true;
            frontStage.move (127);
            hood.move       (-127);
            pros::delay     (500);
            driverOveride = false;
            }
        }
            
        if (color == false){
            if(blockColor.get_hue()>-1 && blockColor.get_hue() < 27 && blockDistance.get()<20){
            driverOveride = true;
            frontStage.move (127);
            hood.move       (-127);
            pros::delay     (500);
            driverOveride = false;
            }
        }
    }
    pros::delay(10);
    }
}