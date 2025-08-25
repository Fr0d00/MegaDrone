#include <Arduino.h>

#define WORKTYPE 3

/*
  WORKTYPE 0 = radio read
  WORKTYPE 1 = Scan Radio Frequencies
  WORKTYPE 2 = Read MPU6050
  WORKTYPE 3 = Motor Test (only one motor) with data from potentiometer;
*/

#include "structures.h"

#include "radio.h"
#include "gyro.h"
#include "regulator.h"
#include "motor.h"

#if WORKTYPE == 0

RadioData dataRadio;

void setup()
{
  Serial.begin(9600);
  setupRadio(0);
  setupMotors();
}

void loop()
{
  readRadio(&dataRadio);
  Serial.print(dataRadio.speed);
  Serial.print(" | ");
  Serial.print(dataRadio.x - 121);
  Serial.print(" | ");
  Serial.println(dataRadio.y - 124);
}

#elif WORKTYPE == 1

void setup()
{
  Serial.begin(9600);
  startCheck();
}

void loop()
{
  radioLoop();
}

#elif WORKTYPE == 2

GyroData dataGyro;

void setup()
{
  Serial.begin(9600);
  setupGyro();
}

void loop()
{
  readGyro(&dataGyro);
  Serial.print(mpuFlag);
  Serial.print(" | ");
  Serial.print(dataGyro.x);
  Serial.print(" | ");
  Serial.print(dataGyro.y);
  Serial.print(" | ");
  Serial.println(dataGyro.z);
}

#elif WORKTYPE == 3

void setup()
{
  Serial.begin(9600);
  setupMotors();
  pinMode(A0, INPUT);
}

void loop(){
  int val = map(analogRead(A0), 0, 1024, 1000, 1800);
  Serial.println(val);
  writeMotors(&MotorData(val, 1000, 1000, 1000));
}



#endif
