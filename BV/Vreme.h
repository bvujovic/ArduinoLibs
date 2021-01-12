//* enum TipVremena { Trenutak, Interval };

class Vreme
{
private:
	//*    TipVremena tip;
	int pocSat, pocMin;
	int krajSat, krajMin;

	// Metod JeVreme je vratio true za neko hh:mm i za vreme trajanja
	// tog hh:mm minuta/vremena, polje jeVremePrijavljeno ce imati vrednost true.
	// Kada dodje hh:mm+1 i JeVreme bude pozvano, jeVremePrijavljeno ce se vratiti na false.
	bool jeVremePrijavljeno = false;

	bool postavljenoPocetnoVreme = false;

	// pin koji se pali u datom intervalu ??

public:
	int getPocSat();
	int getPocMin();
	int getKrajSat();
	int getKrajMin();

	Vreme(int sat, int min);

	Vreme(int pocSat, int pocMin, int krajSat, int krajMin);

	//B Vreme(int sat, int min, IntervalSmer smer);

	void PostaviNovoVreme(int sat, int min);
	
	///<summary>Test XML komentara.</summary>
	void PostaviNovoVreme(int pocSat, int pocMin, int krajSat, int krajMin);

	// da li je prosledjeno vreme u intervalu
	bool UIntervalu(int sat, int min);

	// da li je doslo vreme za pokretanje dogadjaja (Trenutak)
	// ovde paziti da se se dogadjaj ne pokrene vise puta dok traje pocetni minut
	bool JeVreme(int sat, int min);

	void PodesiIntervalUnapred(int min);

	void PodesiIntervalUnazad(int min);
};
