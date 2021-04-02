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
    t = {0};
    const int maxRetires = 10;
    long now = 0;
    int i = 0;
    while (t.tm_year < 120 && ++i < maxRetires)
    {
        Serial.printf("i=%d, y=%d\n", i, t.tm_year);
        delay(200);
        now = getLocalTime(t, false);
    }
    Serial.printf("end: i=%d, y=%d\n", i, t.tm_year);
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
    configTime(1, 2 * 3600, "rs.pool.ntp.org");
    time_t now;
    time(&now);
    if (coefCorrect != 0 && correction)
    {
        int d = roundl((now - lastNetTime) / (float)coefCorrect);
        //T Serial.println("diff: " + String(now - lastNetTime) + ", d: " + String(d));
        now += d;
    }
    localtime_r(&now, &t);
    return now;
}

void SleepTimer::setCoefCorrectIN(long coefCorrect)
{
    if (!isInitialized())
        setCoefCorrect(coefCorrect);
}

void SleepTimer::setNetTimeCheck(long n)
{
    maxNetTimeCheck = n;
    if (!isInitialized())
        cntNetTimeCheck = maxNetTimeCheck;
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
