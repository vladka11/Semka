#include "Sklad.h"
#include "heap_monitor.h"
#include <fstream>

Sklad::Sklad()
{
	zoznamBiofarmarov_ = new LinkedList<Biofarmar *>();
}


/*
 ULOHA è.1 - pridanie biofarmara*/
void Sklad::pridajBiofarmara(Biofarmar * biofarmar)
{
	zoznamBiofarmarov_->add(biofarmar);
}

void Sklad::vypisBiofarmarov()
{
	cout << "BIOFARMARI: \n----------------------------------------\n " << endl;
	bubbleSort(zoznamBiofarmarov_, zoznamBiofarmarov_->size());
	for (Biofarmar* b : *zoznamBiofarmarov_) {
		cout << "Názov: " + b->getObchodnyNazov() << endl;
	}
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

Sklad::~Sklad()
{
	//zmazanie biofarmarov
	if (zoznamBiofarmarov_->size() > 0) {
		Biofarmar * biofarm = zoznamBiofarmarov_->removeAt(zoznamBiofarmarov_->size() - 1);
		delete biofarm;
	}
	delete zoznamBiofarmarov_;
}