#pragma once

#include <Arduino.h>

#if FS_LITTLEFS
#include <LittleFS.h>
#define XFS LittleFS
#elif FS_SPIFFS
#include <SPIFFS.h>
#define XFS SPIFFS
#else
#error FS_LITTLEFS or FS_SPIFFS definition required. e.g. platformio.ini: build_flags = -D FS_SPIFFS
#endif

// Klasa sa statickim metodama koje rade jednostavno citanje i pisanje sa SPIFFS/LittleFS fajlovima.
class EasyFS
{
private:
    // Ime fajla koje se postavlja sa setFileName() i koristi sa readf() i writef();
    static String fileName;

    // Pisanje/dodavanje teksta u fajl.
    static bool _write(String fileName, String text, const char *mode);

public:
    // Citanje kompletnog tekst fajla sa prosledjenim imenom.
    static String read(String fileName);
    // Citanje kompletnog tekst fajla imena zadatog sa setFileName().
    static String readf() { return read(fileName); }
    // Pisanje teksta u fajl sa prosledjenim imenom.
    static bool write(String fileName, String text) { return _write(fileName, text, "w"); }
    // Dodavanje teksta u fajl sa prosledjenim imenom.
    static bool add(String fileName, String text) { return _write(fileName, text, "a"); }
    // Pisanje teksta u fajl imena zadatog sa setFileName().
    static bool writef(String text) { return _write(fileName, text, "w"); }
    // Dodavanje teksta u fajl imena zadatog sa setFileName().
    static bool addf(String text) { return _write(fileName, text, "a"); }

    // Postavljanje imena fajla koje ce biti korisceno sa readf() i writef();
    static void setFileName(String fileName) { EasyFS::fileName = fileName; }
    // Dohvatanje imena fajla koje ce biti korisceno sa readf() i writef();
    static String getFileName() { return fileName; }

    //todo citanje red po red - ovo mozda napraviti tako da metoda vrati niz String-ova ili char[]
};
