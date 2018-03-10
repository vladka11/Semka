#pragma once
#include "Den.h"
#include "array_list.h"
#include "Paleta.h"
#include "explicit_stack.h"
#include "heap_monitor.h"
#include <iostream>

using namespace structures;
using namespace std;

class Paleta;
class Kamion
{
private:
	Den* denPrichodu_;
	ExplicitStack<Paleta*> *paletyVkamione_;

public:
	Kamion(Den* denPrichodu);
	ExplicitStack<Paleta*>* getPaletyVkamione();

	~Kamion();
	
	Den* getDenPrichodu();
	void setDenPrichodu(Den* denPrichodu);

	bool nalozPaletu(Paleta * paleta);
	bool nalozNaklad(int pocetPaliet,string dodavatel, int denSkladu, Kamion *k);
	Paleta* vylozPaletu();
	Paleta* ukazPaletu();
};
