#include "Aliens.h"

using namespace Tmpl8;

Aliens::Aliens(void)
{
	Surface* Aliensprite = new Surface("assets/UFO.png");
	Graphic = Aliensprite;
	state = CALCULATE;
	alive = true;
	xTick = 1000;
	yTick = 1000;
	changestate = true;
}



Aliens::~Aliens(void)
{
}
