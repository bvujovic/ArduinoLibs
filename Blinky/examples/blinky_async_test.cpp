#include <Blinky.h>

Blinky led = Blinky::create();

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    delay(50);
    Serial.print('*');
    led.blinkAsync();
    // constant blinking (500ms defined in create()) regardless on msec number in delay()
    // or even if there is delay() call
}
