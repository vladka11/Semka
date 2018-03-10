#include "Sklad.h"
#include "heap_monitor.h"
#include <fstream>

Sklad::Sklad()
{
	zoznamBiofarmarov_ = new LinkedList<Biofarmar *>();
	zoznamVozidiel_ = new LinkedList<Vozidlo *>();
}


/*
 ULOHA è.1 - pridanie biofarmara*/
void Sklad::pridajBiofarmara(Biofarmar * biofarmar)
{
	zoznamBiofarmarov_->add(biofarmar);
}

void Sklad::vypisBiofarmarov(LinkedList<Biofarmar *> *biofarmari)
{
	cout << "BIOFARMARI: \n----------------------------------------\n " << endl;
	string polotovary;
	bubbleSort(biofarmari,biofarmari->size());
	for (Biofarmar* b : *biofarmari) {
		polotovary = "";
		b->getZemiaky() ? polotovary += "zemiaky, ": polotovary += "";
		b->getOlej() ? polotovary += "olej, " : polotovary += "";
		b->getOchucovadla() ? polotovary += "ochucovadla" : polotovary += "";
		cout << "Nazov: " + b->getObchodnyNazov() + " - " + polotovary << endl;
	}
}

void Sklad::vypisUrcitychBiofarmarov(int typTovaru)
{
	LinkedList<Biofarmar *>* pomocnyListBiofarmarov_ = new LinkedList<Biofarmar *>();

	if (typTovaru == 1) {
		vypisBiofarmarov(zoznamBiofarmarov_);
	}
	else {
		for (Biofarmar* b : *zoznamBiofarmarov_) {
			if (b->getOlej() && typTovaru == 2) { //olej
				pomocnyListBiofarmarov_->add(b);
			}
			if (b->getZemiaky() && typTovaru == 3) { //zemiaky
				pomocnyListBiofarmarov_->add(b);
			}
			if (b->getOchucovadla() && typTovaru == 4) { //ochucovadla
				pomocnyListBiofarmarov_->add(b);
			}

		}
		vypisBiofarmarov(pomocnyListBiofarmarov_);
		
	}


	//zmazanie pomocneho linked listu
	if (pomocnyListBiofarmarov_->size() > 0) {
		Biofarmar * biofarm = pomocnyListBiofarmarov_->removeAt(pomocnyListBiofarmarov_->size() - 1);
		delete biofarm;
	}
	delete pomocnyListBiofarmarov_;
}

//bubble sort pre abecedne usporiadenie biofarmarov
void Sklad::bubbleSort(LinkedList <Biofarmar*> *linkedList, int size) { // O(n^2)
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (linkedList->operator[](j + 1)->getObchodnyNazov() < linkedList->operator[](j)->getObchodnyNazov()) {

				DSRoutines::swap(linkedList->operator[](j + 1), linkedList->operator[](j));
			}
		}
	}
}

//bubble sort pre vozidla - usporiadanie pod¾a datumu
void Sklad::bubbleSortVozidiel(LinkedList <Vozidlo*> *linkedList, int size) { // O(n^2)
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (linkedList->operator[](j + 1)->getDatumZaciatkuEvidencie()->getDen() < linkedList->operator[](j)->getDatumZaciatkuEvidencie()->getDen()) {

				DSRoutines::swap(linkedList->operator[](j + 1), linkedList->operator[](j));
			}
		}
	}
}

void Sklad::pridajVozidlo(Vozidlo * vozidlo)
{
	zoznamVozidiel_->add(vozidlo);
}

void Sklad::vypisVozidla()
{
	bubbleSortVozidiel(zoznamVozidiel_, zoznamVozidiel_->size());

	for (Vozidlo *v : *zoznamVozidiel_) {
		cout << "Vozidlo: " + v->getSpz() << endl;
		string typ = "Rozvoz hranolcekov";
		if (v->getTypVozidla() == 1) {
			typ = "Rozvoz lupienkov";
		} 
		cout << "Typ:" + typ << endl;
		cout << "Datum zaradenia do evidencie: " << v->getDatumZaciatkuEvidencie()->getDen() << endl;
		cout << "Celkove naklady: " << v->getNaklady() << "\n" << endl;
	}
}

Sklad::~Sklad()
{
	//zmazanie biofarmarov
	if (zoznamBiofarmarov_->size() > 0) {
		Biofarmar * biofarm = zoznamBiofarmarov_->removeAt(zoznamBiofarmarov_->size() - 1);
		delete biofarm;
	}
	delete zoznamBiofarmarov_;
}