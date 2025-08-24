#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <Arduino.h>

struct  RadioData
{
    RadioData(byte speed = 0, byte x = 0, byte y = 0){
        this->speed = speed;
        this->x = x;
        this->y = y;
    }
    byte speed;
    byte x;
    byte y;
};

struct GyroData
{
    GyroData(float x = 0, float y = 0, float z = 0)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    float x;
    float y;
    float z;
};

struct motorData
{
  int FR;
  int FL;
  int BR;
  int BL;
};

#endif