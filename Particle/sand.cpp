#include "sand.h"
#include "surface.h"
#include "stdlib.h"
#include "template.h"
#include "string.h"

using namespace Tmpl8;

Sand::Sand(float a_X, float a_Y, int a_Color)
{
	this->m_X=a_X;
	this->m_Y=a_Y;
	this->m_Color=a_Color;
}

void Sand::MoveMe(Surface* Screen,float DT)
{
	if (m_Y < 478 && m_X > 1 && m_X < 639)
	{
		if (Screen->GetBuffer()[(int)(this->m_X +((int)this->m_Y * Screen->GetWidth() + Screen->GetWidth()))] == 0x000000)
			m_Y = m_Y + 1;
		else if (Screen->GetBuffer()[(int)(this->m_X +((int)this->m_Y * Screen->GetWidth() + ( 2 * Screen->GetWidth() ) ))] == 0xE5C357 && Screen->GetBuffer()[(int)(this->m_X + 1 +((int)this->m_Y * Screen->GetWidth() + ( 2 * Screen->GetWidth() ) ))] == 0x000000)
			m_X = m_X + 1;
		else if (Screen->GetBuffer()[(int)(this->m_X +((int)this->m_Y * Screen->GetWidth() + ( 2 * Screen->GetWidth() ) ))] == 0xE5C357 && Screen->GetBuffer()[(int)(this->m_X - 1 +((int)this->m_Y * Screen->GetWidth() + ( 2 * Screen->GetWidth() ) ))] == 0x000000)
			m_X = m_X - 1;
	}
}

Sand::~Sand()
{
}