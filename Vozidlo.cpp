#include "Vozidlo.h"
#include "heap_monitor.h"
#include "Den.h"

Vozidlo::Vozidlo(string spz, int typ, int nosnost, int naklady, Den * datumEvid):
	spz_(spz),
	typVozidla_(typ),
	nosnost_(nosnost),
	naklady_(naklady),
	datZaradeniaDoEvid_(datumEvid)
{	
}

string Vozidlo::getSpz()
{
	return spz_;
}

int Vozidlo::getTypVozidla()
{
	return typVozidla_;
}

int Vozidlo::getNosnost()
{
	return nosnost_;
}

int Vozidlo::getNaklady()
{
	return naklady_;
}

Den * Vozidlo::getDatumZaciatkuEvidencie()
{
	return datZaradeniaDoEvid_;
}

Vozidlo::~Vozidlo() {


}