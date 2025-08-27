#include <Arduino.h>

#define WORKTYPE 4

/*
  WORKTYPE 0 = radio read
  WORKTYPE 1 = Scan Radio Frequencies
  WORKTYPE 2 = Read MPU6050
  WORKTYPE 3 = Motor Test (only one motor) with data from potentiometer;
  WORKTYPE 4 = Fly Mode
*/

#include "structures.h"

#include "radio.h"
#include "gyro.h"
#include "regulator.h"
#include "motor.h"
#include "memoryCheck.h"

#if WORKTYPE == 0

RadioData dataRadio;

void setup()
{
  Serial.begin(9600);
  setupRadio(0);
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
  pinMode(A1, INPUT);
}

void loop(){
  int val = map(analogRead(A1), 0, 1024, 1000, 1800);
  Serial.println(val);
  writeMotors(&MotorData(val, 1000, 1000, 1000));
}

#elif WORKTYPE == 4

RadioData dataRadio;
GyroData dataGyro;
MotorData dataMotors;

void setup(){
  Serial.begin(9600);
  setupRadio(0);
  setupGyro();
  setupMotors();
  //delay(2000);
}


void loop(){
  readRadio(&dataRadio);
  readGyro(&dataGyro);
  regulateXY(&dataGyro, &dataMotors, &dataRadio);
  Serial.print("Free RAM: ");
  Serial.println(memoryFree());
  writeMotors(&dataMotors);
}


#endif
