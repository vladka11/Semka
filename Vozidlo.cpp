#include "Vozidlo.h"
#include "heap_monitor.h"
#include "Den.h"

Vozidlo::Vozidlo(string spz, int typ, int nosnost, int naklady, Den * datumEvid) :
	spz_(spz),
	typVozidla_(typ),
	nosnost_(nosnost),
	naklady_(naklady),
	datZaradeniaDoEvid_(datumEvid)
{
	tovarVoVozidle_ = new ExplicitStack<Objednavka*>();

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

void Vozidlo::setNosnost(int novaNosnost)
{
	nosnost_ = novaNosnost;
}

void Vozidlo::setNaklady(int naklady)
{
	naklady_ = naklady;
}

Den * Vozidlo::getDatumZaciatkuEvidencie()
{
	return datZaradeniaDoEvid_;
}

ExplicitStack<Objednavka*>* Vozidlo::getTovarVoVozidle()
{
	return tovarVoVozidle_;
}

Vozidlo::~Vozidlo() {
	while (tovarVoVozidle_->size() > 0) {
		Objednavka *o = tovarVoVozidle_->pop();
		delete o->getDatumDorucenia();
		delete o->getDatumZaevidovania();
		delete o;
	}
	delete tovarVoVozidle_;
	tovarVoVozidle_ = nullptr;

}