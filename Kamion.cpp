#include "Kamion.h"
#include "heap_monitor.h"


Kamion::Kamion(Den* denPrichodu) :
	denPrichodu_(denPrichodu)
{
	paletyVkamione_ = new ExplicitStack<Paleta*>();
}

ExplicitStack<Paleta*>* Kamion::getPaletyVkamione() {
	return  paletyVkamione_;
}


Kamion::~Kamion()
{
	while (paletyVkamione_->size() > 0) {
		Paleta *p = paletyVkamione_->pop();
		delete p;
	}
	delete paletyVkamione_;
	delete denPrichodu_;
	paletyVkamione_ = nullptr;
	denPrichodu_ = nullptr;
}


Den* Kamion::getDenPrichodu()
{
	return denPrichodu_;
}

void Kamion::setDenPrichodu(Den* denPrichodu)
{
	denPrichodu_ = denPrichodu;
}

bool Kamion::nalozPaletu(Paleta* paleta)
{
	paleta->setDatumPrichoduDoSkladu(denPrichodu_);
	paletyVkamione_->push(paleta);
	return true;
}

bool Kamion::nalozNaklad(int pocetPaliet, string dodavatel, int denSkladu, Kamion *k) {
	int region, den,trieda,hmotnost =0;

	for (int i = 0; i < pocetPaliet;i++) {
		cout << "Zadaj region dorucenia:" << endl;
		cin >> region;
		if (region < 1 || region > 5) {
			cout << "\n Regionov je len 5 ! \n" << endl;
			return false;
		}
		cout << "Hmotnost palety:" << endl;
		cin >> hmotnost;
		if (hmotnost < 1) {
			cout << "\nNeplatna hmotnost, zadaj cislo >1\n" << endl;
			return false;
		}
		cout << "Trieda (1/2):" << endl;
		cin >> trieda;
		if (trieda < 1 || trieda > 2) {
			cout << "\nZadaj platnu triedu (1/2)\n" << endl;
			return false;
		}
		if (trieda == 1) {
			cout << "Zadaj datum dorucenia: \n DEN:" << endl;
			cin >> den;
			if (den < denSkladu || den <= 0) {
				cout << "\nDen dorucenia nemoze byt mensi ako je dnesny den" << endl;
				return false;
			}
			Paleta * p = (new Paleta(region, hmotnost, new Den(den), true, dodavatel));
			p->setDatumPrichoduDoSkladu(new Den(denPrichodu_->getDen()));
			//p->setDatumPrichoduDoSkladu(new Den(k->getDenPrichodu()->getDen()));
			nalozPaletu(p);
			p = nullptr;

		} else {
			Paleta * p =(new Paleta(region, hmotnost, new Den(5000), false, dodavatel));
			p->setDatumPrichoduDoSkladu(new Den(denPrichodu_->getDen()));
			//p->setDatumPrichoduDoSkladu(new Den(k->getDenPrichodu()->getDen()));
			nalozPaletu(p);
			p = nullptr;
		}

	}	

	return true;
}
Paleta * Kamion::vylozPaletu()
{
	return paletyVkamione_->pop();
}

Paleta * Kamion::ukazPaletu()
{
	return paletyVkamione_->peek();
}

