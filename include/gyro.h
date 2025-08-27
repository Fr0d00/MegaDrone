#ifndef GYRO_H
#define GYRO_H

#include <Arduino.h>

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#include "structures.h"

volatile bool mpuFlag = false; // флаг прерывания готовности
uint8_t fifoBuffer[45];        // буфер

MPU6050 mpu;


void dmpReady()
{
    mpuFlag = true;
}

void setupGyro()
{
    Wire.begin();
    mpu.initialize();
    mpu.dmpInitialize();
    mpu.setDMPEnabled(true);
    attachInterrupt(0, dmpReady, RISING);
}



void readGyro(GyroData *data, bool printData = false)
{
    float ypr[3];
    if (mpuFlag && mpu.dmpGetCurrentFIFOPacket(fifoBuffer))
    {
        // переменные для расчёта (ypr можно вынести в глобал)
        Quaternion q;
        VectorFloat gravity;

        // расчёты
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        mpuFlag = false;
    }
    data->x = -(degrees(ypr[2]) + 0.3);
    data->y = -(degrees(ypr[1]) + 3.3);
    data->z = degrees(ypr[0]);
    if(printData){
        Serial.print("Gyro data: ");
        Serial.print(data->x);
        Serial.print(" | ");
        Serial.print(data->y);
        Serial.print(" | ");
        Serial.print(data->z);
        Serial.print(" | ");
    }
}

#endif