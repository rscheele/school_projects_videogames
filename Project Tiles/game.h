// Template, major revision 3, beta
// IGAD/NHTV - Jacco Bikker - 2006-2009

#pragma once

#include <vector>
#include "Tiles.h"

#include "string.h"
#include "surface.h"
#include "stdlib.h"
#include "template.h"

namespace Tmpl8 {

class Surface;

class Game
{ 
public:
	void SetTarget( Surface* a_Surface ) { m_Screen = a_Surface; }
	void Init();
	void Tick( float a_DT );
	void KeyDown( unsigned int code ) {}
	void KeyUp( unsigned int code ) {}
	void MouseMove( unsigned int x, unsigned int y ) {}
	void MouseUp( unsigned int button ) {}
	void MouseDown( unsigned int button ) {}
	void CopyTo(Surface* a_Dst, Surface* a_Src, int a_X, int a_Y );

private:
	Surface* m_Screen;
	Surface* imagedata;
	std::vector<Tiles*> tiles;
};

}; // namespace Tmpl8