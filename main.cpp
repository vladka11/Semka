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
		cout << "9. Napln vozidla tovarom \n";
		cout << "10. Odovzdaj tovar zakaznikom \n";
		cout << "11. Vypis zakaznikov z daneho regionu \n";
		cout << "12. Vypis vsetky objednavok za dany casovy interval  \n";
		cout << "13. Vypis vsetkych nezrealizovanych objednavok \n";
		cout << "14. Vyhladaj biofarmara od ktoreho sme najviac nakupili za 30dni \n";
		cout << "15. Vypisanie celkoveho zisku \n";



		cout << endl;


		cout <<"100. Vypis aktualny den: " << endl;
		cout << "101. Zvys den" << endl;
		cout << "102. Zvys na zadany den" << endl;

		cout << "\n-----Nacitavenie z txt-------" << endl;
		cout << "|90. Nacitaj biofarmarov       |" << endl;
		cout << "|91. Nacitaj vozidla           |" << endl;
		cout << "|92. Nacitaj zakaznikov        |" << endl;
		cout << "|93. Nacitaj objednavky        |" << endl;
		cout << "|94. Nacitaj den a sklad       |" << endl;
		cout << "|0. Uloz a Ukonci program      |" << endl;
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

			cout << "Je biofarmar dodavatelom ochucovadiel? (Vloz 1=ano/0=nie)" << endl;
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
			cout << "Volba 2: V˝pis biofarmarov \n----------------------------------------\n" << endl;
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
						cout << "Hmotnost objednavok: " << sklad->dajHmotnostObjednavokNaDanyDen(datumDorucenia) << " Kapacita aut: " << sklad->dajVolnuKapacituAut(typTovaru) <<endl;
						cout << "Objednavka bola pridana" << endl;
					}
					else {
						Zakaznik *pomZakaznik = sklad->dajZakaznikaPodlaIndexu(zakaznik - 1);
						cout << "Objednavku nie je mozne zrealizovat z dovodu maximalnej kapacity vozidla" << endl;
						sklad->pridajZamietnutuObjednavku(new Objednavka(new Den(den->getDen()), pomZakaznik, typTovaru, mnozstvo, jednotkovaCena, new Den(datumDorucenia), 0));
						
					}
				}
				else {
					Zakaznik *pomZakaznik = sklad->dajZakaznikaPodlaIndexu(zakaznik - 1);
					cout << "Objednavku nie je mozne zrealizovat kvoli kapacite vozidiel." << endl;
					sklad->pridajZamietnutuObjednavku(new Objednavka(new Den(den->getDen()), pomZakaznik, typTovaru, mnozstvo, jednotkovaCena, new Den(datumDorucenia), 0));
				
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
			double potrebneOchucovadla = lupienkyZobjednavok * 0.02;

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
				cout << " Potrebovali sme " << potrebneOchucovadla << "kg ochucovadiel." << endl;
			}
			else {
				cout << "0kg ochucovadiel." << endl;
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

		case 11: {
			int region;
			int denOd;
			int denDo;
			cout << "Vypisanie zoznamu zakaznikov" << endl;
			cout << "Z akeho regionu chcete vypisat zakaznikov ? 1-8" << endl;
			cin >> region;
			cout << "Zadaj pociatocny den pre vypis prijmu " << endl;
			cin >> denOd;
			cout << "Zadaj konecne den pre vypis prijmu" << endl;
			cin >> denDo;
			sklad->vypisZakaznikov(region, denOd, denDo);

			break;
		}
			
		case 12: {
			int denOd;
			int denDo;
			cout << "Vypis zrealizovanych objednavok" << endl;
			cout << "Zadaj pociatocny den pre vypis" << endl;
			cin >> denOd;
			cout << "Zadaj konecny den pre vypis" << endl;
			cin >> denDo;
			sklad->zoradPodlaDatumuZrealizovania();
			sklad->vypisZrealizovaneObjednavky(denOd, denDo);
			break;

		}

		case 13: {
			int denOd;
			int denDo;
			cout << "Vypis zrusenych a zamietnutych objednavok" << endl;
			cout << "Zadaj pociatocny den pre vypis" << endl;
			cin >> denOd;
			cout << "Zadaj konecny den pre vypis" << endl;
			cin >> denDo;

			sklad->vypisZamietnutychObjednavok(denOd, denDo);
			sklad->vypisZrusenychObjednavok(denOd, denDo);
			break;
	
		}

		case 14: {
			sklad->aktualizujPriemerneNakupneCena(den->getDen());

			int volba;
			cout << "Vyhladanie biofarmara od ktorÈho sme najviac nakupili" << endl;
			cout << "Aky typ produktu?? 1=zemiaky, 2=olej, 3=ochucovadla" << endl;
			cin >> volba;

			sklad->vyhladajBiofarmara(volba, den->getDen());
			break;
		}

		case 15: {

			int denOd;
			int denDo;
			cout << "Zadaj pociatocny den pre vypis" << endl;
			cin >> denOd;
			cout << "Zadaj konecny den pre vypis" << endl;
			cin >> denDo;


			int prijem = sklad->dajZiskSpolocnosti(denOd, denDo);
			int naklady = sklad->dajNakladySpolocnosti(denOd, denDo);
			cout << "CELKOVY PRIJEM: " << prijem << endl;;
			cout << "CELKOVE NAKLADY: " << naklady << endl;;
			cout << "CELKOVY ZISK: " << prijem - naklady << endl;
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

		case 93: {
		
			int datumZaevidovania;
			string zakaznik;
			int typTovaru; // 1 = Lupienky, 2 = Hranolceky
			int mnozstvo;
			double jednotkovaCena;
			int datumDorucenia;
			int stav;
			ifstream suborCakajucichObjednavok("objednavky_cakajuce.txt");
			if  (suborCakajucichObjednavok.is_open()) {
				
				while (suborCakajucichObjednavok >>datumZaevidovania>> zakaznik >>typTovaru>>mnozstvo>>jednotkovaCena>>datumDorucenia>>stav) {
					sklad->pridajSchvalenuObjednavku(new Objednavka(new Den(datumZaevidovania),sklad->vratZakaznika(zakaznik), typTovaru, mnozstvo, jednotkovaCena, new Den(datumDorucenia), stav));
				}
			}
			suborCakajucichObjednavok.close();


			ifstream suborZrealizovanychObjednavok("objednavky_zrealizovane.txt");
			if (suborZrealizovanychObjednavok.is_open()) {
				while (suborZrealizovanychObjednavok >> datumZaevidovania >> zakaznik >> typTovaru >> mnozstvo >> jednotkovaCena >> datumDorucenia >> stav) {
					sklad->pridajZrealizovanuObjednavku(new Objednavka(new Den(datumZaevidovania), sklad->vratZakaznika(zakaznik), typTovaru, mnozstvo, jednotkovaCena, new Den(datumDorucenia), stav));
				}
			}
			suborZrealizovanychObjednavok.close();


			ifstream suborZamietnutychObjednavok("objednavky_zamietnute.txt");
			if (suborZamietnutychObjednavok.is_open()) {
				while (suborZamietnutychObjednavok >> datumZaevidovania >> zakaznik >> typTovaru >> mnozstvo >> jednotkovaCena >> datumDorucenia >> stav) {
					sklad->pridajZamietnutuObjednavku(new Objednavka(new Den(datumZaevidovania), sklad->vratZakaznika(zakaznik), typTovaru, mnozstvo, jednotkovaCena, new Den(datumDorucenia), stav));
				}
			}
			suborZamietnutychObjednavok.close();


			ifstream suborZrusenychObjednavok("objednavky_zrusene.txt");
			if (suborZrusenychObjednavok.is_open()) {
				while (suborZrusenychObjednavok >> datumZaevidovania >> zakaznik >> typTovaru >> mnozstvo >> jednotkovaCena >> datumDorucenia >> stav) {
					sklad->pridajZrusenuObjednavku(new Objednavka(new Den(datumZaevidovania), sklad->vratZakaznika(zakaznik), typTovaru, mnozstvo, jednotkovaCena, new Den(datumDorucenia), stav));
				}
			}
			suborZrusenychObjednavok.close();
			cout << "Objednavky boli uspesne nacitane. " << endl;
			break;

		}

		case 94: {
			int dnik;
			ifstream subor("aktualnyDen.txt");
			double zemiaky, olej, ochucovadla;
			ifstream suborr("polotovary.txt");
		

			if (subor.is_open()) {
				while (subor >> dnik) {
					den->setDen(dnik);
				}  
			}
			cout << "Aktualny den: " << dnik << endl;
	
			if (suborr.is_open()) {
			while (suborr >>zemiaky>>olej>>ochucovadla) {
				sklad->setMnozstvoOchucovadielNaSklade(ochucovadla);
				sklad->setMnozstvoOlejaNaSklade(olej);
					sklad->setMnozstvoZemiakovNaSklade(zemiaky);
			}
			}
		suborr.close();
		subor.close();
	
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

		case 102: {
			int denn = 0;
			cout << "Zadaj den na ktory sa chces presunut" << endl;
			cin >> denn;
			den->setDen(denn);
			cout << "Si na dni " << denn << endl;
			break;

		}

		case 500: {
			sklad->vypisSkladu();
			break;
		}

		case 0: {

			//ulozenie do suborov

			//ZAKAZNICI
			if (sklad->getZoznamZakaznikov()->size() > 0) {
				ofstream subor;
				subor.open("zakaznici.txt");
				for (Zakaznik * zak : *sklad->getZoznamZakaznikov()) {
					subor << zak->getObchodnyNazov() << " " << zak->getCisloRegionu() << "\n";
				}
				subor.close();
			}

			//VOZIDLA
			if (sklad->getZoznamVozidiel()->size() > 0) {
				ofstream subor;
				subor.open("vozidla.txt");
				for (Vozidlo * voz : *sklad->getZoznamVozidiel()) {
					subor << voz->getSpz() << " " << voz->getTypVozidla() << " " << voz->getNosnost() << " " << voz->getNaklady() << " " << voz->getDatumZaciatkuEvidencie() << "\n";
				}
				subor.close();
			}

			//BIOFARMARI
			if (sklad->getZoznamBiofarmarov()->size() > 0) {
				ofstream subor;
				subor.open("biofarmari.txt");
				for (Biofarmar * bio : *sklad->getZoznamBiofarmarov()) {
					subor <<  bio->getObchodnyNazov() << " " << bio->getZemiaky() << " " << bio->getOlej() << " " << bio->getOchucovadla() << "\n";
				}
				subor.close();
			}
			
			////ZREALIZOVANE OBJEDNAVKY
			if (sklad->getZoznamZrealizovanychObjednavok()->size() > 0) {
				ofstream subor;
				subor.open("objednavky_zrealizovane.txt");
				for  (Objednavka * obj : *sklad->getZoznamZrealizovanychObjednavok()) {
					subor << obj->getDatumZaevidovania()->getDen() << " " << obj->getZakaznik().getObchodnyNazov() << " " << obj->getTypTovaru() << " " << obj->getMnozstvoTovaru() << " " << obj->getJednotkovaCena() << " " << obj->getDatumDorucenia()->getDen() << " " << obj->getStav() <<  "\n";
				}
				subor.close();
			}

			////ZRUSENE OBJEDNAVKY
			if (sklad->getZoznamZrusenychObjednavok()->size() > 0) {
				ofstream subor;
				subor.open("objednavky_zrusene.txt");
				for (Objednavka * obj : *sklad->getZoznamZrusenychObjednavok()) {
					subor << obj->getDatumZaevidovania()->getDen() << " " << obj->getZakaznik().getObchodnyNazov() << " " << obj->getTypTovaru() << " " << obj->getMnozstvoTovaru() << " " << obj->getJednotkovaCena() << " " << obj->getDatumDorucenia()->getDen() << " " << obj->getStav() << "\n";
				}
				subor.close();
			}

			////CAKAJUCE
			if (sklad->zoznamCakajucichObjednavok()->size() > 0) {
				ofstream subor;
				subor.open("objednavky_cakajuce.txt");
				for (Objednavka * obj : *sklad->zoznamCakajucichObjednavok()) {
					subor << obj->getDatumZaevidovania()->getDen() << " " << obj->getZakaznik().getObchodnyNazov() << " " << obj->getTypTovaru() << " " << obj->getMnozstvoTovaru() << " " << obj->getJednotkovaCena() << " " << obj->getDatumDorucenia()->getDen() << " " << obj->getStav() << "\n";
				}
				subor.close();
			}

				 ofstream subor;
				 subor.open("aktualnyDen.txt");
				 subor << den->getDen();
				 subor.close();

		 ////POLOTOVARY

				 ofstream polotovarySubor;
				 polotovarySubor.open("polotovary.txt");
				 polotovarySubor << sklad->getMnozstvoZemiakovNaSklade() << " " << sklad->getMnozstvoOlejaNaSklade() << " " << sklad->getMnozstvoOchucovadielNaSklade();
		
			delete sklad;
			sklad = nullptr;

			delete den;
			den = nullptr;
			exit(0);

		}

	}


}
}}

