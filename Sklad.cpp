#include "Sklad.h"
#include "heap_monitor.h"
#include <fstream>
#include <string>
#include <time.h>  

Sklad::Sklad()
{
	srand(time(NULL));
	zoznamBiofarmarov_ = new LinkedList<Biofarmar *>();
	zoznamVozidiel_ = new ArrayList<Vozidlo *>();
	zoznamZakaznikov_ = new ArrayList<Zakaznik*>();

	//OBJEDNAVKY
	zoznamCakajucichObjednavok_ = new ArrayList<Objednavka*>();
	zoznamZamietnutychObjednavok_ = new ArrayList<Objednavka*>();

	//OBJEDNAVKA POLOTOVARU
	zoznamObjednavokPolotovaru_ = new LinkedList<DodavkaSurovin*>();

	mnozstvoLupienkovNaSklade = 0;
	mnozstvoHranolcekovNaSklade = 0;
	mnozstvoOlejaNaSklade = 0;
	mnozstvoZemiakovNaSklade = 0;
	mnozstvoOchucovadlaNaSklade = 0;



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
		//polotovary = "";
		cout << "Spolocnost " << b->getObchodnyNazov() << endl;

		if (b->getZemiaky()) {
			cout << "Zemiaky: " << b->getPriemCenaZemiakov() << endl ;
		}
		if(b->getOlej()) {
			cout << "Olej: " << b->getPriemCenaOleja() << endl;

		}
		if (b->getOchucovadla()) {
			cout << "Ochucovadla: " << b->getPriemCenaOchucovadiel() << endl;

		}
		cout << endl;


		/*b->getZemiaky() ? polotovary += "zemiaky, " : polotovary += "";
		b->getOlej() ? polotovary += "olej, " : polotovary += "";
		b->getOchucovadla() ? polotovary += "ochucovadla" : polotovary += "";
		cout << "Nazov: " + b->getObchodnyNazov() + " - " + polotovary << endl;*/
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

	while (pomocnyListBiofarmarov_->size() > 0) {
		Biofarmar * obj = pomocnyListBiofarmarov_->operator[](pomocnyListBiofarmarov_->size() - 1);
		pomocnyListBiofarmarov_->removeAt(pomocnyListBiofarmarov_->size() - 1);
		delete obj;
	}
	pomocnyListBiofarmarov_->clear();
	delete pomocnyListBiofarmarov_;
}




void Sklad::usporiadajBofarmarovPodlaCenyPolotovarov(int typPolotovaru)
{
	// 1 = zemiaky, 2= olej, 3= ochucovadla
	switch (typPolotovaru) {
	case 1: {
		bubbleSortPodlaCenyZemiakov(zoznamBiofarmarov_, zoznamBiofarmarov_->size());
		break;
	}
	case 2:{
		bubbleSortPodlaCenyOleja(zoznamBiofarmarov_, zoznamBiofarmarov_->size());
		break;
	}
	case 3:{
		bubbleSortPodlaCenyOchucovadiel(zoznamBiofarmarov_, zoznamBiofarmarov_->size());
		break;
	}
	}
}



//bubble sort pre vozidla - usporiadanie pod¾a datumu
void Sklad::bubbleSortVozidiel(ArrayList <Vozidlo*> *linkedList, int size) { // O(n^2)
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (linkedList->operator[](j + 1)->getDatumZaciatkuEvidencie()->getDen() < linkedList->operator[](j)->getDatumZaciatkuEvidencie()->getDen()) {

				DSRoutines::swap(linkedList->operator[](j + 1), linkedList->operator[](j));
			}
		}
	}
}

bool Sklad::skontrolujNazovBiofarmara(string nazovBiofarmara) {
	for (Biofarmar *v : *zoznamBiofarmarov_) {
		if (v->getObchodnyNazov() == nazovBiofarmara) {
			return false;
		}
	}
	return true;
}

bool Sklad::skontrolujSPZ(string spz) {
	for (Vozidlo *v : *zoznamVozidiel_) {
		if (v->getSpz() == spz) {
			return false;
		}
	}
	return true;
}


void Sklad::pridajVozidlo(Vozidlo * vozidlo)
{
	zoznamVozidiel_->add(vozidlo);
	cout << "Vozidlo bolo uspesne pridane" << endl;
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

void Sklad::pridajZakaznika(Zakaznik * zakaznik) {
	zoznamZakaznikov_->add(zakaznik);
}
bool Sklad::skontrolujNazovZakaznika(string nazovZakaznika) {
	for (Zakaznik *z : *zoznamZakaznikov_) {
		if (z->getObchodnyNazov() == nazovZakaznika) {
			return false;
		}
	}
	return true;
}

void Sklad::vypisZakaznikov() {
	int i = 0;
	for (i; i < zoznamZakaznikov_->size(); i++) {
		cout << i+1 << ". " << zoznamZakaznikov_->operator[](i)->getObchodnyNazov() << endl;
	}
}

Zakaznik* Sklad::dajZakaznikaPodlaIndexu(int index) {
		return zoznamZakaznikov_->operator[](index);	
}

void Sklad::pridajSchvalenuObjednavku(Objednavka * objednavka) {
	//zoznamObjednavok_->push(objednavka->getDatumDorucenia()->getDen(), objednavka);
	zoznamCakajucichObjednavok_->add(objednavka);
}

void Sklad::vypisPoslednuObjednavku() {

	for (Objednavka * obj : *zoznamCakajucichObjednavok_) {
		cout << "Zakaznik: " << obj->getZakaznik().getObchodnyNazov() << "Den dorucenia:  " << obj->getDatumDorucenia()->getDen() << endl;

	}
}

//kontrola v ulohe èislo 6
bool Sklad::skontrolujDatumDorucenia(int denDorucenia, int aktualnyDen)
{
	if (denDorucenia < aktualnyDen + 7) {
		return false;
	}
	return true;
}
double Sklad::dajVolnuKapacituAut(int typObjednavky)
{
	int celkovaKapacitaVozidiel = 0;
	for (Vozidlo *vozidlo : *zoznamVozidiel_) {
		if (vozidlo->getTypVozidla() == typObjednavky) {
			celkovaKapacitaVozidiel += vozidlo->getNosnost();
		}
	}
	return celkovaKapacitaVozidiel;
}
double Sklad::dajHmotnostObjednavokNaDanyDen(int den) {
	double hmotnostObjednavok = 0
		;
	for (Objednavka * objednavka : *zoznamCakajucichObjednavok_) {
		if (objednavka->getDatumDorucenia()->getDen()==den) {
			hmotnostObjednavok += objednavka->getMnozstvoTovaru();
		}
	}
	return hmotnostObjednavok;
}

void Sklad::pridajZamietnutuObjednavku(Objednavka * objednavka)
{
	zoznamZamietnutychObjednavok_->add(objednavka);
}

void Sklad::aktualizujPriemerneNakupneCena(int aktualnyDen)
{
	for (Biofarmar * bio : *zoznamBiofarmarov_) {
		int pocetObjednavokOlejPreDanehoBio = 0;
		int pocetObjednavokOchucPreDanehoBio = 0;
		int pocetObjednavokZemiakyPreDanehoBio = 0;
		double jednotkovaCenaOlejSpolu = 0;
		double jednotkovaCenaOchucSpolu = 0;
		double jednotkovaCenaZemiakySpolu = 0;


		for (DodavkaSurovin * dodavkaSuriek : *zoznamObjednavokPolotovaru_) {
			if (dodavkaSuriek->getBiofarmar() == bio && dodavkaSuriek->getDatum()->getDen() >= aktualnyDen-30 ) {
				switch (dodavkaSuriek->getTypSuroviny()) { // 1 = zemiaky, 2= olej, 3= ochucovadla
				case 1: {
					pocetObjednavokZemiakyPreDanehoBio++;
					jednotkovaCenaZemiakySpolu += dodavkaSuriek->getJednotkovaCena();
					break;
				}
				case 2: {
					pocetObjednavokOlejPreDanehoBio++;
					jednotkovaCenaOlejSpolu += dodavkaSuriek->getJednotkovaCena();
					break;
				}
				case 3: {
					pocetObjednavokOchucPreDanehoBio++;
					jednotkovaCenaOchucSpolu += dodavkaSuriek->getJednotkovaCena();
					break;
				}
				}
				

			}
		}
		((jednotkovaCenaOchucSpolu / pocetObjednavokOchucPreDanehoBio) > 0) ? bio->setPriemCenaOchucovadiel(jednotkovaCenaOchucSpolu / pocetObjednavokOchucPreDanehoBio) : bio->setPriemCenaOchucovadiel(0);
		((jednotkovaCenaOlejSpolu / pocetObjednavokOlejPreDanehoBio) > 0) ?  bio->setPriemCenaOleja(jednotkovaCenaOlejSpolu / pocetObjednavokOlejPreDanehoBio) : bio->setPriemCenaOleja(0);
		((jednotkovaCenaZemiakySpolu / pocetObjednavokZemiakyPreDanehoBio) > 0) ? bio->setPriemCenaZemiakov(jednotkovaCenaZemiakySpolu / pocetObjednavokZemiakyPreDanehoBio) : bio->setPriemCenaZemiakov(0);
		//bio->setPriemCenaOchucovadiel(jednotkovaCenaOchucSpolu / pocetObjednavokOlejPreDanehoBio);
		//bio->setPriemCenaOleja(jednotkovaCenaOlejSpolu / pocetObjednavokOlejPreDanehoBio);
		//bio->setPriemCenaZemiakov(jednotkovaCenaZemiakySpolu / pocetObjednavokZemiakyPreDanehoBio);
	}
}

void Sklad::nakupPolotovar(DodavkaSurovin * objednavkaPolotovarov)
{
	zoznamObjednavokPolotovaru_->add(objednavkaPolotovarov);

}
// 1 = Lupienky, 2 = Hranolceky
int Sklad::dajObjednanyPocetHranoliek(int den)
{
	double objednaneMnozstvo = 0;
	for (Objednavka * obj : * zoznamCakajucichObjednavok_) {
		if ((obj->getTypTovaru() == 2) && (obj->getDatumDorucenia()->getDen()<den+7)) {
			objednaneMnozstvo += obj->getMnozstvoTovaru();
		}
	}
	return objednaneMnozstvo - mnozstvoHranolcekovNaSklade;
}

int Sklad::dajObjednanyPocetLupienkov(int den)
{
	
	double objednaneMnozstvo = 0;
	for (Objednavka * obj : *zoznamCakajucichObjednavok_) {
		if ((obj->getTypTovaru() == 1) && (obj->getDatumDorucenia()->getDen()<den + 7)) {
			objednaneMnozstvo += obj->getMnozstvoTovaru();
		}
	}
	return objednaneMnozstvo - mnozstvoLupienkovNaSklade;

}

void Sklad::zabezpecOlej(double mnozstvoOleja, int den)
{
	bubbleSortPodlaCenyOleja(zoznamBiofarmarov_, zoznamBiofarmarov_->size());
	double mnozstvoKupenehoOleja = mnozstvoOlejaNaSklade; //ak nam ostal nejaky zostatkovy olej náhodou ?
	for (Biofarmar * bio : *zoznamBiofarmarov_) {
		if (bio->getOlej() && mnozstvoOleja > mnozstvoKupenehoOleja) { //mnozstvo potrebneho oleja na 7 dni je > ako aktualne mnozstvo na sklade
			double randomMnzostvoOleja = dajRandomCislo(0, 1000);
			nakupPolotovar(new DodavkaSurovin(bio, 2,randomMnzostvoOleja,dajRandomCislo(1,4), new Den(den)));
			mnozstvoKupenehoOleja += randomMnzostvoOleja;
			cout << "Biofarmar " << bio->getObchodnyNazov() << "nakúpil " << randomMnzostvoOleja << "l oleja." << endl;
		}
	}
	mnozstvoOlejaNaSklade = mnozstvoKupenehoOleja;

}

void Sklad::zabezpecZemiaky(double mnozstvoZemiakov, int den)
{
	bubbleSortPodlaCenyZemiakov(zoznamBiofarmarov_, zoznamBiofarmarov_->size());
	double mnozstvoKupenychZemiakov = mnozstvoZemiakovNaSklade;
	for (Biofarmar * bio : *zoznamBiofarmarov_) {
		if (bio->getZemiaky() && mnozstvoZemiakov > mnozstvoKupenychZemiakov) {
			double randomMnozstvoZemiakov = dajRandomCislo(0, 5000);
			nakupPolotovar(new DodavkaSurovin(bio, 1, randomMnozstvoZemiakov, dajRandomCislo(1, 3), new Den(den)));
			mnozstvoKupenychZemiakov += randomMnozstvoZemiakov;
			cout << "Biofarmar " << bio->getObchodnyNazov() << "nakúpil " << randomMnozstvoZemiakov << "kg zemiakov." << endl;
		}
	}
	mnozstvoZemiakovNaSklade = mnozstvoKupenychZemiakov;

}

void Sklad::zabezpecOchucovadla(double mnozstvoOchucovadiel, int den)
{
	bubbleSortPodlaCenyOchucovadiel(zoznamBiofarmarov_, zoznamBiofarmarov_->size());
	double mnozstvoKupenychOchucovadiel = mnozstvoOchucovadlaNaSklade;
	for (Biofarmar * bio : *zoznamBiofarmarov_) {
		if (bio->getOchucovadla() && mnozstvoOchucovadiel > mnozstvoKupenychOchucovadiel) { 
			double randomMnozstvoOchucovadiel = dajRandomCislo(0, 1000);
			nakupPolotovar(new DodavkaSurovin(bio, 3, randomMnozstvoOchucovadiel, dajRandomCislo(1, 2), new Den(den)));
			mnozstvoKupenychOchucovadiel += randomMnozstvoOchucovadiel;
			cout << "Biofarmar " << bio->getObchodnyNazov() << "nakupil " << randomMnozstvoOchucovadiel << "kg ochucovadiel." << endl;
		}
	}
	mnozstvoOchucovadlaNaSklade = mnozstvoKupenychOchucovadiel;

}

//vracia random double zaokruhlene na dve desatinné miesta
double Sklad::dajRandomCislo(double min, double max)
{	
		double f = (double)rand() / RAND_MAX;
		return round(((min + f * (max - min)) * 100) / 100);
}

void Sklad::vyrobTovar()
{

}

double Sklad::getMnozstvoOlejaNaSklade()
{
	return mnozstvoOlejaNaSklade;
}

double Sklad::getMnozstvoOchucovadielNaSklade()
{
	return mnozstvoOchucovadlaNaSklade;
}

double Sklad::getMnozstvoZemiakovNaSklade()
{
	return mnozstvoZemiakovNaSklade;
}

Sklad::~Sklad()
{
	//zmazanie biofarmarov

	while (zoznamBiofarmarov_->size() > 0) {
		Biofarmar * b = zoznamBiofarmarov_->removeAt(zoznamBiofarmarov_->size() - 1);
		delete b;
	}
	delete zoznamBiofarmarov_;


	//zmazanie vozidiel
	while (zoznamVozidiel_->size() > 0) {

		Vozidlo * vozidlo = zoznamVozidiel_->operator[](zoznamVozidiel_->size() - 1);
		delete vozidlo->getDatumZaciatkuEvidencie();
		zoznamVozidiel_->removeAt(zoznamVozidiel_->size() - 1);
		delete vozidlo;
	}
	zoznamVozidiel_->clear();
	delete zoznamVozidiel_;


	while (zoznamZakaznikov_->size() > 0) {
		Zakaznik * zak = zoznamZakaznikov_->operator[](zoznamZakaznikov_->size() - 1);
		zoznamZakaznikov_->removeAt(zoznamZakaznikov_->size() - 1);
		delete zak;
	}
	zoznamZakaznikov_->clear();
	delete zoznamZakaznikov_;


	while (zoznamCakajucichObjednavok_->size() > 0) {
		Objednavka * obj = zoznamCakajucichObjednavok_->operator[](zoznamCakajucichObjednavok_->size() - 1);
		zoznamCakajucichObjednavok_->removeAt(zoznamCakajucichObjednavok_->size() - 1);
		delete obj;
	}
	zoznamCakajucichObjednavok_->clear();
	delete zoznamCakajucichObjednavok_;


	// pre heap 
	//while (zoznamObjednavok_->size() > 0) {
	//	Objednavka *objednavka = zoznamObjednavok_->pop();
	//	delete objednavka->getDatumDorucenia();
	//	delete objednavka->getDatumZaevidovania();
	//	delete objednavka;
	//}
	//delete zoznamObjednavok_;



}

//BUBBLE SORTY
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

void Sklad::bubbleSortPodlaCenyZemiakov(LinkedList<Biofarmar*>* linkedList, int size)
{
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (linkedList->operator[](j + 1)->getPriemCenaZemiakov() < linkedList->operator[](j)->getPriemCenaZemiakov()) {

				DSRoutines::swap(linkedList->operator[](j + 1), linkedList->operator[](j));
			}
		}
	}
}

void Sklad::bubbleSortPodlaCenyOleja(LinkedList<Biofarmar*>* linkedList, int size)
{
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (linkedList->operator[](j + 1)->getPriemCenaOleja() < linkedList->operator[](j)->getPriemCenaOleja()) {

				DSRoutines::swap(linkedList->operator[](j + 1), linkedList->operator[](j));
			}
		}
	}
}


void Sklad::bubbleSortPodlaCenyOchucovadiel(LinkedList<Biofarmar*>* linkedList, int size)
{
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (linkedList->operator[](j + 1)->getPriemCenaOchucovadiel() < linkedList->operator[](j)->getPriemCenaOchucovadiel()) {

				DSRoutines::swap(linkedList->operator[](j + 1), linkedList->operator[](j));
			}
		}
	}
}