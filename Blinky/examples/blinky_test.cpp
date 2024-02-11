#include <Arduino.h>

#define PAUSE 1500
#include "Blinky.h"
// Blinky led(GPIO_NUM_33, false, 250, 5);
Blinky led = Blinky::create(250, 5);

void setup()
{
    led.blink(1000, 2);              // 2x 1sec ON, 1sec OFF
    delay(PAUSE);                    //
    led.blink();                     // 5x 250ms ON, 250ms OFF (values defined in create())
    delay(PAUSE);                    //
    led.blinkIrregular(200, 800, 3); // 3x 200ms ON 800ms OFF
    delay(PAUSE);                    //
    led.blinkOk();                   // 2 short blinks as a signal that everything is OK
    delay(PAUSE);                    //
    led.blink(500, 0);               // blinking forever 500ms ON, 500ms OFF
}

void loop()
{
}
