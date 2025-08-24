#ifndef GYRO_H
#define GYRO_H

#include <Arduino.h>

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

volatile bool mpuFlag = false; // флаг прерывания готовности
uint8_t fifoBuffer[45];        // буфер

MPU6050 mpu;

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

void readGyro(GyroData *data)
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
    data->x = degrees(ypr[2]) + 0.7;
    data->y = degrees(ypr[1]) - 2.5;
    data->z = degrees(ypr[0]);
}

#endif