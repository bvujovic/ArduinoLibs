#include "TimeESP.h"

long TimeESP::getNetTime()
{
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    char *srvr = new char[30];
    strcpy(srvr, "rs.pool.ntp.org");
    sntp_setservername(0, srvr);
    sntp_init();
    ti = {0};
    const int maxRetires = 5;
    long now = 0;
    int i = 0;
    while (ti.tm_year < 2020 && ++i < maxRetires)
    {
        delay(1000);
        now = getLocalTime();
    }
    return i < maxRetires ? now : 0;
}

long TimeESP::getLocalTime()
{
    time_t now;
    time(&now);
    localtime_r(&now, &ti);
    ti.tm_year += 1900;
    ti.tm_mon++;
    ti.tm_hour++;
    if (ti.tm_hour == 24)
    {
        ti.tm_hour = 0;
        ti.tm_mday++;
    }
    return now;
}
