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

		void bubbleSortVozidiel(ArrayList<Vozidlo*>* linkedList, int size);

		bool skontrolujSPZ(string spz);
		void pridajVozidlo(Vozidlo * vozidlo);
		void vypisVozidla();


		void pridajZakaznika(Zakaznik * zakaznik);
		bool skontrolujNazovZakaznika(string nazovZakaznika);
		~Sklad();


	private:
		LinkedList<Biofarmar*>* zoznamBiofarmarov_;
		ArrayList<Vozidlo*>* zoznamVozidiel_;
		ArrayList<Zakaznik*>* zoznamZakaznikov_;

	};



