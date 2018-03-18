#include "DodavkaSurovin.h"



DodavkaSurovin::DodavkaSurovin(Biofarmar * biofarmar, int typSuroviny, double mnozstvo, double jednotkovaCena, Den * datum):
	biofarmar_(biofarmar), typSuroviny_(typSuroviny), mnozstvo_(mnozstvo), jednotkovaCena_(jednotkovaCena), celkovaCena_(mnozstvo*jednotkovaCena), datum_(datum)
{
}

Biofarmar * DodavkaSurovin::getBiofarmar() 
{
	return biofarmar_;
}

int DodavkaSurovin::getTypSuroviny()
{
	return typSuroviny_;
}

double DodavkaSurovin::getMnozstvo()
{
	return mnozstvo_;
}

double DodavkaSurovin::getJednotkovaCena()
{
	return jednotkovaCena_;
}

double DodavkaSurovin::getCelkovaCena()
{
	return celkovaCena_;
}

Den * DodavkaSurovin::getDatum()
{
	return datum_;
}

DodavkaSurovin::~DodavkaSurovin()
{
}
