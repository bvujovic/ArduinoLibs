//* Test primer koriscenja funkcionalnosti klase EasyFS SA prosledjivanjem fileName u read(), write() i add().

#include <Arduino.h>
#include <EasyFS.h>

const String fileName = "/test.txt";

void setup()
{
    Serial.begin(115200);
    Serial.println();
    ulong ms = millis();

    Serial.println(" *** Reading from a file");
    Serial.println(fileName + " content:");
    Serial.println(EasyFS::read(fileName));

    Serial.println(" *** Writing to a file");
    EasyFS::write(fileName, "I disappear!"); // Ovo ce biti pregazeno sledecim upisom.
    EasyFS::write(fileName, "I appear!");
    EasyFS::add(fileName, "mee too, mee tooo!");

    Serial.println(" *** Finished in " + String(millis() - ms) + " ms.");

    while (true)
        delay(1000);
}

void loop() {}