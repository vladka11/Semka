#pragma once
#include <string>

using namespace std;

class Zakaznik
{
public:
	Zakaznik(string obchodnyNazov, int cisloRegionu);
	string getObchodnyNazov();
	int getCisloRegionu();
	~Zakaznik();

private:
	string obchodnyNazov_;
	int cisloRegionu_;
};
