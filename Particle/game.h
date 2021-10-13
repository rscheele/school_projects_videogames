// Template, major revision 3, beta
// IGAD/NHTV - Jacco Bikker - 2006-2009

#pragma once

#include "surface.h"
#include "particle.h"
#include <vector>

namespace Tmpl8 {

class Game
{ 
public:
	void SetTarget( Surface* a_Surface ) { m_Screen = a_Surface; }
	void Init();
	void Tick( float a_DT );
	void KeyDown( unsigned int code ) {}
	void KeyUp( unsigned int code ) {}
	void MouseMove( unsigned int x, unsigned int y ) ;
	void MouseUp( unsigned int button ) ;
	void MouseDown( unsigned int button ) ;
	std::vector<Particle*> Particles;
private:
	bool SpawnSand;
	bool SpawnWater;
	bool lmbup, rmbup;
	Surface* m_Screen;
};

}; // namespace Tmpl8