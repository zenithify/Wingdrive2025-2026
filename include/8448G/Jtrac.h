#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/motors.hpp"
#include "subsystems.h"
#include "math.h"
//varibles for offset from tracking center
float DRoffsetFB  = 0;
float DRoffsetRL  = 0;
float DLoffsetFB  = 0;
float DLoffsetRL  = 0;
float DFRoffsetFB = 0;
float DFRoffsetR  = 0;
float DFLoffsetFB = 0;
float DFLoffsetL  = 0;
float DBoffsetFB  = 0;

static float mmToIn(float mm){return mm/25.4;}


//raw distance with offset getters
static float rightRawDistance()      {return (DR.get_distance() + DRoffsetFB);}
static float leftRawDistance()       {return (DL.get_distance() + DLoffsetFB);}
static float frontRightRawDistance() {return (DFR.get_distance() + DFRoffsetFB);}
static float frontLeftRawDistance()  {return (DFL.get_distance() + DFLoffsetFB);}
static float BackRawDistance()       {return (DB.get_distance() + DBoffsetFB);}

// the trig angles of the raw distances
static float rightDistance() {return sin(rightRawDistance())+ DRoffsetRL;}
static float leftDistance()  {return sin(leftRawDistance()) + DLoffsetRL;}
static float frontDistance() {return ((cos(frontRightRawDistance())+cos(frontLeftRawDistance()))/2);}
static float backDistance()  {return cos(BackRawDistance());}

//

static void jtracStandardWallReset(int expectedQuadrent, bool frontsensors){
float x = 0;
float y = 0;
if(expectedQuadrent= 1){
    if (frontsensors){
        x = mmToIn(1800 - frontDistance());
        y = mmToIn(1800 - leftDistance());
    }
    else {
    
    }

}
if(expectedQuadrent= 2){
    if (frontsensors){
        x = mmToIn(1800 - frontDistance());
        y = mmToIn(-1800 + rightDistance());
    }
    else {
    
    }    
}
if(expectedQuadrent= 3){
    if (frontsensors){

    }
    else {
    
    }
}
if(expectedQuadrent= 4){
    if (frontsensors){

    }
    else {
    
    }
}
chassis.setPose(x,y,imu.get_heading());
}


