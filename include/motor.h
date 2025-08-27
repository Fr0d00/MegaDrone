#ifndef MOTOR_H
#define MOTOR_H

/*
Low value - 0% of power if we accept that 4.625% of it is an amount ow power when the motor starts
4.625 is because the lowest avaliable power is 800, and the lowest start power is a power for M_FR = 837
*/

#define FR_LOW 800
#define FR_UP 1566

#define FL_LOW 806
#define FL_UP 1593

#define BR_LOW 1048
#define BR_UP 1531

#define BL_LOW 804
#define BL_UP 1600

#include <Arduino.h>
#include "structures.h"
#include "Servo.h"

Servo M_FR, M_FL, M_BR, M_BL;

void setupMotors()
{
    M_FR.attach(4);
    M_FL.attach(5);
    M_BR.attach(6); 
    M_BL.attach(7);
    delay(3000);
    M_FL.writeMicroseconds(2200);
    M_FR.writeMicroseconds(2200);
    M_BL.writeMicroseconds(2200);
    M_BR.writeMicroseconds(2200);
    delay(3000);
    M_FL.writeMicroseconds(800);
    M_FR.writeMicroseconds(800);
    M_BL.writeMicroseconds(800);
    M_BR.writeMicroseconds(800);
    delay(3000);


}

void writeMotors(MotorData *data)
{
    M_FR.writeMicroseconds(map(data->FR, 0, 255, FR_LOW, FR_UP));
    M_FL.writeMicroseconds(map(data->FL, 0, 255, FL_LOW, FL_UP));
    M_BR.writeMicroseconds(map(data->BR, 0, 255, BR_LOW, BR_UP));
    M_BL.writeMicroseconds(map(data->BL, 0, 255, BL_LOW, BL_UP));
}

#endif