#pragma once


// https://stackoverflow.com/questions/11761703/overloading-macro-on-number-of-arguments
#define GET_MACRO(_1, _2, _3, _4, NAME, ...) NAME
#define tprintln(...)                                                             \
    GET_MACRO(__VA_ARGS__, tprintln4, tprintln3, tprintln2, tprintln1, tprintln0) \
    (__VA_ARGS__)

#if TEST
#define tbegin(rate)        \
    {                       \
        Serial.begin(rate); \
        Serial.println();   \
    }
// Caption printline -> <caption> = <obj>
#define cprintln(caption, obj) \
    {                          \
        Serial.print(caption); \
        Serial.print(" = ");   \
        Serial.println(obj);   \
    }
#define tprintln0()       \
    {                     \
        Serial.println(); \
    }
#define tprintln1(p1)       \
    {                       \
        Serial.println(p1); \
    }
#define tprintln2(p1, p2)   \
    {                       \
        Serial.print(p1);   \
        Serial.println(p2); \
    }
#define tprintln3(p1, p2, p3) \
    {                         \
        Serial.print(p1);     \
        Serial.print(p2);     \
        Serial.println(p3);   \
    }
#define tprintln4(p1, p2, p3, p4) \
    {                             \
        Serial.print(p1);         \
        Serial.print(p2);         \
        Serial.print(p3);         \
        Serial.println(p4);       \
    }
#else
#define tbegin(rate) ;
#define cprintln(caption, obj) ;
#define tprintln0() ;
#define tprintln1(p1) ;
#define tprintln2(p1, p2) ;
#define tprintln3(p1, p2, p3) ;
#define tprintln4(p1, p2, p3, p4) ;
#endif

//* Test za tbegin i tprintln funkcije
// #include <Arduino.h>
// #define TEST false
// #include <UtilsCommon.h>
// int pin = 33;
// bool val = true;
// void setup()
// {
//     pinMode(pin, OUTPUT);
//     digitalWrite(pin, val);
//     tbegin(115200);
// }
// void loop()
// {
//     tprintln("Testing...");
//     digitalWrite(pin, val = !val);
//     delay(2000);
// }

// //#ifdef Arduino_h
// typedef unsigned char byte; // Ako nije ukljucen Arduino.h - valja objasniti sta je to byte
// //#endif

// https://stackoverflow.com/questions/3982348/implement-generic-swap-macro-in-c
/*
#define SWAP(x, y)          \
    do                      \
    {                       \
        typeof(x) SWAP = x; \
        x = y;              \
        y = SWAP;           \
    } while (0)
*/

#define SWAP(x, y, T) \
    do                \
    {                 \
        T SWAP = x;   \
        x = y;        \
        y = SWAP;     \
    } while (0)
