#pragma once

#include <Arduino.h>
#include "time.h"
#include "lwip/apps/sntp.h"

//
class TimeESP
{
private:
    struct tm ti;

public:
    // Uzimanje tacnog vremena sa SNTP servera. WiFi mora biti ukljucen. Vraca POSIX broj sekundi.
    long getNetTime();
    // Izracunavanje tacnog vremena na osnovu poslednjeg SNTP vremena i internog sata. Vraca POSIX broj sekundi.
    long getLocalTime();

    int year() { return ti.tm_year; }
    int month() { return ti.tm_mon; }
    int day() { return ti.tm_mday; }
    int hour() { return ti.tm_hour; }
    int min() { return ti.tm_min; }
    int sec() { return ti.tm_sec; }
};
