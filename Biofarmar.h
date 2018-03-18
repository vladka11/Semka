#pragma once
#include <string>

using namespace std;

class Biofarmar
{
public:
	Biofarmar(string obchodnyNazov, bool zemiaky, bool olej, bool ochucovadla);
	string getObchodnyNazov();
	bool getZemiaky();
	bool getOlej();
	bool getOchucovadla();

	double getPriemCenaZemiakov();
	double getPriemCenaOleja();
	double getPriemCenaOchucovadiel();
	void setPriemCenaZemiakov(double cena);
	void setPriemCenaOleja(double cena);
	void setPriemCenaOchucovadiel(double cena);
	~Biofarmar();


private:
	string obchodnyNazov_;
	bool zemiaky_;
	bool olej_;
	bool ochucovadla_;
	double priemCenaZemiaky_;
	double priemCenaOlej_;
	double priemCenaOchucovadla_;

};

