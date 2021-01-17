#include "SleepTimer.h"

SleepTimer::SleepTimer(long coefCorrect)
{
    if (!isInitialized())
        setCoefCorrect(coefCorrect);
}

SleepTimer::SleepTimer(long wakeEverySec, short netTimeCheck, long coefCorrect)
{
    if (!isInitialized())
    {
        this->wakeEverySec = wakeEverySec;
        this->maxNetTimeCheck = this->cntNetTimeCheck = netTimeCheck;
        setCoefCorrect(coefCorrect);
    }
}

long SleepTimer::getNetTime(tm &t)
{
    long nowLocal = getLocalTime(t, false);
    ulong ms = millis();
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    char *srvr = new char[30];
    strcpy(srvr, "rs.pool.ntp.org");
    sntp_setservername(0, srvr);
    sntp_init();
    t = {0};
    const int maxRetires = 5;
    long now = 0;
    int i = 0;
    while (t.tm_year < 2020 && ++i < maxRetires)
    {
        delay(1000);
        now = getLocalTime(t, false);
    }
    if (lastNetTime != 0)
    {
        long prediction = nowLocal + (millis() - ms + 500) / 1000; // +500 je tu zbog zaokruzivanja umesto odsecanja
        coefError = (now == prediction) ? 0 : roundl((double)(now - lastNetTime) / (now - prediction));
    }
    lastNetTime = now;
    cntNetTimeCheck = 0;
    return i < maxRetires ? now : 0;
}

long SleepTimer::getLocalTime(tm &t, bool correction)
{
    time_t now;
    time(&now);
    if (coefCorrect != 0 && correction)
    {
        int d = roundl((now - lastNetTime) / (float)coefCorrect);
        //T Serial.println("diff: " + String(now - lastNetTime) + ", d: " + String(d));
        now += d;
    }
    localtime_r(&now, &t);
    t.tm_year += 1900;
    t.tm_mon++;
    t.tm_hour++;
    if (t.tm_hour == 24)
    {
        t.tm_hour = 0;
        t.tm_mday++;
    }
    return now;
}

void SleepTimer::setCoefCorrectIN(long coefCorrect)
{
    if (!isInitialized())
        setCoefCorrect(coefCorrect);
}

uint64_t SleepTimer::usecToSleep(tm &t)
{
    getLocalTime(t);
    int sec = sleepSeconds(t.tm_min, t.tm_sec, wakeEverySec);
    //T Serial.println("sec: " + String(sec));
    return secToUsec(sec);
}

int SleepTimer::sleepSeconds(int m, int s, int itv)
{
    if (itv % 60 != 0) // ako itv ne predstavlja tacan broj minuta, onda nema namestanja na pocetak minuta
        return itv;
    int x = itv / 60;            // 300/60 = 5
    int nextMin = m / x * x + x; // 56/5 * 5 + 5 = 11*5 + 5 = 55 + 5 = 60
    int min = nextMin - m;       // 60 - 56 = 4
    int sec = min * 60 - s;      // 4*60 - 30 = 240 - 30 = 210
    return sec;
}

void SleepTimer::waitFor00(tm &t)
{
    if (wakeEverySec % 60 != 0)
        return;
    while (true)
    {
        getLocalTime(t);
        if (t.tm_sec < 45)
            break;
        delay(250);
        //T Serial.print('#');
    }
}
