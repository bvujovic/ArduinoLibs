#include "Arduino.h"

class BV
{
public:
	void PishtiSetPin(int pin);
	void Pishti(int itvPishtanje);

private:
	int pinPishti = -1;
};