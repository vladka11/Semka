#include "heap_monitor.h"
#include "Den.h"

Den::Den(int den) :
	den(den)
{

}
Den::~Den()
{
}
void Den::zvysDen()
{
	den++;
}

int Den::getDen()
{
	return den;
}

void Den::setDen(int denn)
{
	den = denn;
}


