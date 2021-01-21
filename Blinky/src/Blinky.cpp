#include <Arduino.h>
#include "Blinky.h"

Blinky::Blinky(int pin, bool onValue, ulong msec, ulong count)
{
    pinMode(this->pin = pin, OUTPUT);
    digitalWrite(pin, !onValue);
    this->onValue = onValue;
    this->msec = msec;
    this->count = count;
}

void Blinky::blink(ulong msec, ulong count)
{
    bool val = onValue;
    for (ulong i = 0; i < count * 2 || count == 0; i++)
    {
        digitalWrite(pin, val);
        val = !val;
        delay(msec);
    }
}

void Blinky::blinkIrregular(ulong msOn, ulong msOff, ulong count)
{
    for (ulong i = 0; i < count || count == 0; i++)
    {
        digitalWrite(pin, onValue);
        delay(msOn);
        digitalWrite(pin, !onValue);
        delay(msOff);
    }
}

void Blinky::blinkAsync(ulong ms, ulong msec)
{
    digitalWrite(pin, ms % (2 * msec) > msec);
}

void Blinky::blinkProgress(ulong progress, ulong total, ulong d)
{
    ulong p = (100 / d) * progress / total;
    ledOn(p % 2 == 0);
}

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
Blinky &Blinky::create(ulong msec, ulong count)
{
    Blinky *led = new Blinky(LED_BUILTIN, true, msec, count);
    return *led;
}

#elif (ESP8266) || (ESP32)
Blinky &Blinky::create(ulong msec, ulong count)
{
#ifdef ESP32
    Blinky *led = new Blinky(33, false, msec, count);
#else
    Blinky *led = new Blinky(LED_BUILTIN, false, msec, count);
#endif
    return *led;
}

#endif