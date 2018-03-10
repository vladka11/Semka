#include "Paleta.h"
#include "heap_monitor.h"
#include "Den.h"

Paleta::Paleta(int region, int hmotnost, Den* datum, bool prvaTrieda, string dodavatel) :
	region_(region),
	hmotnost_(hmotnost),
	datDorucenia_(datum),
	prvaTrieda_(prvaTrieda),
	dodavatel_(dodavatel)
{
}

int Paleta::getRegion() {
	return region_;
}

void Paleta::setRegion(int region) {
	region_ = region;
}

int Paleta::getHmotnost() {
	return hmotnost_;
}

void Paleta::setHmotnost(int hmotnost) {
	hmotnost_ = hmotnost;
}

Den* Paleta::getDenDorucenia() {
	return datDorucenia_;
}

void Paleta::setDenDorucenia(Den* datum) {
	datDorucenia_ = datum;
}

bool Paleta::getPrvaTrieda() {
	return prvaTrieda_;
}

void Paleta::setPrvaTrieda(bool prvaTrieda) {
	prvaTrieda_ = prvaTrieda;
}

int Paleta::getStav() {
	return stav_;
}

void Paleta::setStav(int stav) {
	stav_ = stav;
}

string Paleta::getDodavatal()
{
	return dodavatel_;
}

void Paleta::setDodavatel(string dodavatel)
{
	dodavatel_ = dodavatel;
}

Den * Paleta::getDatumPrichoduDoSkladu()
{
	return datPrichDoSkladu_;
}

void Paleta::setDatumPrichoduDoSkladu(Den * denPrichodu)
{
	datPrichDoSkladu_ = denPrichodu;
}


Paleta::~Paleta()
{
	delete datPrichDoSkladu_;
	delete datDorucenia_;
}

