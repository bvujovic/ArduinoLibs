#include <Arduino.h>
#include "DataLogger.h"

// Pamti promenu vrednosti na nekom digitalnom pinu. Prikazuje sve promene prilikom sledeceg reseta.

struct Rec
{
    ulong ms;
    bool val;
};

void dumpToFile(void *obj, File &fp)
{
    Rec *r = (Rec *)obj;
    fp.printf("%5ld %8s \n", r->ms % 100000, r->val ? "HIGH" : "LOW");
}

DataLogger<Rec, 20> vals("/vals.txt", dumpToFile);

// void stringToFile(void *obj, File &fp)
// {
//     String *s = (String *)obj;
//     fp.printf("%s\n", s->c_str());
// }

void forEach(void *obj)
{
    String *s = (String *)obj;
    Serial.println(*s);
    // Rec *r = (Rec *)obj;
    // Serial.println(r->val);
    // fp.print(r->ms);
    // fp.print('\t');
    // fp.println(r->val ? "HIGH" : "LOW");
}
// vals.forEach(forEach);

const int pinButton = D1;
bool valButton = 1;

void setup()
{
    pinMode(pinButton, INPUT_PULLUP);

    Serial.begin(115200);
    Serial.println();

    DataLogger<String, 2> strings("/strings.log", DataLogger<String, 2>::stringToFile);
    strings.add("Once");
    strings.add("Twice");
    strings.add("Thrice");
    strings.saveToFile();
    Serial.println(strings.readFromFile());

    Serial.println("Fajl:");
    Serial.println(vals.readFromFile());
}

bool bioIspis = false;

void loop()
{
    delay(20);

    bool newValButton = digitalRead(pinButton);
    if (valButton != newValButton)
    {
        Serial.print(newValButton ? "HI " : "LO ");
        ulong ms = millis();
        valButton = newValButton;
        // vals.add(Rec{millis(), valButton});
        // vals.saveToFile(dumpToFile, true);

        // vals.addSave(Rec{millis(), valButton}, dumpToFile);

        // vals.addSave(Rec{millis(), valButton});

        vals.addSaveDelayed(Rec{millis(), valButton});

        Serial.println(millis() - ms);
    }

    if (!bioIspis && vals.size() >= 2)
    {
        Serial.println(vals[0].ms);
        Serial.println(vals[1].ms);
        bioIspis = true;
    }

    vals.refresh(millis());
}