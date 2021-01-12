#pragma once

#include "CircularBuffer.h"

#if FS_LITTLEFS
#include <LittleFS.h>
#define XFS LittleFS
#endif
#if FS_SPIFFS
#include <SPIFFS.h>
#define XFS SPIFFS
#endif

// Kruzna lista S objekata tipa T koja moze biti sacuvana u SPIFFS/LittleFS fajl.
template <typename T, size_t S>
class DataLogger
{
private:
    const char *fileName;             // Naziv fajla u koji se smestaju podaci, npr: /events.log
    void (*saveFunc)(void *, File &); // Funkcija koja prosledjeni objekat cuva u fajl. Npr: f.print()
    ulong msSave = UINT32_MAX;        // Trenutak (u ms) kada ce se podaci iz bafera sacuvati u fajl.
    int msSaveDelay;                  // Min. interval (u ms) izmedju poslednjeg addSaveDelayed i cuvanja bafera u fajl.

protected:
    CircularBuffer<T, S> buf;         // Kruzna lista S objekata tipa T.

public:
    DataLogger(const char *, void (*saveFunc)(void *, File &) = NULL, bool clearFile = false, int saveDelay = 1000);

    // Broj stavki u baferu.
    int size() { return buf.size(); }
    // Dohvatanje stavke iz bafera.
    T get(int idx) { return buf[idx]; }
    // Dohvatanje stavke iz bafera.
    const T &operator[](int i)
    {
        const T &obj = buf[i];
        return obj;
    }
    // Dodavanje stavke u bafer (kruznu listu).
    void add(T el) { buf.push(el); }
    // Prosledjena funkcija se izvrsava za sve stavke u baferu.
    void forEach(void (*f)(void *));
    // Vraca ime fajla koje je prosledjeno konstruktoru.
    const char *getFileName() { return fileName; }
    // Pisanje podataka iz bafera u fajl.
    void saveToFile(bool clearBuffer = true);
    // Dodavanje stavke u bafer (kruznu listu) uz upisivanje svih stavki u fajl.
    void addSave(T el, bool clearBuffer = true);
    // Dodavanje stavke u bafer (kruznu listu) uz odlozeno upisivanje (i brisanje) svih stavki u fajl.
    void addSaveDelayed(T el);
    // Poziv ove metode je neophodan u loop-u ako se koristi addSaveDelayed.
    void refresh(ulong ms);
    // Brisanje podataka u fajlu.
    void clearFile();
    // Vraca procitane podatke iz fileName fajla.
    String readFromFile();
    // Metoda prolazi kroz sve redove fajla i poziva func funkciju za svaki od njih.
    void forEachInFile(void (*func)(String));
    // Podrazumevana funkcija za ispis String objekata u fajl.
    static void stringToFile(void *obj, File &fp);
};

#include "DataLogger.tpp"