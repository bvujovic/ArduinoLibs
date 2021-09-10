#pragma once

#include <Arduino.h>

// #if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
typedef unsigned long ulong;
typedef unsigned int uint;
// #endif

// Klasa koja sadrzi metode za blinkanje LED diode ili cega vec.
class Blinky
{
private:
    int pin;      // Pin na kojem se nalazi LED dioda.
    bool onValue; // Vrednost koja odgovara upaljenoj LED diodi: HIGH/LOW tj. true/false tj. 1/0.
    ulong msec;   // Koliko je milisekundi LED dioda ukljucena tj. iskljucena u jednom ciklusu.
    ulong count;  // Broj ciklusa (blinkova). 0 - beskonacno bliknanje.

public:
    Blinky(int pin, bool onValue, ulong msec = 500, ulong count = 3);
    // LED dioda je msec milisekundi ON, pa msec milisekundi OFF. Ovo se ponavlja count puta ili beskonacno ako je count==0.
    void blink(ulong msec, ulong count);
    // Blinkanje sa msec i count parametrima prethodno definisanim u konstruktoru.
    void blink() { blink(this->msec, this->count); }
    // Blinkanje count puta sa msec parametrom prethodno definisanim u konstruktoru.
    void blink(ulong count) { blink(this->msec, count); }
    // OK - blink(500, 2)
    void blinkOk() { blink(500, 2); }
    // Warning Minor - blinkIrregular(150, 450, 3)
    void blinkErrorMinor() { blinkIrregular(150, 450, 3); }
    // Error Major - blink(250, 3)
    void blinkErrorMajor() { blink(250, 3); }
    // Neravnomerno blinkanje. Npr. 500ms ON, 1500ms OFF. count==0 -> beskonacno blinkanje.
    void blinkIrregular(ulong msOn, ulong msOff, ulong count);
    // Paljenje (true) ili gasenje (false) LED diode na pinu koji je prethodno definisan u konstruktoru.
    void ledOn(bool val) { digitalWrite(pin, !(val ^ onValue)); }
    // Paljenje i gasenje LED diode po zadatom paternu. 1. cifra trajanje ON, 2. cifra trajanje OFF, 3 ON...
    // Samo se cifre racunaju -> "111131" isto kao "11.11.31" ili "11 11 31". "10" -> kratko ON pa OFF bez delay-a.
    void ledOn(const char *s, ulong msec);
    void ledOn(const char *s) { ledOn(s, this->msec); }
    // void ledOn(const String &s);
    // Paljenje LED diode.
    void on() { ledOn(true); }
    // Gasenje LED diode.
    void off() { ledOn(false); }
    // Asinhrono/neblokirajuce (bez delay()) blinkanje.
    void blinkAsync(ulong ms, ulong msec);
    // Asinhrono/neblokirajuce (bez delay()) blinkanje. msec definisano u konstruktoru.
    void blinkAsync(ulong ms) { blinkAsync(ms, this->msec); }
    // Asinhrono blinkanje kao odraz nekog progresa. progress: trenutna vrednost, total: max vrednost,
    // d: koliko % je LED ON, tj. OFF. Jedan blink traje onoliko koliko se vrednost promeni za 2*d.
    void blinkProgress(ulong progress, ulong total, ulong d = 10);
    // Vrednost/broj pina LED diode.
    int getPin() { return pin; }
    // Ispis greske i [beskonacno] blinkovanje.
    void printBlink(const char* msg, ulong msTotal = 0, ulong msBlink = 0);
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
    // Kreiranje Blinky objekta za Arduino.
    static Blinky &create(ulong msec = 500, ulong count = 3);
#elif (ESP8266) || (ESP32)
    // Kreiranje Blinky objekta za ESP8266 ili ESP32.
    static Blinky &create(ulong msec = 500, ulong count = 3);
#endif
};
