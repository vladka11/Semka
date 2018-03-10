#pragma once
#include <string>
#include "Den.h"
#include "heap_monitor.h"

using namespace std;

class Paleta

{
private:
	int region_;
	int hmotnost_;
	Den* datDorucenia_;
	bool prvaTrieda_;
	int stav_;
	string dodavatel_;
	Den* datPrichDoSkladu_;

public:
	Paleta(int region, int hmotnost, Den* datum, bool PrvaTrieda, string dodavatel);
	int getRegion();
	void setRegion(int region);
	int getHmotnost();
	void setHmotnost(int hmotnost);
	Den* getDenDorucenia();
	void setDenDorucenia(Den* datum);
	bool getPrvaTrieda();
	void setPrvaTrieda(bool prvaTrieda);
	int getStav();
	void setStav(int stav);
	string getDodavatal();
	void setDodavatel(string dodavatel);
	Den* getDatumPrichoduDoSkladu();
	void setDatumPrichoduDoSkladu(Den* denPrichodu);
	~Paleta();


};
