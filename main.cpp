// SemPraca2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Sklad.h"
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

	while (true) {
		cout << "----------------------------------------\n \t\t MENU \n----------------------------------------\n";
		cout << "1. Pridaj noveho biofarmara \n";
		cout << "2. Vypis zoznam biofarmarov v abecednom poradi \n";
		cout << "3. Pridaj nove vozidlo  \n";
		cout << "4. Vypis zoznam vozidiel podla datumu zaradenia do evidencie \n";


		cout << "\n-----Nacitavenie z txt-------" << endl;
		cout << "|90. Nacitaj biofarmarov       |" << endl;
		cout << "|92. Nacitaj dodavatelov z txt |" << endl;
		cout << "|93. Nacitaj vozidla z txt     |" << endl;
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

			sklad->pridajBiofarmara(new Biofarmar(nazovSpolocnosti, konverziaIntToBool(zemiaky),konverziaIntToBool(olej), konverziaIntToBool(ochucovadla)));
			cout << "Biofarmar bol uspesne pridany" << endl;
			break;
		}
		case 2: {
			sklad->vypisBiofarmarov();
			break;
		}
		case 3: {
			cout << "vybral si si 3" << endl;
			break;
		}
		case 4: {
			cout << "vybral si si 4" << endl;
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

		case 0: {
			delete sklad;
			sklad = nullptr;
			exit(0);

		}

	}


}
}

