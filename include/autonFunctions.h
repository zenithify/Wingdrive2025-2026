#include "lemlib/api.hpp" // IWYU pragma: keep
#include "driverFunctions.h"
#include "pros/rtos.hpp"
#include <cstdio>


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

//block counter for autons
int blockCount = 0;
int timestamp = 0;
int lastDistance =blockDistance.get();
int cycles = 0;
int blockdis = blockDistance.get();
static int getblockCount(){
    return blockCount;
}

static void blockCounter(int desiredBlocks, int maxTime){
    timestamp = pros::millis();
    frontStage.move(100);
    hood.move(127);
    while((blockCount < desiredBlocks) && ((pros::millis() - timestamp) < maxTime)){
        blockdis = blockDistance.get();
        while (blockdis < 70){
            if (cycles < 1){
                blockCount++;
                printf("counted");
                lastDistance = blockDistance.get();
                cycles++;
            }
        blockdis = blockDistance.get();
    }
        cycles = 0;
        pros::delay(100);
    }
    frontStage.move(0);
    hood.move(0);
    blockCount = 0;
}
