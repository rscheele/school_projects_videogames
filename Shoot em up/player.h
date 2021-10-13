#pragma once

#include "Tiles.h"
#include "string.h"
#include "surface.h"
#include "stdlib.h"
#include "template.h"

namespace Tmpl8 {

class Player
{
public:
	Player(void);
	~Player(void);
private:
	float a_X;
	float a_Y;
	float a_Z;
	Surface* Graphic;
};

}
