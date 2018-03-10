#pragma once
#include "array_list.h"
#include "explicit_queue.h"
#include "heap.h"
#include "heap_monitor.h"
#include "linked_list.h"
#include <iostream>
#include "Biofarmar.h"
#include "Vozidlo.h"

using namespace structures;
	class Sklad
	{
	public:
		Sklad();
		void pridajBiofarmara(Biofarmar * biofarmar);
		void vypisBiofarmarov(LinkedList<Biofarmar *>* biofarmari);
		void vypisUrcitychBiofarmarov(int typTovaru);
		void bubbleSort(LinkedList<Biofarmar*>* linkedList, int size);

		void bubbleSortVozidiel(LinkedList<Vozidlo*>* linkedList, int size);

		void pridajVozidlo(Vozidlo * vozidlo);
		void vypisVozidla();
		~Sklad();


	private:
		LinkedList<Biofarmar*>* zoznamBiofarmarov_;
		LinkedList<Vozidlo*>* zoznamVozidiel_;

	};



