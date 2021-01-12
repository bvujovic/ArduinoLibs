#include "Vreme.h"

int Vreme::getPocSat() { return pocSat; }
int Vreme::getPocMin() { return pocMin; }
int Vreme::getKrajSat() { return krajSat; }
int Vreme::getKrajMin() { return krajMin; }

Vreme::Vreme(int sat, int min)
{
	this->pocSat = sat % 24;
	this->pocMin = min % 60;
}

Vreme::Vreme(int pocSat, int pocMin, int krajSat, int krajMin)
{
	this->pocSat = pocSat % 24;
	this->pocMin = pocMin % 60;
	this->krajSat = krajSat % 24;
	this->krajMin = krajMin % 60;
}

void Vreme::PostaviNovoVreme(int sat, int min)
{
	this->pocSat = sat % 24;
	this->pocMin = min % 60;
}

///<summary>Test XML komentara.</summary>
void Vreme::PostaviNovoVreme(int pocSat, int pocMin, int krajSat, int krajMin)
{
	this->pocSat = pocSat % 24;
	this->pocMin = pocMin % 60;
	this->krajSat = krajSat % 24;
	this->krajMin = krajMin % 60;
}

bool Vreme::UIntervalu(int sat, int min)
{
	if (pocSat == 0 && pocMin == 0 && krajSat == 0 && krajMin == 0)
		return false;

	// ako je prvo vreme manje od drugog (npr. 15:00 - 19:59)
	if (krajSat > pocSat || krajSat == pocSat && krajMin >= pocMin)
		return (sat > pocSat || (sat == pocSat && min >= pocMin))
		&& (sat < krajSat || (sat == krajSat && min <= krajMin));

	else
		// ako je prvo vreme vece od drugog (npr. 22:00 - 04:30)
		return (sat > pocSat || sat == pocSat && min >= pocMin)
		|| (sat < krajSat || (sat == krajSat && min <= krajMin));
}


bool Vreme::JeVreme(int sat, int min) {
	if (sat == pocSat && min == pocMin)
		if (!jeVremePrijavljeno)
		{
			jeVremePrijavljeno = true;
			return true;
		}
		else
			return false;
	else
	{
		jeVremePrijavljeno = false;
		return false;
	}
}

// testovi:
//vreme		min		kraj (rezultat)
//4.35		5		4.40
//4.35		30		5.05
//23.45		30		0.15
//23.45		90		1.15
void Vreme::PodesiIntervalUnapred(int min)
{
	//[ min = min % (24*60); // dani se odsecaju, ostaju samo minuti i sati

	krajMin = pocMin + min;

	int sati = krajMin / 60;
	krajMin %= 60;

	krajSat = pocSat + sati;
	krajSat %= 24;
}

// testovi:
//vreme		min		poc (rezultat)
//4.40		5		4.35
//5.05		30		4.35
//0.15		30		23.45
//1.15		90		23.45
void Vreme::PodesiIntervalUnazad(int min)
{
	//[ min = min % (24*60); // dani se odsecaju, ostaju samo minuti i sati

	// konstruktorom (prvim, za trenutak) su definisane pocetne vrednosti za sat i min
	// pozivom ovog metoda zapravo zelimo da to budu krajnje vrednosti
	if (!postavljenoPocetnoVreme)
	{
		krajSat = pocSat;
		krajMin = pocMin;

		pocSat -= min / 60;
		min %= 60;

		pocMin = krajMin - min;

		if (pocMin < 0)
		{
			pocMin += 60;
			pocSat--;
		}

		if (pocSat < 0)
			pocSat += 24;

		postavljenoPocetnoVreme = true;
	}
}

