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
	~Biofarmar();


private:
	string obchodnyNazov_;
	bool zemiaky_;
	bool olej_;
	bool ochucovadla_;

};

