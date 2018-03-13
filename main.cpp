// SemPraca2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Sklad.h"
#include "Den.h"
#include "heap_monitor.h"

using namespace std;

//kontrola pri vkladani biofarmara, zadana hodnota musi byt 1/0 (1=ano,0=nie)
bool kontrolaCisla(int hodnota) {
	if (hodnota == 0 || hodnota == 1) {
		return true;
	}
	cout << "\n Zadana hodnota nie je spravna, prosim zadajte len cislo 1/0. \n";
	return false;
}

bool konverziaIntToBool(int cislo) {
	if (cislo == 1) {
		return true;
	}
	return false;
}
void main()
{
	//initHeapMonitor(); 
	Sklad * sklad = new Sklad();
	Den * den = new Den(1);

	while (1) {
		cout << "----------------------------------------\n \t\t MENU \n----------------------------------------\n";
		cout << "1. Pridaj noveho biofarmara \n";
		cout << "2. Vypis zoznam biofarmarov v abecednom poradi \n";
		cout << "3. Pridaj nove vozidlo  \n";
		cout << "4. Vypis zoznam vozidiel podla datumu zaradenia do evidencie \n";
		cout << "5. Pridaj noveho zakaznika \n";


		cout << "\n-----Nacitavenie z txt-------" << endl;
		cout << "|90. Nacitaj biofarmarov       |" << endl;
		cout << "|91. Nacitaj vozidla           |" << endl;
		//cout << "|92. Nacitaj vozidla z txt     |" << endl;
		cout << "--------------------------------" << endl;
		int vyber;
		cin >> vyber;

		switch (vyber) {
		case 1: {
			string nazovSpolocnosti;
			int zemiaky;
			int olej;
			int ochucovadla;
			cin.ignore();

			cout << "Volba 1: Pridanie noveho biofarmara \n----------------------------------------\n" << endl;
			cout << "Zadaj obchodny nazov spolocnosti:" << endl;;
			getline(cin, nazovSpolocnosti);
			cout << "Je biofarmar dodavatelom zemiakov? (Vloz 1=ano/0=nie)" << endl;
			cin >> zemiaky;
			if (kontrolaCisla(zemiaky) == false) { main(); }

			cout << "Je biofarmar dodavatelom oleja? (Vloz 1=ano/0=nie)" << endl;
			cin >> olej;
			if (kontrolaCisla(olej) == false) { break; }

			cout << "Je biofarmar dodavatelom ochucovadiel? (Vlož 1=ano/0=nie)" << endl;
			cin >> ochucovadla;
			if (kontrolaCisla(ochucovadla) == false) { break; }

			if (sklad->skontrolujNazovBiofarmara(nazovSpolocnosti)) {
				sklad->pridajBiofarmara(new Biofarmar(nazovSpolocnosti, konverziaIntToBool(zemiaky), konverziaIntToBool(olej), konverziaIntToBool(ochucovadla)));
				cout << "Biofarmar bol uspesne pridany" << endl;
			}
			else {
				cout << "Biofarmar uz exituje." << endl;
			}
			
			break;
		}
		case 2: {
			int volba;
			cout << "Volba 2: Výpis biofarmárov \n----------------------------------------\n" << endl;
			cout << "Vyber moznost pre vypisanie:" << endl;
			cout << "1: vypis vsetkych biofarmarov" << endl;
			cout << "2. vypis dodavatelov oleja" << endl;
			cout << "3. vypis dodavatelov zemiakov" << endl;
			cout << "4. vypis dodavatelov ochucovadiel" << endl;

			cin >> volba;

			sklad->vypisUrcitychBiofarmarov(volba);

			break;
		}
		case 3: {
			string spz;
			int typVozidla;
			int nosnost;
			cout << "Volba 2: Pridanie noveho vozidla \n----------------------------------------\n" << endl;
			cout << "Zadaj spz vozidla: " << endl;
			cin >> spz;
			cout << "Co bude vozidlo rozvazat? 1 = Lupienky, 2 = Hranolceky" << endl;
			cin >> typVozidla;
			if (typVozidla == 1) {
				nosnost = 2;
			}else {
				nosnost = 5;
			}
			if (sklad->skontrolujSPZ(spz)) {
				sklad->pridajVozidlo(new Vozidlo(spz, typVozidla, nosnost, 0, new Den(den->getDen())));
			}
		else {
				cout << "Zadane vozidlo uz existuje." << endl;
			}
			
			
			break;
		}
		case 4: {
			cout << "Volba 4: Vypis vsetkych vozidiel \n----------------------------------------\n" << endl;
			sklad->vypisVozidla();
			break;
		}

		case 5: {
			string obchodnyNazov;
			int region;
			cout << "Volba 5: Registracia noveho zakaznika \n----------------------------------------\n" << endl;
			cout << "Zadaj obchodny nazov zakaznika: " << endl;
			cin >> obchodnyNazov;
			cout << "Zadaj region v ktorom sa zakaznik nachadza: " << endl;
			cin >> region;
			 
			if (sklad->skontrolujNazovZakaznika(obchodnyNazov)) {
				sklad->pridajZakaznika(new Zakaznik(obchodnyNazov, region));
					cout << "Zakaznik bol uspecne pridany" << endl;	
			}
			else {
				cout << "Zadany zakaznik uz existuje" << endl;
			}

			break;
		}

		case 90: {
			string obchodnyNazov;
			int zemiaky, olej, ochucovadla;
			ifstream suborBiofarmarov("biofarmari.txt");
			string riadok;

			if (suborBiofarmarov.is_open()) {
				while (suborBiofarmarov >> obchodnyNazov >> zemiaky >> olej >> ochucovadla) {
					sklad->pridajBiofarmara(new Biofarmar(obchodnyNazov,(zemiaky), konverziaIntToBool(olej), konverziaIntToBool(ochucovadla)));
				}
			}
			suborBiofarmarov.close();
			cout << "Biofarmari boli uspesne nacitani. " << endl;
			break;
		}

		case 91: {
			string spz;
			int typ, nosnost, naklady, datum;
			ifstream suborVozidiel("vozidla.txt");
			string riadok;

			if (suborVozidiel.is_open()) {
				while (suborVozidiel >> spz >> typ >> nosnost >> naklady >> datum) {
					sklad->pridajVozidlo(new Vozidlo(spz,typ,nosnost,naklady, new Den(datum)));
				}
			}
			suborVozidiel.close();
			cout << "Vozidla boli uspesne nacitane. " << endl;
			break;

		}

		case 0: {
			delete sklad;
			sklad = nullptr;
			exit(0);

		}

	}


}
}

