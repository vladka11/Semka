#include "Zakaznik.h"
#include <string>


Zakaznik::Zakaznik(string obchodnyNazov, int cisloRegionu) :
	obchodnyNazov_(obchodnyNazov), cisloRegionu_(cisloRegionu)
{
}

string Zakaznik::getObchodnyNazov()
{
	return obchodnyNazov_;
}

int Zakaznik::getCisloRegionu()
{
	return cisloRegionu_;
}

Zakaznik::~Zakaznik()
{
}
