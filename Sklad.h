#pragma once
#include "array_list.h"
#include "explicit_queue.h"
#include "heap.h"
#include "heap_monitor.h"
#include "linked_list.h"
#include <iostream>
#include "Biofarmar.h"

using namespace structures;
	class Sklad
	{
	public:
		Sklad();
		void pridajBiofarmara(Biofarmar * biofarmar);
		void vypisBiofarmarov();
		void bubbleSort(LinkedList<Biofarmar*>* linkedList, int size);
		~Sklad();


	private:
		LinkedList<Biofarmar*>* zoznamBiofarmarov_;

	};



