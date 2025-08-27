#ifndef RADIO_H
#define RADIO_H

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "structures.h"

/*
    Radio.h
    This file contains all needed radio methods

    void setupRadio(byte channel) - radio initialization and reading pipe opening. channel - Which RF channel to communicate 0-127
    void readRadio(RadioData* data) - receving radio data. data - pointer to RadioData structure which contains data

*/

RF24 radio(7, 8);

const uint64_t PIPE = 0xF0F1F2F3F4LL;

const uint8_t num_channels = 128;
uint8_t values[num_channels];
const int num_reps = 100;

void setupRadio(byte channel)
{
    radio.begin();
    radio.setChannel(channel);

    radio.setDataRate(RF24_1MBPS);
    radio.setPALevel(RF24_PA_MAX);

    radio.openReadingPipe(1, PIPE);
    radio.startListening();
}

void readRadio(RadioData *data, bool printData = false)
{
    if (radio.available())
    {
        radio.read(data, sizeof(RadioData));
        if (printData)
        {
            Serial.print("Radio data: ");
            Serial.print(data->speed);
            Serial.print(" | ");
            Serial.print(data->x);
            Serial.print(" | ");
            Serial.print(data->y);
            Serial.print(" | ");
        }
    }
}

int serial_putc(char c, FILE *)
{
    Serial.write(c);
    return c;
}

void printf_begin(void)
{
    fdevopen(&serial_putc, 0);
}

void startCheck(void)
{
    Serial.begin(9600);
    printf_begin();
    radio.begin();
    radio.setAutoAck(false);
    radio.startListening(); // включаем прием сигнала

    radio.printDetails(); // если правильно соединили, то увидите настройки модуля
    delay(10000);         // задержка на 10 секунд

    radio.stopListening(); // выключаем прием сигнала
    int i = 0;             // вывод заголовков всех 127 каналов
    while (i < num_channels)
    {
        printf("%x", i >> 4);
        ++i;
    }
    printf("\n\r");
    i = 0;
    while (i < num_channels)
    {
        printf("%x", i & 0xf);
        ++i;
    }
    printf("\n\r");
}

void radioLoop(void)
{
    memset(values, 0, sizeof(values));
    int rep_counter = num_reps;
    while (rep_counter--)
    {
        int i = num_channels;
        while (i--)
        {
            radio.setChannel(i);
            radio.startListening(); // включаем прием сигнала
            delayMicroseconds(128);
            radio.stopListening(); // выключаем прием сигнала
            if (radio.testCarrier())
                ++values[i];
        }
    }
    int i = 0;
    while (i < num_channels)
    {
        printf("%x", min(0xf, values[i] & 0xf));
        ++i;
    }
    printf("\n\r");
}

#endif
