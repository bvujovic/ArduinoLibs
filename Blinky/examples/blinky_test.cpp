#include <Arduino.h>

#include "Blinky.h"
Blinky blnkLed(GPIO_NUM_33, false, 250, 5);

void setup()
{
    blnkLed.blink(1000, 2); // 2x 1sec ON, 1sec OFF
    delay(2000);            // pauza
    blnkLed.blink();        // 5x 250ms ON, 250ms OFF (vrednosti su definisane u konstruktoru)
    delay(2000);            // pauza
    blnkLed.blink(500, 0);  // beskonacno ponavljanje 500ms ON, 500ms OFF
}

void loop()
{
    delay(100);
}