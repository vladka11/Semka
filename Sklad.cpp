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
	zoznamZrusenychObjednavok_ = new ArrayList<Objednavka *>();
	zoznamZrealizovanychObjednavok_ = new ArrayList<Objednavka *>();

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
		//delete obj;
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
			double randomMnozstvoOchucovadiel = dajRandomCislo(0, 50000);
			nakupPolotovar(new DodavkaSurovin(bio, 3, randomMnozstvoOchucovadiel, dajRandomCislo(1000, 2000), new Den(den)));
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
		return round((min + f * (max - min)) * 100) / 100;
}

void Sklad::dajZajtrajsieObjednavky(int den)
{
	bubbleSortObjednavokPodlaTrzby(zoznamCakajucichObjednavok_, zoznamCakajucichObjednavok_->size());
	ArrayList<Objednavka*>* zoznamNaZmazanie= new ArrayList<Objednavka*>();
	//LinkedList<Biofarmar *>* pomocnyListBiofarmarov_ = new LinkedList<Biofarmar*>();


	double olej =0, zemiaky=0, ochucovadla = 0;
	int size = zoznamCakajucichObjednavok_->size();
	for (int i = 0; i < size; i++)
	{
	//for (Objednavka* objednavka : *zoznamCakajucichObjednavok_) {
		if (zoznamCakajucichObjednavok_->operator[](i)->getDatumDorucenia()->getDen() == den) {
			cout << "Zakaznik: " << zoznamCakajucichObjednavok_->operator[](i)->getZakaznik().getObchodnyNazov() << " z regionu c." << zoznamCakajucichObjednavok_->operator[](i)->getZakaznik().getCisloRegionu() << endl;
			cout << "Datum zaevidovania: " << zoznamCakajucichObjednavok_->operator[](i)->getDatumZaevidovania()->getDen() << endl;
			cout << "Mnozstvo: " << zoznamCakajucichObjednavok_->operator[](i)->getMnozstvoTovaru() << endl;
			cout << "Jednotkova cena: " << zoznamCakajucichObjednavok_->operator[](i)->getJednotkovaCena() << endl;
			cout << "Celkove trzby: " << zoznamCakajucichObjednavok_->operator[](i)->getJednotkovaCena()*zoznamCakajucichObjednavok_->operator[](i)->getMnozstvoTovaru() << endl;

			switch (zoznamCakajucichObjednavok_->operator[](i)->getTypTovaru()) {
			case 1: { //lupienky
				cout << "Typ tovaru: lupienky" << endl;
				olej += zoznamCakajucichObjednavok_->operator[](i)->getMnozstvoTovaru()*0.4;
				zemiaky += zoznamCakajucichObjednavok_->operator[](i)->getMnozstvoTovaru() * 2;
				ochucovadla += zoznamCakajucichObjednavok_->operator[](i)->getMnozstvoTovaru() * 20;
				if (olej < getMnozstvoOlejaNaSklade() && zemiaky < getMnozstvoZemiakovNaSklade() && ochucovadla < getMnozstvoOchucovadielNaSklade()) {
					cout << "Objednavka NEBUDE zrusena kvoli nedostatku tovaru" << endl << endl;
				}
				else {
					cout << "Objednavka BUDE zrusena kvoli nedostatku tovaru" << endl << endl;
					olej -= zoznamCakajucichObjednavok_->operator[](i)->getMnozstvoTovaru()*0.4;
					zemiaky -= zoznamCakajucichObjednavok_->operator[](i)->getMnozstvoTovaru() * 2;
					ochucovadla -= zoznamCakajucichObjednavok_->operator[](i)->getMnozstvoTovaru() * 20;
					zoznamZrusenychObjednavok_->add(zoznamCakajucichObjednavok_->operator[](i));
					zoznamNaZmazanie->add(zoznamCakajucichObjednavok_->operator[](i));
					//zoznamCakajucichObjednavok_->tryRemove(zoznamCakajucichObjednavok_->operator[](i));

				}
				break;
			} 
			case 2: { //hranolky
				cout << "Typ tovaru: hranolky" << endl;
				olej += 0.2 * zoznamCakajucichObjednavok_->operator[](i)->getMnozstvoTovaru();
				zemiaky += 1.5 * zoznamCakajucichObjednavok_->operator[](i)->getMnozstvoTovaru();
				if (olej < getMnozstvoOlejaNaSklade() && zemiaky < getMnozstvoZemiakovNaSklade()) {
					cout << "Objednavka NEBUDE zrusena kvoli nedostatku tovaru" << endl << endl;
				}
				else {
					cout << "Objednavka BUDE zrusena kvoli nedostatku tovaru" << endl << endl;
					olej -= 0.2 * zoznamCakajucichObjednavok_->operator[](i)->getMnozstvoTovaru();
					zemiaky -= 1.5 * zoznamCakajucichObjednavok_->operator[](i)->getMnozstvoTovaru();
					zoznamZrusenychObjednavok_->add(zoznamCakajucichObjednavok_->operator[](i));
					zoznamNaZmazanie->add(zoznamCakajucichObjednavok_->operator[](i));

					//zoznamCakajucichObjednavok_->tryRemove(zoznamCakajucichObjednavok_->operator[](i));
				}
				break;
			}
			}
		}

	}
	for (Objednavka * obj : *zoznamNaZmazanie) {
		zoznamCakajucichObjednavok_->tryRemove(obj);
	}

	while (zoznamNaZmazanie->size() > 0) {
		Objednavka * obj = zoznamNaZmazanie->operator[](zoznamNaZmazanie->size() - 1);
		zoznamNaZmazanie->removeAt(zoznamNaZmazanie->size() - 1);
		//delete obj;
	}
	zoznamNaZmazanie->clear();
	delete zoznamNaZmazanie;


}

void Sklad::bubbleSortObjednavokPodlaTrzby(ArrayList<Objednavka*>* linkedList, int size)
{
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (linkedList->operator[](j + 1)->getJednotkovaCena() *linkedList->operator[](j + 1)->getMnozstvoTovaru() > linkedList->operator[](j)->getJednotkovaCena()*linkedList->operator[](j)->getMnozstvoTovaru()) {

				DSRoutines::swap(linkedList->operator[](j + 1), linkedList->operator[](j));
			}
		}
	}
}

void Sklad::naplnVozidla(int den)
{
	ArrayList<Objednavka*>* dnesneObjednavkyLupienkov = new ArrayList<Objednavka*>();
	ArrayList<Objednavka*>* dnesneObjednavkyHranoliek = new ArrayList<Objednavka*>();

	//rozdelenie dnešných objednávok do pomocných arraylistov
	for each (Objednavka *obj  in *zoznamCakajucichObjednavok_) {
		if (obj->getDatumDorucenia()->getDen() == den) {
			switch (obj->getTypTovaru()) {
			case 1: { // 1 = Lupienky
				dnesneObjednavkyLupienkov->add(obj);
				break;
			}
			case 2: { // 2 = Hranolceky
				dnesneObjednavkyHranoliek->add(obj);
				break;
			}
			}
		}
	}

	//zmazanie tých èo sme presunuli do vozidiel už
	for each (Objednavka *obj  in *zoznamCakajucichObjednavok_) {
		if (obj->getDatumDorucenia()->getDen() == den) {
			zoznamCakajucichObjednavok_->tryRemove(obj);
		}
	}

	//zosortovanie objednavok pod¾a èísla regionu od najväèšieho po najmenší
	zosortujObjednavkyPodlaRegionu(dnesneObjednavkyHranoliek);
	zosortujObjednavkyPodlaRegionu(dnesneObjednavkyLupienkov);

	for each (Vozidlo * voz in *zoznamVozidiel_)
	{
	
		if (voz->getTypVozidla() == 1) {
			for each (Objednavka* obj in *dnesneObjednavkyLupienkov)
			{
				if (voz->getNosnost() >= obj->getMnozstvoTovaru() && obj->getStav()==0) {
					voz->getTovarVoVozidle()->push(obj);
					voz->setNosnost(voz->getNosnost() - obj->getMnozstvoTovaru());
					obj->setStav(1);
					setMnozstvoOlejaNaSklade(getMnozstvoOlejaNaSklade() - obj->getMnozstvoTovaru()*0.4);
					setMnozstvoOchucovadielNaSklade(getMnozstvoOchucovadielNaSklade() - obj->getMnozstvoTovaru() * 20);
					setMnozstvoZemiakovNaSklade(getMnozstvoZemiakovNaSklade() - obj->getMnozstvoTovaru() * 2);
				    cout << "Do vozidla s spz: " << voz->getSpz() << "sme nalozili lupienky v mnozstve: " << obj->getMnozstvoTovaru() << "kg" <<endl;
					cout << "Dana objednavka bola od zakaznika " << obj->getZakaznik().getObchodnyNazov() << " z regionu " << obj->getZakaznik().getCisloRegionu() << endl;
					cout << "Nosnost vozidla je teraz: " << voz->getNosnost() << endl;
					cout << "------------------------------------" << endl;
				}
			}
		}
		if (voz->getTypVozidla() == 2) {
			for each (Objednavka* obj in *dnesneObjednavkyHranoliek)
			{
				if (voz->getNosnost() >= obj->getMnozstvoTovaru() && obj->getStav() == 0) {
					voz->getTovarVoVozidle()->push(obj);
					voz->setNosnost(voz->getNosnost() - obj->getMnozstvoTovaru());
					obj->setStav(1);
					setMnozstvoZemiakovNaSklade(getMnozstvoZemiakovNaSklade() - obj->getMnozstvoTovaru()*1.5);
					setMnozstvoOlejaNaSklade(getMnozstvoOlejaNaSklade() - obj->getMnozstvoTovaru()*0.2);
					cout << "Do vozidla s spz: " << voz->getSpz() << "sme nalozili hranolky v mnozstve: " << obj->getMnozstvoTovaru() << "kg" << endl;
					cout << "Dana objednavka bola od zakaznika " << obj->getZakaznik().getObchodnyNazov() << " z regionu " << obj->getZakaznik().getCisloRegionu() << endl;
 					cout << "Nosnost vozidla je teraz: " << voz->getNosnost() << endl;
					cout << "------------------------------------" << endl;
				}
			}
		}
	}


	//deštruktor pre lokalne premenné

	while (dnesneObjednavkyHranoliek->size() > 0) {
		Objednavka * obj = dnesneObjednavkyHranoliek->operator[](dnesneObjednavkyHranoliek->size() - 1);
		dnesneObjednavkyHranoliek->removeAt(dnesneObjednavkyHranoliek->size() - 1);
		//delete obj;
	}
	dnesneObjednavkyHranoliek->clear();
	delete dnesneObjednavkyHranoliek;

	while (dnesneObjednavkyLupienkov->size() > 0) {
		Objednavka * obj = dnesneObjednavkyLupienkov->operator[](dnesneObjednavkyLupienkov->size() - 1);
		dnesneObjednavkyLupienkov->removeAt(dnesneObjednavkyLupienkov->size() - 1);
		//delete obj;
	}
	dnesneObjednavkyLupienkov->clear();
	delete dnesneObjednavkyLupienkov;
}

void Sklad::naplnVozidlaOstatnymiObjednavkami()
{
	zosortujObjednavkyPodlaDatumuDorucenia(zoznamCakajucichObjednavok_);
	cout << "Objednavky pridane z dalsieho dna" << endl;
	cout << "---------------------------------" << endl;
	for (Vozidlo * voz : *zoznamVozidiel_) {
		for (Objednavka * obj : *zoznamCakajucichObjednavok_) {
			if (voz->getTovarVoVozidle()->size() > 0
				&& voz->getNosnost() >= obj->getMnozstvoTovaru()
				&& voz->getTovarVoVozidle()->peek()->getZakaznik().getCisloRegionu() == obj->getZakaznik().getCisloRegionu()
				&& voz->getTypVozidla() == obj->getTypTovaru()
				&& obj->getStav() == 0)
			{
				voz->getTovarVoVozidle()->push(obj);
				obj->setStav(1);
				voz->setNosnost(voz->getNosnost() - obj->getMnozstvoTovaru());

				if (obj->getTypTovaru() == 1) {
					setMnozstvoOlejaNaSklade(getMnozstvoOlejaNaSklade() - obj->getMnozstvoTovaru()*0.4);
					setMnozstvoOchucovadielNaSklade(getMnozstvoOchucovadielNaSklade() - obj->getMnozstvoTovaru() * 20);
					setMnozstvoZemiakovNaSklade(getMnozstvoZemiakovNaSklade() - obj->getMnozstvoTovaru() * 2);
					cout << "Do vozidla s spz: " << voz->getSpz() << "sme nalozili lupienky v mnozstve: " << obj->getMnozstvoTovaru() << "kg" << endl;;
				} 
				else{
					setMnozstvoZemiakovNaSklade(getMnozstvoZemiakovNaSklade() - obj->getMnozstvoTovaru()*1.5);
					setMnozstvoOlejaNaSklade(getMnozstvoOlejaNaSklade() - obj->getMnozstvoTovaru()*0.2);
					cout << "Do vozidla s spz: " << voz->getSpz() << "sme nalozili hranolky v mnozstve: " << obj->getMnozstvoTovaru() << "kg" << endl;;
				}

				cout << "Dana objednavka bola od zakaznika " << obj->getZakaznik().getObchodnyNazov() << " z regionu " << obj->getZakaznik().getCisloRegionu() << endl;
				cout << "Nosnost vozidla je teraz: " << voz->getNosnost() << endl;
				cout << "------------------------------------" << endl;
			}

		}

	}

	for (Objednavka * obj : *zoznamCakajucichObjednavok_) {
		if (obj->getStav() == 1) {
			zoznamCakajucichObjednavok_->tryRemove(obj);
		}
		}
}

void Sklad::zosortujObjednavkyPodlaRegionu(ArrayList<Objednavka*>* objednavky)
{
	int size = objednavky->size();
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (objednavky->operator[](j + 1)->getZakaznik().getCisloRegionu() > objednavky->operator[](j)->getZakaznik().getCisloRegionu()) {

				DSRoutines::swap(objednavky->operator[](j + 1), objednavky->operator[](j));
			}
		}
	}
}

void Sklad::zosortujObjednavkyPodlaDatumuDorucenia(ArrayList<Objednavka*>* objednavky)
{
	int size = objednavky->size();
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (objednavky->operator[](j + 1)->getDatumDorucenia() < objednavky->operator[](j)->getDatumDorucenia()) {

				DSRoutines::swap(objednavky->operator[](j + 1), objednavky->operator[](j));
			}
		}
	}
}

void Sklad::vypisSkladu() {

	cout << "VYPIS POLOTOVAROV NA SKLADE" << endl;
	cout << "OLEJ: " << getMnozstvoOlejaNaSklade() << endl;
	cout << "ZEMIAKY: " << getMnozstvoZemiakovNaSklade() << endl;
	cout << "OCHUCOVADLA: " << getMnozstvoOchucovadielNaSklade() << endl;
}

void Sklad::vylozVozidla()
{
	for each (Vozidlo * voz in *zoznamVozidiel_)
	{
		int aktRegion = 0;
		int pocetRegionov = 0;
		Objednavka *obj;

		if (voz->getTovarVoVozidle()->size() > 0){
		while (voz->getTovarVoVozidle()->size() > 0) {
			obj= voz->getTovarVoVozidle()->pop();
			zoznamZrealizovanychObjednavok_->add(obj);
			//zistenie poètu regionov v ktorych vozidlo bolo	
			if (aktRegion < obj->getZakaznik().getCisloRegionu()) {
				pocetRegionov++;
				aktRegion = obj->getZakaznik().getCisloRegionu();
			}

		}

		cout << "Tovar z vozidla s spz " << voz->getSpz() << " bol uspesne odovzdany " << endl;
		if (voz->getTypVozidla() == 1) {
			voz->setNosnost(2000);
			voz->setNaklady(voz->getNaklady() + 70 * pocetRegionov);
			cout << "Celkove naklady vozidla su " << voz->getSpz() << " su " << voz->getNaklady() << "eur"<<endl;
		}
		else if (voz->getTypVozidla() == 2) {
			voz->setNosnost(5000);
			voz->setNaklady(voz->getNaklady() + 100 * pocetRegionov);
			cout << "Celkove naklady vozidla su " << voz->getSpz() << " su " << voz->getNaklady() << "eur"<<endl;

		}
		}
	}
}

void Sklad::vypisZakaznikov(int region, int denOd, int denDo)
{
	bubbleSortZakanikovPodlaAbc(zoznamZakaznikov_, zoznamZakaznikov_->size());
	cout << "Zakaznici z regionu " + region << endl;
	cout << endl;
	for (Zakaznik *zak : *zoznamZakaznikov_) {
		if (zak->getCisloRegionu() == region) {
			int celkovyPrijem = 0;
			for (Objednavka *obj : *zoznamZrealizovanychObjednavok_) {
				if (obj->getZakaznik().getObchodnyNazov() == zak->getObchodnyNazov()
					&& obj->getDatumDorucenia()->getDen() >= denOd
					&& obj->getDatumDorucenia()->getDen() <= denDo) {
					celkovyPrijem += obj->getJednotkovaCena()*obj->getMnozstvoTovaru();
				}
			}
			int pocetZrus= 0;
			int hmotnostZrus = 0;
			int trzbyZrus = 0;
			for (Objednavka *obj : *zoznamZrusenychObjednavok_) {
				if (obj->getZakaznik().getObchodnyNazov() == zak->getObchodnyNazov()) {
					pocetZrus++;
					hmotnostZrus += obj->getMnozstvoTovaru();
					trzbyZrus += obj->getMnozstvoTovaru()*obj->getJednotkovaCena();
				}
			}

			int pocetZam = 0;
			int hmotnostZam = 0;
			int trzbyZam = 0;
			for (Objednavka *obj : *zoznamZamietnutychObjednavok_){
				if (obj->getZakaznik().getObchodnyNazov() == zak->getObchodnyNazov()) {
					pocetZam++;
					hmotnostZam += obj->getMnozstvoTovaru();
					trzbyZam += obj->getMnozstvoTovaru()*obj->getJednotkovaCena();
				}

			}
				cout << "Zakaznik: " << zak->getObchodnyNazov() << endl;
				cout << "Celkovy prijem zo zrealizovanych: " << celkovyPrijem << endl;
				cout << "Pocet zrusenych: " << pocetZrus << endl;
				cout << "Hmotnost: " << hmotnostZrus << endl;
				cout << "Celkove trzby: " << trzbyZrus << endl;
				
				cout << "Pocet zrusenych: " << pocetZam << endl;
				cout << "Hmotnost: " << hmotnostZam << endl;
				cout << "Celkove trzby: " << trzbyZam << endl;
				cout << endl;
		}
	}

}

void Sklad::vypisZrealizovaneObjednavky(int denOd, int denDo)
{
	cout << "ZREALIZOVANE OBJEDNAVKY" << endl;
	for (Objednavka *obj : *zoznamZrealizovanychObjednavok_) {
		if (denOd <= obj->getDatumDorucenia()->getDen() && denDo >= obj->getDatumDorucenia()->getDen()) {
			cout << "Zakaznik: " << obj->getZakaznik().getObchodnyNazov() << endl;
			cout << "Datum realizacie: " << obj->getDatumDorucenia()->getDen() << endl;
			cout << "Typ produktu: " << obj->getTypTovaru() << endl;
			cout << "Mnozstvo: " << obj->getMnozstvoTovaru() << endl;
			cout << "Celkove trzby: " << obj->getMnozstvoTovaru()*obj->getJednotkovaCena() << endl;
			cout << endl;
		}
	
	}
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

void Sklad::setMnozstvoOlejaNaSklade(double mnozstvo)
{
	mnozstvoOlejaNaSklade = mnozstvo;
}

void Sklad::setMnozstvoOchucovadielNaSklade(double mnozstvo)
{
	mnozstvoOchucovadlaNaSklade = mnozstvo;
}

void Sklad::setMnozstvoZemiakovNaSklade(double mnozstvo)
{
	mnozstvoZemiakovNaSklade = mnozstvo;
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
		delete obj->getDatumDorucenia();
		delete obj->getDatumZaevidovania();
		zoznamCakajucichObjednavok_->removeAt(zoznamCakajucichObjednavok_->size() - 1);
		delete obj;
	}
	zoznamCakajucichObjednavok_->clear();
	delete zoznamCakajucichObjednavok_;

	while (zoznamObjednavokPolotovaru_->size() > 0) {
		DodavkaSurovin * obj = zoznamObjednavokPolotovaru_->operator[](zoznamObjednavokPolotovaru_->size() - 1);
		delete obj->getDatum();
	    zoznamObjednavokPolotovaru_->removeAt(zoznamObjednavokPolotovaru_->size() - 1);
		delete obj;
	}
	zoznamObjednavokPolotovaru_->clear();
	delete zoznamObjednavokPolotovaru_;

	while (zoznamZrusenychObjednavok_->size() > 0) {
		Objednavka * obj = zoznamZrusenychObjednavok_->operator[](zoznamZrusenychObjednavok_->size() - 1);
		delete obj->getDatumDorucenia();
		delete obj->getDatumZaevidovania();
		zoznamZrusenychObjednavok_->removeAt(zoznamZrusenychObjednavok_->size() - 1);
		delete obj;
	}
	zoznamZrusenychObjednavok_->clear();
	delete zoznamZrusenychObjednavok_;


	while (zoznamZamietnutychObjednavok_->size() > 0) {
		Objednavka * obj = zoznamZamietnutychObjednavok_->operator[](zoznamZamietnutychObjednavok_->size() - 1);
		delete obj->getDatumDorucenia();
		delete obj->getDatumZaevidovania();
		zoznamZamietnutychObjednavok_->removeAt(zoznamZamietnutychObjednavok_->size() - 1);
		delete obj;
	}
	zoznamZamietnutychObjednavok_->clear();
	delete zoznamZamietnutychObjednavok_;

	while (zoznamZrealizovanychObjednavok_->size() > 0) {
		Objednavka * obj = zoznamZrealizovanychObjednavok_->operator[](zoznamZrealizovanychObjednavok_->size() - 1);
		delete obj->getDatumDorucenia();
		delete obj->getDatumZaevidovania();
		zoznamZrealizovanychObjednavok_->removeAt(zoznamZrealizovanychObjednavok_->size() - 1);
		delete obj;
	}
	zoznamZrealizovanychObjednavok_->clear();
	delete zoznamZrealizovanychObjednavok_;

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

void Sklad::bubbleSortZakanikovPodlaAbc(ArrayList<Zakaznik*>* arrayList, int size)
{
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arrayList->operator[](j + 1)->getObchodnyNazov() < arrayList->operator[](j)->getObchodnyNazov()) {

				DSRoutines::swap(arrayList->operator[](j + 1), arrayList->operator[](j));
			}
		}
	}
}