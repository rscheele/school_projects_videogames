#include "particle.h"
#include "stdlib.h"
#include "template.h"
#include "string.h"

using namespace Tmpl8;

Particle::Particle(void)
{
}

void Particle::MoveMe(Surface* Screen,float DT)
{
	Draw(m_Screen);
}

void Particle::Draw(Surface* Screen)
{
	Screen->GetBuffer()[(int)(this->m_X +((int)this->m_Y * Screen->GetWidth()))] = m_Color;
}

Particle::~Particle(void)
{
}
