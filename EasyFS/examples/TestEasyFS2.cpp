//* Test primer koriscenja funkcionalnosti klase EasyFS BEZ prosledjivanja fileName u readf(), writef() i addf().

#include <Arduino.h>
#include <EasyFS.h>

void setup()
{
    Serial.begin(115200);
    Serial.println();
    ulong ms = millis();
    EasyFS::setFileName("/test.txt");

    Serial.println(" *** Reading from a file");
    Serial.println(EasyFS::getFileName() + " content:");
    Serial.println(EasyFS::readf());

    Serial.println(" *** Writing to a file");
    EasyFS::writef("I disappear!"); // Ovo ce biti pregazeno sledecim upisom.
    EasyFS::writef("I appear!");
    EasyFS::addf("mee too, mee tooo!");

    Serial.println(" *** Finished in " + String(millis() - ms) + " ms.");

    while (true)
        delay(1000);
}

void loop() {}