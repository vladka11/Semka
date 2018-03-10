#include "Biofarmar.h"
#include "heap_monitor.h"
#include <string>


Biofarmar::Biofarmar(string obchodnyNazov, bool zemiaky, bool olej, bool ochucovadla) :
	obchodnyNazov_(obchodnyNazov), zemiaky_(zemiaky), olej_(olej), ochucovadla_(ochucovadla)
{
}

string Biofarmar::getObchodnyNazov() {
	return obchodnyNazov_;
}

bool Biofarmar::getZemiaky()
{
	return zemiaky_;
}

bool Biofarmar::getOlej()
{
	return olej_;
}

bool Biofarmar::getOchucovadla()
{
	return ochucovadla_;
}

Biofarmar::~Biofarmar()
{
}
