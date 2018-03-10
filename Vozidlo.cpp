#include "Vozidlo.h"
#include "heap_monitor.h"
#include "Den.h"

Vozidlo::Vozidlo(string spz, int opotrebovanost, int nosnost, Den* denZaciatkuEvid) :
	spz_(spz), opotrebovanie_(opotrebovanost), nosnost_(nosnost), datZaciokEvid_(denZaciatkuEvid)
{
	paletyVoVozidle_ = new ExplicitStack<Paleta*>();
}

ExplicitStack<Paleta*>* Vozidlo::getPaletyVoVozidle() {
	return paletyVoVozidle_;
}


Paleta * Vozidlo::vylozPaletu()
{
	return paletyVoVozidle_->pop();
}

bool Vozidlo::nalozPaletu(Paleta * paleta)
{
	paletyVoVozidle_->push(paleta);
	return true;
}

Paleta * Vozidlo::ukazPaletu()
{
	return paletyVoVozidle_->peek();
}

string Vozidlo::getSpz() {
	return spz_;
}
void Vozidlo::setSpz(string spz) {
	spz_ = spz;
}

int Vozidlo::getOpotrebovanost() {
	return opotrebovanie_;
}
void Vozidlo::setOpotrebovanost(int opotrebovanost) {
	opotrebovanie_ = opotrebovanost;
}
int Vozidlo::getNosnost() {
	return nosnost_;
}
void Vozidlo::setNosnost(int nosnost) {
	nosnost_ = nosnost;
}
Den* Vozidlo::getDenZaciatkuEvid() {
	return datZaciokEvid_;
}
void Vozidlo::setDenZaciatkuEvid(Den* datum) {
	datZaciokEvid_ = datum;
}

Vozidlo::~Vozidlo(){
	while (paletyVoVozidle_->size() > 0) {
		Paleta *p = paletyVoVozidle_->pop();
		delete p;
	}
	delete paletyVoVozidle_;
	delete datZaciokEvid_;
	paletyVoVozidle_ = nullptr;
	datZaciokEvid_ = nullptr;

}
