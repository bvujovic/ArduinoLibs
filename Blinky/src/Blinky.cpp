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

void Blinky::ledOn(const char *s, ulong msec)
{
    bool isLedOn = true;
    const char *p = s;
    while (*p != 0)
    {
        byte x = *p - '0';
        if (x <= 9)
        {
            if (x > 0)
            {
                ledOn(isLedOn);
                delay(x * msec);
            }
            isLedOn = !isLedOn;
        }
        p++;
    }
}

void Blinky::printBlink(const char *msg, ulong msTotal, ulong msBlink)
{
    Serial.println(msg);
    if (msBlink == 0)
        msBlink = this->msec;
    ulong count = msTotal / msBlink;
    blink(msBlink, count);
}

//B
// void Blinky::ledOn(const String &s)
// {
//     uint n = s.length();
//     Serial.println(n);
//     bool isLedOn = true;
//     for (uint i = 0; i < n; i++)
//     {
//         char ch = s.charAt(i);
//         if (ch < '0' || ch > '9')
//             continue;
//         ledOn(isLedOn);
//         Serial.print(isLedOn);
//         delay((ch - '0') * msec);
//         Serial.print('\t');
//         Serial.println((ch - '0') * msec);
//         isLedOn = !isLedOn;
//     }
// }

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