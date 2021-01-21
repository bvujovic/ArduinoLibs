#include <Blinky.h>

#define MAX 10000
Blinky led = Blinky::createESP();

void setup()
{
}

void loop()
{
    delay(20);
    ulong ms = millis();

    // led.blinkAsync(millis(), 250);
    // led.blinkAsync(ms); // koristi se msec definisan u ctor-u

    led.blinkProgress(ms, MAX, 5);

    if (ms > MAX)
    {
        led.ledOn(false);
        while (true)
            delay(100);
    }
}
