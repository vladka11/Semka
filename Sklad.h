#pragma once
#include "array_list.h"
#include "explicit_queue.h"
#include "heap.h"
#include "heap_monitor.h"
#include "linked_list.h"
#include <iostream>
#include "Biofarmar.h"
#include "Vozidlo.h"
#include "Zakaznik.h"
#include "Objednavka.h"
#include "priority_queue.h"
#include "DodavkaSurovin.h"

using namespace structures;
class Sklad
{
public:
	Sklad();
	void pridajBiofarmara(Biofarmar * biofarmar);
	bool skontrolujNazovBiofarmara(string nazovBiofarmara);

	void vypisBiofarmarov(LinkedList<Biofarmar *>* biofarmari);
	void vypisUrcitychBiofarmarov(int typTovaru);
	void bubbleSort(LinkedList<Biofarmar*>* linkedList, int size);
	void usporiadajBofarmarovPodlaCenyPolotovarov(int typPolotovaru);
	void bubbleSortPodlaCenyZemiakov(LinkedList<Biofarmar*>* linkedList, int size);
	void bubbleSortPodlaCenyOchucovadiel(LinkedList<Biofarmar*>* linkedList, int size);
	void bubbleSortPodlaCenyOleja(LinkedList<Biofarmar*>* linkedList, int size);


	//VOZIDLA
	void bubbleSortVozidiel(ArrayList<Vozidlo*>* linkedList, int size);
	bool skontrolujSPZ(string spz);
	void pridajVozidlo(Vozidlo * vozidlo);
	void vypisVozidla();

	//ZAKAZNICI
	void pridajZakaznika(Zakaznik * zakaznik);
	bool skontrolujNazovZakaznika(string nazovZakaznika);
	void vypisZakaznikov();
	Zakaznik* dajZakaznikaPodlaIndexu(int index);

	//OBJEDNAVKY
	void pridajSchvalenuObjednavku(Objednavka * objednavka);
	void vypisPoslednuObjednavku();
	bool skontrolujDatumDorucenia(int denDodania, int aktualnyDen);
	double dajVolnuKapacituAut(int typObjednavky);
	double dajHmotnostObjednavokNaDanyDen(int den);

	void pridajZamietnutuObjednavku(Objednavka * objednavka);
	void aktualizujPriemerneNakupneCena(int aktualnyDen);

	//POLOTOVARY
	void nakupPolotovar(DodavkaSurovin * objednavkaPolotovarov);
	//metody vratia poèet tovarov ktore nam chybaju
	int dajObjednanyPocetHranoliek(int den);
	int dajObjednanyPocetLupienkov(int den);
	void zabezpecOlej(double mnozstvoOleja, int den);
	void zabezpecZemiaky(double mnozstvoZemiakov, int den);
	void zabezpecOchucovadla(double mnozstvoOchucovadiel, int den);
		

	//Ostatne
	double dajRandomCislo(double min, double max);

	//8.uloha
	 void dajZajtrajsieObjednavky(int den);
	 void bubbleSortObjednavokPodlaTrzby(ArrayList<Objednavka*>* linkedList, int size);

	 //9.uloha
	 void naplnVozidla(int den);
	 void naplnVozidlaOstatnymiObjednavkami();
	 void zosortujObjednavkyPodlaRegionu(ArrayList<Objednavka*>* objednavky);
	 void zosortujObjednavkyPodlaDatumuDorucenia(ArrayList<Objednavka*>* objednavky);
	 void vypisSkladu();

	 //10.uloha
	 void vylozVozidla();

	//gettery
	double getMnozstvoOlejaNaSklade();
	double getMnozstvoOchucovadielNaSklade();
	double getMnozstvoZemiakovNaSklade();
	void setMnozstvoOlejaNaSklade(double mnozstvo);
	void setMnozstvoOchucovadielNaSklade(double mnozstvo);
	void setMnozstvoZemiakovNaSklade(double mnozstvo);


		~Sklad();


	private:
		double mnozstvoLupienkovNaSklade;
		double mnozstvoHranolcekovNaSklade;
		double mnozstvoOlejaNaSklade;
		double mnozstvoZemiakovNaSklade;
		double mnozstvoOchucovadlaNaSklade;

		LinkedList<Biofarmar*>* zoznamBiofarmarov_;
		ArrayList<Vozidlo*>* zoznamVozidiel_;
		ArrayList<Zakaznik*>* zoznamZakaznikov_;
		ArrayList<Objednavka*>* zoznamCakajucichObjednavok_;
		ArrayList<Objednavka*>* zoznamZamietnutychObjednavok_;
		ArrayList<Objednavka*>* zoznamZrusenychObjednavok_;
		LinkedList<DodavkaSurovin*>* zoznamObjednavokPolotovaru_;
		ArrayList<Objednavka*>* zoznamZrealizovanychObjednavok_;

	};



