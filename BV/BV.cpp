#include "BV.h"

void BV::Pishti(int itvPishtanje)
{
  if(pinPishti != -1)
  {
    digitalWrite(pinPishti, true);
    delay(itvPishtanje);
    digitalWrite(pinPishti, false);
    delay(itvPishtanje);
  }
}

void BV::PishtiSetPin(int pin)
{
  pinPishti = pin;
  pinMode(pin, OUTPUT);
}