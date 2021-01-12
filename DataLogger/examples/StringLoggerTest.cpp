#include "StringLogger.h"
// DataLogger<String, 3> dl;
StringLogger<3> *ss;

void forEachString(const String &s) { Serial.println(s); }

void setup()
{
    Serial.begin(115200);
    Serial.println();
    ss = new StringLogger<3>("/strings.log");
    ss->add("Once");
    ss->add("Twice");
    ss->add("Thrice");
    ss->add("Force?");

    Serial.println(ss->size());
    ss->forEach(forEachString);
    ss->print(" * ");
    Serial.println("\nJoin: " + ss->join(";"));

    // ss->saveToFile();
    // Serial.println(ss->readFromFile());

    while (true)
        delay(100);
}

void loop()
{
    delay(100);
}