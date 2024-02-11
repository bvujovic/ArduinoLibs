#pragma once

#include <Arduino.h>

// #if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
typedef unsigned long ulong;
typedef unsigned int uint;
// #endif

// Class with methodes for blinking LEDs, maybe turning ON/OFF buzzers...
class Blinky
{
private:
    int pin;      // Pin connected to a LED.
    bool onValue; // Value that corresponds to the LED being ON. For LED_BUILTIN on ESP boards this value should be false (LOW).
    ulong msec;   // Duration (milliseconds) of LED turned ON or OFF in one cycle.
    ulong count;  // How many times LED will blink. 0 for endless blinking.

public:
    Blinky(int pin, bool onValue, ulong msec = 500, ulong count = 3);
    // LED is turned ON for {msec} milliseconds, then {msec} milliseconds is turned OFF.
    // This will repeat {count} times or forever if count==0.
    void blink(ulong msec, ulong count);
    // Blinking using {msec} and {count} values defined in constructor.
    void blink() { blink(this->msec, this->count); }
    // Blinkanje count puta sa msec parametrom prethodno definisanim u konstruktoru.
    void blink(ulong count) { blink(this->msec, count); }
    // OK - blink(500, 2)
    void blinkOk() { blink(500, 2); }
    // Warning Minor - blinkIrregular(150, 450, 3)
    void blinkErrorMinor() { blinkIrregular(150, 450, 3); }
    // Error Major - blink(250, 3)
    void blinkErrorMajor() { blink(250, 3); }
    // E.g. 500ms LED is ON, 1500ms is OFF.
    void blinkIrregular(ulong msOn, ulong msOff, ulong count);
    // Turning the LED ON (val==true) or OFF (val==false). Methods on() or off() can be used for this purpose.
    void ledOn(bool val) { digitalWrite(pin, !(val ^ onValue)); }
    // Turning the LED ON and OFF using given pattern {s}. 1st digit is ON duration, 2nd is OFF duration, 3rd for ON again...
    // Only digits are processed -> "111131" is the same as "11.11.31" or "11 11 31". "10" -> short ON then OFF without delay().
    void ledOn(const char *s, ulong msec);
    // Turning the LED ON and OFF using given pattern {s}. 1st digit is ON duration, 2nd is OFF duration, 3rd for ON again...
    // Only digits are processed -> "111131" is the same as "11.11.31" or "11 11 31". "10" -> short ON then OFF without delay().
    void ledOn(const char *s) { ledOn(s, this->msec); }
    // Turning the LED ON.
    void on() { ledOn(true); }
    // Turning the LED OFF.
    void off() { ledOn(false); }
    // Asynchronous/non-blocking (without delay()) blinking.
    void blinkAsync(ulong ms, ulong msec);
    // Asynchronous/non-blocking (without delay()) blinking. {msec} is set in constructor.
    void blinkAsync(ulong ms) { blinkAsync(ms, this->msec); }
    // Asynchronous/non-blocking (without delay()) blinking. {msec} and {ms} are set in constructor.
    void blinkAsync() { blinkAsync(millis(), this->msec); }
    // Asynchronous blinking that reflect some progress. {progress} - current value, {total} - max value,
    // d - how many % is LED ON or OFF. One blink lasts for as long as {progress} changes for 2*d.
    void blinkProgress(ulong progress, ulong total, ulong d = 10);
    // Get pin number for a LED.
    int getPin() { return pin; }
    // Print {msg} on Serial and then do blinking.
    void printBlink(const char *msg, ulong msTotal = 0, ulong msBlink = 0);
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
    // Creating Blinky object for Arduino board.
    static Blinky &create(ulong msec = 500, ulong count = 3);
#elif (ESP8266) || (ESP32)
    // Creating Blinky object for ESP8266 or ESP32.
    static Blinky &create(ulong msec = 500, ulong count = 3);
#endif
};
