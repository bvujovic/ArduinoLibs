#pragma once

#include <Arduino.h>
#include <SPIFFS.h>

// Klasa sa statickim metodama koje rade (citanje i pisanje) sa SPIFFS fajlovima. 
class SpiffsUtils
{
public:
    // Citanje tekst fajla.
    static String ReadFile(String fileName);
    // Pisanje/dodavanje teksta u fajl.
    static bool WriteFile(String fileName, String s, const char* mode);
    //todo citanje red po red - ovo mozda napraviti tako da metoda vrati niz String-ova ili char[]
};
