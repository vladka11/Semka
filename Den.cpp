#include "heap_monitor.h"
#include "Den.h"

Den::Den(int den) :
	den_(den)
{

}
Den::~Den()
{
}
void Den::zvysDen()
{
	den_++;
}

int Den::getDen()
{
	return den_;
}

void Den::setDen(int denn)
{
	den_ = denn;
}


