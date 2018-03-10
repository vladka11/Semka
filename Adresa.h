#pragma once
#include <string>
#include "heap_monitor.h"
using namespace std;
class Adresa
{
private:
	string mesto_;
	string ulica_;
	string psc_;
	string cisloDomu_;
public:
	Adresa(string mesto, string ulica, string psc, string cislDomu);
	~Adresa();
	string getMesto();
	string getUlica();
	string getPsc();
	string getCisloDomu();
	void setMesto(string mesto);
	void setUlica(string ulica);
	void setPsc(string psc);
	void setCisloDomu(string cisloDomu);
};