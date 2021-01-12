#pragma once

#include "DataLogger.h"

// template <typename T, size_t S>
// class DataLogger
// {

// template <size_t S> // specialization
// class DataLogger<String, S>
// {
// };

template <size_t S>
class StringLogger : public DataLogger<String, S>
{
public:
    StringLogger(const char *fileName, bool clearFile = false, int saveDelay = 1000)
        : DataLogger<String, S>(fileName, DataLogger<String, S>::stringToFile, clearFile, saveDelay) {}

    void forEach(void (*f)(const String &));

    void print(const String &);

    String join(const String &);
};

#include "StringLogger.tpp"
