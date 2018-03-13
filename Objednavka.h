#pragma once
#include "Den.h"
#include "Zakaznik.h"
class Objednavka
{
public:
	Objednavka(Den * datumZaevidovania, Zakaznik * zakaznik, int typTovaru, int mnozstvo, double jednotkovaCena, Den * datumDorucenia);
	~Objednavka();

private:
	Den * datumZaevidovania_;
	Zakaznik * zakaznik_;
	int typTovaru_; // 1 = Lupienky, 2 = Hranolceky
	int mnozstvo_;
	double jednotkovaCena_;
	Den * datumDorucenia_;


};

