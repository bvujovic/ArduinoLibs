#include "StringLogger.h"

template <size_t S>
void StringLogger<S>::forEach(void (*f)(const String &))
{
    for (int i = 0; i < this->size(); i++)
        f(this->buf[i]);
}

template <size_t S>
void StringLogger<S>::print(const String &sep)
{
    for (int i = 0; i < this->size(); i++)
    {
        Serial.print(this->buf[i]);
        Serial.print(sep);
    }
}

template <size_t S>
String StringLogger<S>::join(const String &sep)
{
    String s;
    for (int i = 0; i < this->size() - 1; i++)
    {
        s.concat(this->buf[i]);
        s.concat(sep);
    }
    if (this->size() > 0)
        s.concat(this->buf[this->size() - 1]);
    return s;
}