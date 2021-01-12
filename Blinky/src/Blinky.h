#pragma once

#include <Arduino.h>

// Klasa koja sadrzi metode za blinkanje LED diode ili cega vec.
class Blinky
{
private:
    int pin;      // Pin na kojem se nalazi LED dioda.
    bool onValue; // Vrednost koja odgovara upaljenoj LED diodi: HIGH/LOW tj. true/false tj. 1/0.
    int msec;     // Koliko je milisekundi LED dioda ukljucena tj. iskljucena u jednom ciklusu.
    int count;    // Broj ciklusa (blinkova). 0 - beskonacno bliknanje.

public:
    Blinky(int pin, bool onValue, int msec = 500, int count = 3);
    // LED dioda je msec milisekundi ON, pa msec milisekundi OFF. Ovo se ponavlja count puta ili beskonacno ako je count==0.
    void blink(int msec, int count);
    // Blinkanje sa msec i count parametrima prethodno definisanim u konstruktoru.
    void blink();
    // Blinkanje count puta sa msec parametrom prethodno definisanim u konstruktoru.
    void blink(int count);
    // OK - blink(500, 2)
    void blinkOk() { blink(500, 2); }
    // Warning Minor - blinkIrregular(150, 450, 3)
    void blinkErrorMinor() { blinkIrregular(150, 450, 3); }
    // Error Major - blink(250, 3)
    void blinkErrorMajor() { blink(250, 3); }
    // Neravnomerno blinkanje. Npr. 500ms ON, 1500ms OFF. count==0 -> beskonacno blinkanje.
    void blinkIrregular(int msOn, int msOff, int count);
    // Paljenje (true) ili gasenje (false) LED diode na pinu koji je prethodno definisan u konstruktoru.
    void ledOn(bool val) { digitalWrite(pin, !(val ^ onValue)); }

    //* blinkAsync/blinkSetup, refresh(ms)

    // Kreiranje Blinky objekta za ESP8266 ili ESP32.
    static Blinky &createESP();
};
