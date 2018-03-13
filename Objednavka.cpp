#include "Objednavka.h"

Objednavka::Objednavka(Den * datumZaevidovania, Zakaznik * zakaznik, int typTovaru, int mnozstvo, double jednotkovaCena,Den * datumDorucenia):
	zakaznik_(zakaznik),typTovaru_(typTovaru),mnozstvo_(mnozstvo), jednotkovaCena_(jednotkovaCena),datumDorucenia_(datumDorucenia)
{
}

Objednavka::~Objednavka()
{
}
