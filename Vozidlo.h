#pragma once
#include <string>
//#include "Datum.h"
#include "Paleta.h"
#include "array_list.h"
#include "heap_monitor.h"
#include "explicit_stack.h"

using namespace std;
using namespace structures;
class Vozidlo
{
private:
	string spz_;
	int opotrebovanie_;
	int nosnost_;
	Den* datZaciokEvid_;											//datum zaèiatku evidencie vozidla	
	ExplicitStack<Paleta*>* paletyVoVozidle_;

public:
	Vozidlo(string spz, int opotrebovanost,int nosnost, Den* denZaciatkuEvid);
	ExplicitStack<Paleta*>* getPaletyVoVozidle();

	Paleta * vylozPaletu();

	bool nalozPaletu(Paleta * paleta);

	Paleta * ukazPaletu();
	
	void vratenieVozidla();
	void prevzatiePaliet();
	string getSpz();
	void setSpz(string spz);
	int getOpotrebovanost();
	void setOpotrebovanost(int opotrebovanost);
	int getNosnost();
	void setNosnost(int nosnost);
	Den* getDenZaciatkuEvid();
	void setDenZaciatkuEvid(Den* datum);
	~Vozidlo();



};

