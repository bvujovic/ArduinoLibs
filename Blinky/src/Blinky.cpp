#include <Arduino.h>
#include "Blinky.h"

Blinky::Blinky(int pin, bool onValue, int msec, int count)
{
    pinMode(this->pin = pin, OUTPUT);
    digitalWrite(pin, !onValue);
    this->onValue = onValue;
    this->msec = msec;
    this->count = count;
}

void Blinky::blink(int msec, int count)
{
    bool val = onValue;
    for (int i = 0; i < count * 2 || count == 0; i++)
    {
        digitalWrite(pin, val);
        val = !val;
        delay(msec);
    }
}

void Blinky::blink(int count)
{
    blink(this->msec, count);
}

void Blinky::blink()
{
    blink(this->msec, this->count);
}

void Blinky::blinkIrregular(int msOn, int msOff, int count)
{
    for (int i = 0; i < count || count == 0; i++)
    {
        digitalWrite(pin, onValue);
        delay(msOn);
        digitalWrite(pin, !onValue);
        delay(msOff);
    }
}

Blinky &Blinky::createESP()
{
#ifdef ESP32
    Blinky *led = new Blinky(33, false);
#else
    Blinky *led = new Blinky(LED_BUILTIN, false);
#endif
    return *led;
}