#pragma once

#include <Arduino.h>
#include "time.h"
#include "lwip/apps/sntp.h"

// Razlika izmedju tekuce godine i broja koji vraca NTP server.
#define ST_ADD_YEAR (1900)
// Razlika izmedju tekuceg meseca i broja koji vraca NTP server.
#define ST_ADD_MON (1)

//
class SleepTimer
{
private:
    long lastNetTime;
    long coefCorrect;
    long coefError;
    long wakeEverySec;     // Na koliko sekundi se aparat budi.
    short cntNetTimeCheck; // Brojac budjenja [0..maxNetTimeCheck]
    short maxNetTimeCheck; // Posle koliko budjenja se uzima vreme sa neta radi provere.
    //
    int sleepSeconds(int m, int s, int itv);

public:
    SleepTimer() {}
    SleepTimer(long coefCorrect);
    SleepTimer(long wakeEverySec, short netTimeCheck, long coefCorrect);
    // Uzimanje tacnog vremena sa SNTP servera. WiFi mora biti ukljucen. Vraca POSIX broj sekundi.
    long getNetTime(tm &t);
    // Izracunavanje tacnog vremena na osnovu poslednjeg SNTP vremena i internog sata. Vraca POSIX broj sekundi.
    long getLocalTime(tm &t, bool correction = true);
    // Da li je do sada pozvan getNetTime() i time uzeto tacno vreme sa neta.
    bool isInitialized() { return lastNetTime != 0; }
    //
    long getCoefCorrect() { return coefCorrect; }
    //
    void setCoefCorrect(long coefCorrect) { this->coefCorrect = coefCorrect; }
    // Postavljanje koeficijenta za korigovanje vremena samo ako objekat nije inicijalizovan (lastNetTime==0).
    void setCoefCorrectIN(long coefCorrect);
    // Vraca koeficijent greske sata NEracunajuci postavljen coefCorrect. Proteklo vreme (sec) / greska (sec).
    long getCoefError() { return coefError; }
    // Na koliko sekundi se aparat budi.
    long getWakeEvery() { return wakeEverySec; }
    // Postavlja broj sekundi na koliko se aparat budi.
    void setWakeEvery(long sec) { wakeEverySec = sec; }
    // Posle koliko budjenja se uzima vreme sa neta.
    long getNetTimeCheck() { return maxNetTimeCheck; }
    //
    bool shouldGetNetTime() { return ++cntNetTimeCheck >= maxNetTimeCheck; }
    // Postavljanje broja budjenja posle koliko se uzima vreme sa neta.
    void setNetTimeCheck(long n);
    //B void setNetTimeCheck(long n) { maxNetTimeCheck = n; }
    //
    short getCountNetTimeCheck() { return cntNetTimeCheck + 1; }
    //
    void setCountNetTimeCheck(long n) { cntNetTimeCheck = n; }
    // Za dati broj sekundi, staticki metod vraca broj mikrosekundi.
    uint64_t static secToUsec(int sec) { return (uint64_t)1000 * 1000 * sec; }
    //
    uint64_t usecToSleep(tm &t);
    //
    void waitFor00(tm &t);
};
