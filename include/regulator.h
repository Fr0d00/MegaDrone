#ifndef REGULATOR_H
#define REGULATOR_H

#define _calc_pid(error, pKoff) error * pKoff

#include <Arduino.h>

#include "structures.h"

#define Pk 0.5
#define Dk 20
#define Ik 0.01


void regulateXY(GyroData* data, motorData* mData, byte speed, byte targetX, byte targetY){
    speed = map(speed, 0, 255, 0, 100);
    float uX = _calc_pid(data->x - float(constrain(targetX - 127, -15, 15)), Pk);
    float uY = _calc_pid(data->y - float(constrain(targetY - 127, -15, 15)), Pk);
    mData->FL = constrain(speed + (uX - uY), 0, 100);
    mData->FR = constrain(speed + (uX + uY), 0, 100);
    mData->BL = constrain(speed + (-uX - uY), 0, 100);
    mData->BR = constrain(speed + (uY - uX), 0, 100);
}

#endif