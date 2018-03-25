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
	initHeapMonitor(); 
	Sklad * sklad = new Sklad();
	Den * den = new Den(1);

	while (1) {
		cout << "----------------------------------------\n \t\t MENU \n----------------------------------------\n";
		cout << "1. Pridaj noveho biofarmara \n";
		cout << "2. Vypis zoznam biofarmarov v abecednom poradi \n";
		cout << "3. Pridaj nove vozidlo  \n";
		cout << "4. Vypis zoznam vozidiel podla datumu zaradenia do evidencie \n";
		cout << "5. Pridaj noveho zakaznika \n";
		cout << "6. Zaevidovanie novej objednavky \n" ; 
		cout << "7. Skontroluj zasoby polotovarov \n";
		cout << "8. Vypis zajtrajsie objednavky \n" ;
		cout << "9. Napln vozidla \n";


		cout << endl;






		cout <<"100. Vypis aktualny den: " << endl;
		cout << "101. Zvys den" << endl;

		cout << "\n-----Nacitavenie z txt-------" << endl;
		cout << "|90. Nacitaj biofarmarov       |" << endl;
		cout << "|91. Nacitaj vozidla           |" << endl;
		cout << "|92. Nacitaj zakaznikov        |" << endl;
		cout << "|0. Ukonci program             |" << endl;
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

			cout << "Je biofarmar dodavatelom ochucovadiel? (Vloû 1=ano/0=nie)" << endl;
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
			cout << "Volba 2: V˝pis biofarm·rov \n----------------------------------------\n" << endl;
			cout << "Vyber moznost pre vypisanie:" << endl;
			cout << "1: vypis vsetkych biofarmarov" << endl;
			cout << "2. vypis dodavatelov oleja" << endl;
			cout << "3. vypis dodavatelov zemiakov" << endl;
			cout << "4. vypis dodavatelov ochucovadiel" << endl;

			cin >> volba;

			sklad->aktualizujPriemerneNakupneCena(den->getDen());
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
				nosnost = 2000;
			}else {
				nosnost = 5000;
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

		case 6: {
			int typTovaru, zakaznik;
			double jednotkovaCena,mnozstvo;
			//Zakaznik * pomZakaznik;

			int datumDorucenia;
			cout << "Volba 5: Registracia noveho zakaznika \n----------------------------------------\n" << endl;
			cout << "Vyber zakaznika zo zoznamu: " << endl;
			sklad->vypisZakaznikov();
			cin >> zakaznik;

			cout << "O aky typ tovaru mate zaujem?  ( 1 = Lupienky, 2 = Hranolky)" << endl;
			cin >> typTovaru;
			cout << "Zadajte mnozstvo " << endl;
			cin >> mnozstvo;
			cout << "Zadajte jednotkovu cenu " << endl;
			cin >> jednotkovaCena;
			cout << "Zadajte datum dorucenia  " << endl;
			cout << "Help (dnesny den): " << den->getDen() << endl;
			cin >> datumDorucenia;
			
			if (sklad->skontrolujDatumDorucenia(datumDorucenia, den->getDen())) {
				if (sklad->dajHmotnostObjednavokNaDanyDen(datumDorucenia) + mnozstvo <= sklad->dajVolnuKapacituAut(typTovaru)){
					if (mnozstvo < 5000 && typTovaru == 2 || mnozstvo < 2000 && typTovaru == 1) {
						Zakaznik *pomZakaznik = sklad->dajZakaznikaPodlaIndexu(zakaznik - 1);
						sklad->pridajSchvalenuObjednavku(new Objednavka(new Den(den->getDen()), pomZakaznik, typTovaru, mnozstvo, jednotkovaCena, new Den(datumDorucenia), 0));
						cout << "Hmotnost objednavok: " << sklad->dajHmotnostObjednavokNaDanyDen(datumDorucenia) << "Kapacita aut: " << sklad->dajVolnuKapacituAut(typTovaru);
						cout << "Objednavka bola pridana" << endl;
					}
					else {
						cout << "Objednavku nie je mozne zrealizovat z dovodu maximalnej kapacity vozidla" << endl;
					}
				}
				else {
					cout << "Objednavku nie je mozne zrealizovat kvoli kapacite vozidiel." << endl;
				}
			}
			else {
				cout << "Datum dorucenia objednavky musi byt vacsi ako o tyzden" << endl;
			}
			
			sklad->vypisPoslednuObjednavku();
			break;
		
		}

		case 7: {

			// Otestovanie koæko hranoliek
			double hranolkyZobjednavok = sklad->dajObjednanyPocetHranoliek(den->getDen());
			double lupienkyZobjednavok = sklad->dajObjednanyPocetLupienkov(den->getDen());


			double potrebneZemiaky = hranolkyZobjednavok * 1.5 + lupienkyZobjednavok * 2;
			double potrebnyOlej = hranolkyZobjednavok * 0.2 + lupienkyZobjednavok * 0.4;
			double potrebneOchucovadla = lupienkyZobjednavok * 20;

			//Len pre vypis, inak moûeö zmazaù ... 
			hranolkyZobjednavok < 0 ? hranolkyZobjednavok = 0 : hranolkyZobjednavok = hranolkyZobjednavok;
			lupienkyZobjednavok < 0 ? lupienkyZobjednavok = 0 : lupienkyZobjednavok = lupienkyZobjednavok;

			cout << "\n \n Zhrnutie:  " << endl;
			

			sklad->aktualizujPriemerneNakupneCena(den->getDen());

			if (sklad->getMnozstvoZemiakovNaSklade() < potrebneZemiaky) {
				sklad->zabezpecZemiaky(potrebneZemiaky, den->getDen());
				cout <<" Potrebovali sme "<< potrebneZemiaky << "kg zemiakov." << endl;
			}
			else {
				cout << "0kg zemiakov." << endl;

			}

			if (sklad->getMnozstvoOlejaNaSklade() < potrebnyOlej) {
				sklad->zabezpecOlej(potrebnyOlej, den->getDen());
				cout << " Potrebovali sme " << potrebnyOlej << "l oleja." << endl;
			}
			else {
				cout << "0l oleja." << endl;
			}

			if (sklad->getMnozstvoOchucovadielNaSklade() < potrebneOchucovadla) {
				sklad->zabezpecOchucovadla(potrebneOchucovadla, den->getDen());
				cout << " Potrebovali sme " << potrebneOchucovadla << "g ochucovadiel." << endl;
			}
			else {
				cout << "0g ochucovadiel." << endl;
			}
			break;
		}

		case 8: {
			sklad->dajZajtrajsieObjednavky(den->getDen() + 1);
			sklad->vypisSkladu();
			break;
		}

		case 9: {
			sklad->naplnVozidla(den->getDen());
			sklad->naplnVozidlaOstatnymiObjednavkami();
			sklad->vypisSkladu();
			break;
		}

		case 10: {
			sklad->vylozVozidla();
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

		case 92: {
			int region;
			string obchodnyNazov;
			ifstream suborZakaznikov("zakaznici.txt");
			string riadok;

			if (suborZakaznikov.is_open()) {
				while (suborZakaznikov >> obchodnyNazov >> region) {
					sklad->pridajZakaznika(new Zakaznik(obchodnyNazov, region));
				}
			}
			suborZakaznikov.close();
			cout << "Zakaznici boli uspesne nacitani. " << endl;
			break;

		}

		case 100: {
			cout << "Dnes je den c."<< den->getDen() << " \n \n";
			break;
		}
		case 101: {
			den->zvysDen();
			cout << "Den bol zvyseny" << endl;
			cout << "Dnes je den c." << den->getDen() << endl;
			break;

		}

		case 0: {
			delete sklad;
			sklad = nullptr;

			delete den;
			den = nullptr;
			exit(0);

		}

	}


}
}

