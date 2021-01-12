#include <Vreme.h>

// 3 test-objekta za klasu Vreme - ne kombinovati ih u ovom primeru jer koriste isti pin!
Vreme alarm(0, 1);
// Vreme svetlo1(0, 0, 0, 5);
// Vreme svetlo2(23, 58, 0, 2);

int hh = 23, mm = 55;
const int itvMain = 500;
bool broj = false; // omogucava brojanje u svakom drugom ciklusu

const int pinTest = 13;

void setup() {
  pinMode(pinTest, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  Serial.print(hh); Serial.print(':'); Serial.println(mm);

  if (alarm.JeVreme(hh, mm))
    Serial.println("e, eto ga!");

  // digitalWrite(pinTest, svetlo1.UIntervalu(hh, mm));
  // digitalWrite(pinTest, svetlo2.UIntervalu(hh, mm));

  delay(itvMain);

  if (broj)
  {
    if (hh == 23 && mm == 59)
    {
      hh = 0;
      mm = 0;
    }
    else
      mm++;
  }
  broj = !broj;
}



