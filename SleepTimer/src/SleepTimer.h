#pragma once

#include <Arduino.h>
#include "time.h"
#include "lwip/apps/sntp.h"

//
class SleepTimer
{
private:
    long lastNetTime;
    long coefCorrect;
    long coefError;
    // Na koliko sekundi se aparat budi.
    long wakeEverySec;
    short cntNetTimeCheck;
    short maxNetTimeCheck;
    //
    int sleepSeconds(int m, int s, int itv);

public:
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
    // Za dati broj sekundi, staticki metod vraca broj mikrosekundi.
    uint64_t static secToUsec(int sec) { return (uint64_t)1000 * 1000 * sec; }
    //
    uint64_t usecToSleep(tm &t);
    //
    bool shouldGetNetTime() { return ++cntNetTimeCheck >= maxNetTimeCheck; }
    // 
    short getCntNetTimeCheck() { return cntNetTimeCheck + 1; }
    // 
    short getMaxNetTimeCheck() { return maxNetTimeCheck; }
    //
    void waitFor00(tm &t);
};
