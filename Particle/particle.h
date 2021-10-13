#pragma once

#include "surface.h"

namespace Tmpl8 {

class Particle
{
public:
   Particle();
   ~Particle();
   virtual void MoveMe(Surface* Screen,float DT);
   void Draw(Surface* Screen);
   int m_Color;
   Surface* m_Screen;
   float m_X, m_Y;
};

};
