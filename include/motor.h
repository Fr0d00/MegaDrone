#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "structures.h"
#include "Servo.h"

Servo M_FR, M_FL, M_BR, M_BL;

void setupMotors()
{
    M_FR.attach(3, 1000, 2000);
    M_FL.attach(4, 1000, 2000);
    M_BR.attach(5, 1000, 2000);
    M_BL.attach(6, 1000, 2000);
}

void writeMotors(MotorData *data)
{
    M_FR.write(constrain(data->FR, 1000, 1800));
    M_FL.write(constrain(data->FL, 1000, 1800));
    M_BR.write(constrain(data->BR, 1000, 1800));
    M_BL.write(constrain(data->BL, 1000, 1800));
}

#endif