#include <Blinky.h>
Blinky led = Blinky::create();

void setup()
{
    pinMode(led.getPin(), OUTPUT);
}

void loop()
{
    led.blink();
}