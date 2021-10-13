#pragma once

#include "particle.h"

namespace Tmpl8 {

class Sand : public Particle
{
public:
	Sand(float a_X, float a_Y, int a_Color) ;
	~Sand() ;
   void MoveMe(Surface* Screen,float DT);
};

};