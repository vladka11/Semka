#pragma once
#include <string>
#include "array_list.h"
#include "heap_monitor.h"
#include "Objednavka.h"
#include "explicit_stack.h"

using namespace std;
using namespace structures;
class Vozidlo
{
private:
	string spz_;
	int typVozidla_; // 1 = Lupienky, 2 = Hranolceky
	int nosnost_;
	int naklady_;
	Den *datZaradeniaDoEvid_;
	ExplicitStack<Objednavka*>* tovarVoVozidle_;



public:
	Vozidlo(string spz, int typ, int nosnost, int naklady, Den * datumEvid);
	~Vozidlo();
	string getSpz();
	int getTypVozidla();
	int getNosnost();
	int getNaklady();
	void setNosnost(int novaNosnost);
	void setNaklady(int naklady);
	Den *getDatumZaciatkuEvidencie();
	ExplicitStack<Objednavka*>* getTovarVoVozidle();
	
};

