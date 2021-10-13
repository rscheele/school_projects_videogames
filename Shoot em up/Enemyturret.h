#pragma once

#include "Tiles.h"
#include "string.h"
#include "surface.h"
#include "stdlib.h"
#include "template.h"

namespace Tmpl8 {

class Enemyturret
{
public:
	Enemyturret(void);
	void Draw(Surface* surface);
	~Enemyturret(void);
private:
	float a_X;
	float a_Y;
	float a_Z;
	Surface* turretImage;
	Surface* Graphic;
};

}
