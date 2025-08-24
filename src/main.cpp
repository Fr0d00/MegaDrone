#include <Arduino.h>

#define WORKTYPE 2

/*
  WORKTYPE 0 = radio read
  WORKTYPE 1 = Scan Radio Frequencies
  WROKTYPE 2 = Read MPU6050
*/

#include "radio.h"
#include "gyro.h"

RadioData dataRadio;
GyroData dataGyro;

#if WORKTYPE == 0

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

void setup(){
  Serial.begin(9600);
  startCheck();
}

void loop(){
  radioLoop();
}

#elif WORKTYPE == 2



void setup(){
  setupGyro();
}

void loop(){
  readGyro(&dataGyro);
  Serial.print(dataGyro.x);
  Serial.print(" | ");
  Serial.print(dataGyro.y);
  Serial.print(" | ");
  Serial.println(dataGyro.z);
}

#endif

