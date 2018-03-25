#include "Objednavka.h"
#include "heap_monitor.h"

Objednavka::Objednavka(Den * datumZaevidovania, Zakaznik * zakaznik, int typTovaru, double mnozstvo, double jednotkovaCena,Den * datumDorucenia, int stav):
	
	datumZaevidovania_(datumZaevidovania),zakaznik_(zakaznik),typTovaru_(typTovaru),mnozstvo_(mnozstvo), jednotkovaCena_(jednotkovaCena),datumDorucenia_(datumDorucenia), stav_(stav)
{
}

Den * Objednavka::getDatumZaevidovania()
{
	return datumZaevidovania_;
}

Zakaznik Objednavka::getZakaznik()
{
	return *zakaznik_;
}

int Objednavka::getTypTovaru()
{
	return typTovaru_;
}

int Objednavka::getMnozstvoTovaru()
{
	return mnozstvo_;
}

double Objednavka::getJednotkovaCena()
{
	return jednotkovaCena_;
}

Den * Objednavka::getDatumDorucenia()
{
	return datumDorucenia_;
}

int Objednavka::getStav()
{
	return stav_;
}

void Objednavka::setStav(int i)
{
	stav_ = i;
}

Objednavka::~Objednavka()
{
}
