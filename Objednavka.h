#pragma once
#include "Den.h"
#include "Zakaznik.h"
class Objednavka
{
public:
	Objednavka(Den * datumZaevidovania, Zakaznik * zakaznik, int typTovaru, double mnozstvo, double jednotkovaCena, Den * datumDorucenia, int stav);
	Den *getDatumZaevidovania();
	Zakaznik getZakaznik();
	int getTypTovaru();
	int getMnozstvoTovaru();
	double getJednotkovaCena();
	Den *getDatumDorucenia();
	
	~Objednavka();

private:
	Den * datumZaevidovania_;
	Zakaznik * zakaznik_;
	int typTovaru_; // 1 = Lupienky, 2 = Hranolceky
	int mnozstvo_;
	double jednotkovaCena_;
	Den * datumDorucenia_;
	int stav_;


};

