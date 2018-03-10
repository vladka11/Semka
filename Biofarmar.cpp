#include "Biofarmar.h"
#include <string>


Biofarmar::Biofarmar(string obchodnyNazov, bool zemiaky, bool olej, bool ochucovadla) :
	obchodnyNazov_(obchodnyNazov), zemiaky_(zemiaky), olej_(olej), ochucovadla_(ochucovadla)
{
}

string Biofarmar::getObchodnyNazov() {
	return obchodnyNazov_;
}

Biofarmar::~Biofarmar()
{
}
