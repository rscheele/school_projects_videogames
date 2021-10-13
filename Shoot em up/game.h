// Template, major revision 3, beta
// IGAD/NHTV - Jacco Bikker - 2006-2009

#pragma once

#include <vector>
#include <ctime>
#include "Tiles.h"

#include "string.h"
#include "surface.h"
#include "stdlib.h"
#include "template.h"
#include "Enemyturret.h"
#include "Aliens.h"

namespace Tmpl8 {

class Surface;

class Game;
struct Explosion
{
	Surface* Graphic;
};

struct Playerbullet
{
	Surface* Graphic;
	float xmove;
	float ymove;
	float xdir;
	float ydir;
	float xscreenpos;
	float yscreenpos;
};

struct Enemybullet
{
public:
	Surface* Graphic;
	void Tick(float a_DT, Game* game);
	int xPos();
	int yPos();
	bool active;
	bool calculate;
private:
	float xpos;
	float ypos;
	float xvel;
	float yvel;
	float xscreenpos;
	float yscreenpos;
};

struct Towerbullet
{
public:
	Surface* Graphic;
	void Tick(float a_DT, Game* game);
	int xPos();
	int yPos();
	bool active;
	bool calculate;
private:
	float xpos;
	float ypos;
	float xvel;
	float yvel;
	float xscreenpos;
	float yscreenpos;
};

class Game
{ 
public:
	void SetTarget( Surface* a_Surface ) { m_Screen = a_Surface; }
	void Init();
	void Tick( float a_DT );
	void KeyDown( unsigned int code );
	void KeyUp( unsigned int code );
	void MouseMove( unsigned int x, unsigned int y ) {}
	void MouseUp( unsigned int button ) {}
	void MouseDown( unsigned int button ) {}
	void KeyPress(unsigned int code);
	void KeyRelease(unsigned int code);
public:
	Surface* m_Screen;
private:
	bool keyleft, keyright, keyup, keydown, keyspace;
	bool bulletactive;
	int score;
	double rotation;
	float respawntimer;
	int lives;
	bool alive;
	Surface* imagedata;
	Enemyturret* m_Turret;
	std::vector<Tiles*> tiles;		
};

}; // namespace Tmpl8