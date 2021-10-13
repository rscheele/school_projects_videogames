// Template, major revision 3, beta
// IGAD/NHTV - Jacco Bikker - 2006-2009

#pragma once

namespace Tmpl8 {
enum {
	LEFT = 0,
	RIGHT
};

class Surface;

class Game;
	struct Invader
	{
		double Xpos;
		double Ypos;
		int State;
		bool CanIShoot;
		int Type;
		Surface* Graphic;
		int Dir ;
		bool Visible;
		void Tick(float a_DT);
		bool colision;
	};

	struct Ball
	{
		int Ymove;
		int Xmove;
		Surface* Graphic;
		bool flying;
	};

	struct Spaceship
	{
		float Ydir;
		float Xdir;
		int Shoot;
		int leftarrow;
		int CanIShoot;
		int rightarrow;
		int lives;
		bool alive;
		Surface* Graphic;
		int invadersalive;
		float arcchoose;
	};

	struct EnemyBullet
	{
		int XAttack;
		int YAttack;
		bool active;
		bool Attacked;
		Surface* Graphic;
		void Tick(float DT,Game* game);
	};

	enum {
	MOVELEFTRIGHT,
	ARC,
	FLY,
	SHOOT,
	GOBACK
	};

	class Commander
	{
	public:
		float Xvel;
		float Yvel;
		int State;
		int xdirection;
		bool shootarc;
		float Xdirc;
		float Ydirc;
		int bulletx;
		int bullety;
		bool bulletactive;
		int arcPosX;
		int arcPosY;
		int counter;
		int number;
		float Walkx;
		float Walky;
		bool visible2;
		float step ;
		float stepCounter;
		float maxStep;
		Surface* Graphic;
		void Tick(float DT,Game* game);
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

	int  Update(Invader*,int);
	int Update(Commander*,int);
public:
	Surface* m_Screen;
};

}; // namespace Tmpl8