#pragma once
#include "Biofarmar.h"
#include "Den.h"

class DodavkaSurovin
{
public:
	DodavkaSurovin(Biofarmar * biofarmar, int typSuroviny, double mnozstvo, double jednotkaCena, Den * datum);
	Biofarmar * getBiofarmar();
	int getTypSuroviny();  // 1 = zemiaky, 2= olej, 3= ochucovadla
	double getMnozstvo();
	double getJednotkovaCena();
	double getCelkovaCena();
	Den * getDatum();
	~DodavkaSurovin();

private:

	Biofarmar * biofarmar_;
	int typSuroviny_;
	double mnozstvo_;
	double jednotkovaCena_;
	double celkovaCena_;
	Den * datum_;

};
