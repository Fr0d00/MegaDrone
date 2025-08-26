#ifndef REGULATOR_H
#define REGULATOR_H

#include <Arduino.h>

#include "structures.h"


#define Pk 0.5
#define Dk 20
#define Ik 0.01

#define _calc_pid(error, pKoff) error * pKoff


void regulateXY(GyroData* data, MotorData* mData, byte speed, byte targetX, byte targetY){
    float uX = _calc_pid(data->x - float(map((targetX - 127), -128, 127, -15, 15)), Pk);
    float uY = _calc_pid(data->y - float(map((targetY - 127), -128, 127, -15, 15)), Pk);
    mData->FL = constrain(speed + (uX - uY), 0, 255);
    mData->FR = constrain(speed + (uX + uY), 0, 255);
    mData->BL = constrain(speed + (-uX - uY), 0, 255);
    mData->BR = constrain(speed + (uY - uX), 0, 255);
}

#endif