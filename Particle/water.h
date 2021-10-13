#pragma once

#include "particle.h"

namespace Tmpl8 {

enum {
	FALL,
	FLOW,
	STILL
};

class Water	: public Particle
{
public:
	Water(float a_X, float a_Y, int a_Color) ;
	~Water() ;
   void MoveMe(Surface* Screen,float DT);
};

};