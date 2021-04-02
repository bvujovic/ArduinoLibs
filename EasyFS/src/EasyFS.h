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
    static bool _write(const String &fileName, const String &text, const char *mode);

public:
    // Citanje kompletnog tekst fajla sa prosledjenim imenom.
    static String read(const String &fileName);
    // Citanje kompletnog tekst fajla imena zadatog sa setFileName().
    static String readf() { return read(fileName); }
    // Pisanje teksta (stari sadrzaj se brise) u fajl sa prosledjenim imenom.
    static bool write(const String &fileName, const String &text) { return _write(fileName, text, "w"); }
    // Dodavanje teksta u fajl sa prosledjenim imenom.
    static bool add(const String &fileName, const String &text) { return _write(fileName, text, "a"); }
    // Pisanje teksta (stari sadrzaj se brise) u fajl imena zadatog sa setFileName().
    static bool writef(const String &text) { return _write(fileName, text, "w"); }
    // Dodavanje teksta u fajl imena zadatog sa setFileName().
    static bool addf(const String &text) { return _write(fileName, text, "a"); }
    // Brisanje sadrzaja fajla sa prosledjenim imenom.
    static bool clear(const String &fileName);
    // Brisanje sadrzaja fajla imena zadatog sa setFileName().
    static bool clearf() { return clear(fileName); }

    // Postavljanje imena fajla koje ce biti korisceno sa readf(), addf() i writef();
    static void setFileName(const String &fileName, bool clearContent = false);
    // Dohvatanje imena fajla koje ce biti korisceno sa readf() i writef();
    static String getFileName() { return fileName; }

    //todo citanje red po red - ovo mozda napraviti tako da metoda vrati niz String-ova ili char[]
};
