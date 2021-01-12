#include <Arduino.h>
#include "EasyINI.h"

// testirati: ima li problema ako se u istom skecu vise puta pozove SPIFFS.begin()
// sta ako pozovem close, a nisam ni otvorio fajl
// pronaci neki nacin za davanje informacije o mogucim greskama
// mozda staviti u destruktor Close? (ako je fajl prethodno otvoren)

//* platformio.ini
//* build_flags =
//*     -D FS_LITTLEFS

EasyINI ei("/test3.ini");

void setup()
{
    Serial.begin(115200);
    Serial.println("\n");

    bool succ = ei.open(FMOD_READ);
    if (succ)
    {
        Serial.println(ei.getInt("one"));
        Serial.println(ei.getFloat("two"));
        bool three = ei.getInt("three");
        Serial.println(three);
        // citanje teksta - String
        Serial.println(ei.getString("four_five"));
        Serial.println(ei.getString("six"));
        // citanje teksta - char *
        Serial.println(ei.getCharArray("four_five"));
        Serial.println(ei.getCharArray("six"));
        ei.close();
    }
    else
        Serial.println("feeejl");

    // ulong ms = millis();
    // ei.open(EasyIniFileMode::FMOD_READ);
    // {
    //     Serial.println(ei.getFloat("two", 5.99));
    //     Serial.println(ei.getInt("three", 3));
    //     Serial.println(ei.getInt("one", 1));
    //     Serial.println(ei.getAll());
    //     Serial.println(ei.getString("str", "bleja"));
    //     ei.close();
    // }
    // Serial.println(millis() - ms);
    // delay(2000);

    // if (ei.open(EasyIniFileMode::FMOD_WRITE))
    // {
    //     ei.setFloat("two", 10.55);
    //     ei.setInt("three", 125);
    //     ei.setInt("ones", 100);
    //     ei.setString("str", "Azuki");
    //     ei.close();
    // }
    Serial.println("End.");
}

void loop()
{
    delay(100);
}