#ifndef REGULATOR_H
#define REGULATOR_H

#include <Arduino.h>

#include "structures.h"

#define Pk 1
#define Dk 20
#define Ik 0.01

#define _calc_pid(error, errOld, pKoff, dKoff) (error * pKoff) + ((error - errOld) * dKoff)

float _errOldX = 0;
float _errOldY = 0;

void regulateXY(GyroData *data, MotorData *mData, RadioData *rData, bool printData = false)
{
    float errX = data->x - float(map((rData->x - 127), -128, 127, -15, 15));
    float errY = data->y - float(map((rData->y - 127), -128, 127, -15, 15));
    float uX = _calc_pid(errX, _errOldX, Pk, Dk);
    float uY = _calc_pid(errY, _errOldY, Pk, Dk);
    _errOldX = errX;
    _errOldY = errY;
    mData->FL = constrain(rData->speed + (uX - uY), 0, 255);
    mData->FR = constrain(rData->speed + (uX + uY), 0, 255);
    mData->BL = constrain(rData->speed + (-uX - uY), 0, 255);
    mData->BR = constrain(rData->speed + (uY - uX), 0, 255);
    delay(1);
    if (printData)
    {
        Serial.print("Motor data: ");
        Serial.print(mData->FL);
        Serial.print(" | ");
        Serial.print(mData->FR);
        Serial.print(" | ");
        Serial.print(mData->BL);
        Serial.print(" | ");
        Serial.print(mData->BR);
        Serial.print(" | ");
    }
}

#endif