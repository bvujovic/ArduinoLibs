#pragma once

#include <Arduino.h>
#include <LittleFS.h>

// Klasa sa statickim metodama koje rade (citanje i pisanje) sa SPIFFS fajlovima. 
class LittleFsUtils
{
public:
    // Citanje tekst fajla.
    static String ReadFile(String fileName);
    // Pisanje u tekst fajl.
    static bool WriteFile(String fileName, String s);
    //todo citanje red po red - ovo mozda napraviti tako da metoda vrati niz String-ova ili char[]
};
