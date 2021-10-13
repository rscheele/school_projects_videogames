#pragma once

#include <ctime>

#include "Tiles.h"
#include "string.h"
#include "surface.h"
#include "stdlib.h"
#include "template.h"

namespace Tmpl8 {

enum {
	CALCULATE,
	MOVETOPLAYER,
	SHOOT,
	MOVERIGHT,
	MOVEUP,
	MOVELEFT,
	MOVEDOWN,
	MOVEFREE,
	DEAD
};

class Aliens
{
public:
	Aliens(void);
	~Aliens(void);
	void Tick(float a_DT);
	//float Timer(a_DT);
	void Draw(Surface* surface);
	Surface* Graphic;
	int Xpos();
	int Ypos();
	bool alive;
	bool shoot;
private:
	float xPos;
	float yPos;
	float xTick;
	float yTick;
	float Xvel;
	float Yvel;
	int state;
	int deadtimer;
	bool changestate;
};

}