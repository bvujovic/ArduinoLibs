#include <Arduino.h>

#define PAUSE 1500
#include "Blinky.h"
// Blinky blnkLed(GPIO_NUM_33, false, 250, 5);
Blinky blnkLed = Blinky::createESP(250, 5);

void setup()
{
    blnkLed.blink(1000, 2);              // 2x 1sec ON, 1sec OFF
    delay(PAUSE);                        // pauza
    blnkLed.blink();                     // 5x 250ms ON, 250ms OFF (vrednosti su definisane u konstruktoru)
    delay(PAUSE);                        // pauza
    blnkLed.blinkIrregular(200, 800, 3); // Neravnomerno blinkanje. 3x 200ms ON 800ms OFF
    delay(PAUSE);                        // pauza
    blnkLed.blinkOk();                   // 2 kratka blinka kao znak da je sve Ok
    delay(PAUSE);                        // pauza
    blnkLed.blink(500, 0);               // beskonacno ponavljanje 500ms ON, 500ms OFF
}

void loop()
{
    delay(100);
}