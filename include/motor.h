#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "structures.h"
#include "Servo.h"

Servo M_FR, M_FL, M_BR, M_BL;

void setupMotors()
{
    M_FR.attach(3, 800, 2200);
    M_FL.attach(4, 800, 2200);
    M_BR.attach(5, 800, 2200);
    M_BL.attach(6, 800, 2200);
}

void writeMotors(MotorData *data)
{   
    M_FR.write(map(data->FR, 0, 100, 800, 1566));
    M_FL.write(map(data->FL,0, 100, 803, 1593));
    M_BR.write(map(data->BR,0, 100, 1044, 1531));
    M_BL.write(map(data->BL,0, 100, 801, 1600));
}

#endif