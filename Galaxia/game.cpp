#include "string.h"
#include "surface.h"
#include "stdlib.h"
#include "template.h"
#include "game.h"
#include <ctime>

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACE 57

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

int TargetX = 0;
int TargetY = 200;
int TargetHDir = RIGHT;
int TargetVDir = DOWN;
int	Down = 0;
int a = 0;
float arcchoose = 2585.145;

using namespace Tmpl8;

Surface* Target = new Surface("assets/invader.tga");
Surface* Ship = new Surface("assets/turret.tga");
Surface* Pew = new Surface("assets/bullet.tga");
Surface* Enemybullet = new Surface("assets/bulletenemy.tga");
Surface* arcenemy = new Surface("assets/commander.tga");

Invader Invaders[55];
Spaceship Player;
Ball Bullet;
EnemyBullet Laser[20];
Commander Enemy[5];

bool keyleft = false;
bool keyright = false;
bool shoot = false;
int attack;
float delay = 578.154;
float deathdelay = 1478.21;
int Arcradius = 50; 

void Game::Init()
{
srand(time(0));

float maxStep = PI;
float step = 180.0/maxStep;
float stepCounter = 1.0;

int counter = 0;
int number = 0;
bool Visible = true;
int xdirection = RIGHT;
Player.alive = true;
Player.lives = 2;
Player.invadersalive = 60;
bool colision = false;
bool shootarc = false;
float arcchoose = 2873.36;

// drawing the player
Player.Graphic = Ship;
Bullet.Graphic = Pew;
Player.Xdir = 300;
Player.Ydir = 425;

for (int i = 0; i < 5; i++)
{
	Enemy[number].State = MOVELEFTRIGHT;
	Enemy[4].State = ARC;
	Enemy[number].Graphic = arcenemy;
	Enemy[number].Ydirc = 65;
	Enemy[number].Xdirc = 64*i+96;
	Enemy[number].visible2 = true;
	Enemy[number].Walkx = 64*i+96;
	Enemy[number].Walky = 65;
	number++;
}

// drawing bullet
for (int i = 0; i < 20; i++)
{
	Laser[i].Graphic = Enemybullet;
	Laser[i].active = false;
}

for (int k = 0; k <5 ; k++)
{
	for (int i = 0; i <11 ; i++)
	{
		//drawing the invaders
		Invaders[counter].Graphic = Target;
		Invaders[counter].Ypos = 100+(k*32);
		Invaders[counter].Xpos = 32*i+64;
		Invaders[counter].Dir = RIGHT;
		Invaders[counter].Visible = true;
		Invaders[counter].CanIShoot = false;
		counter++;
	}
}	
}


void Game::Tick( float a_DT )
{
	for (int i = 0; i <10 ; i++) // force a repeat of the clear screen to slow things down
		m_Screen->Clear( 0 );  

	if (delay >= 2.0)
	{
		delay = delay - a_DT;
	}

	if (Player.arcchoose >= 2.0)
	{
		Player.arcchoose = Player.arcchoose - a_DT;
	}

	if (Player.arcchoose <= 5.0)
	{
		a = a + 1;
		Player.arcchoose = 5631.14;
		if (a == 2)
		{
			Enemy[0].State = ARC;
		}
		if (a == 3)
		{
			Enemy[1].State = ARC;
		}
		if (a == 4)
		{
			Enemy[2].State = ARC;
		}
		if (a == 5)
		{
			Enemy[3].State = ARC;
		}
		if (a == 6)
		{
			Enemy[4].State = ARC;
		}
		if (a >= 7)
		{
			a = 1;
		}
	}

	if (deathdelay >= 2.0 && Player.alive == false)
	{
		deathdelay = deathdelay - a_DT;
	}
	if (deathdelay <= 5.0 && Player.alive == false && Player.lives >= 1)
	{
		Player.alive = true;
	}

	// making the player bullet colide with the enemy spaceships
	for (int i = 0; i < 55; ++i)
	{
		if (Bullet.Ymove - 16 <= Invaders[i].Ypos && Bullet.Ymove + 16 >= Invaders[i].Ypos && Bullet.Xmove + 16 >= Invaders[i].Xpos && Bullet.Xmove - 16 <= Invaders[i].Xpos && Bullet.flying == true)
		{
			if (Invaders[i].Visible == false)
			{
			Bullet.flying = true;
			}
			else
			{
			Player.invadersalive = Player.invadersalive - 1;
			printf("attacked \n");
			Invaders[i].Visible = false;
			Bullet.flying = false;
			}
		}
	}

	// printing player bullets
	if (Bullet.flying == true)
	{
		Bullet.Ymove=Bullet.Ymove-10;
		Bullet.Graphic->CopyTo(m_Screen,Bullet.Xmove+10,Bullet.Ymove);
	}

	if (Bullet.Ymove < 0 )
	{
	Bullet.flying = false;
	}

	//Updating the invader
for (int i = 0; i < 55; i++)
{
	if (Invaders[i].Visible == true)
	{
	Invaders[i].Tick(a_DT);
	}
}

if (Player.invadersalive <= 0)
{
	m_Screen->Print("You won!!!", 250, 250, 0xffffff);
}

for (int i = 0; i < 5; i++)
{
	Enemy[i].Tick(a_DT,this);
}

//Updating bullets
for(int i = 0; i<20; i++)
{
	Laser[i].Tick(a_DT,this);
}
	// drawing commanders
	for (int i = 0; i < 5; i++)
	{
		if (Enemy[i].visible2 == true)
		{
			Enemy[i].Graphic->CopyTo(m_Screen,Enemy[i].Xdirc,Enemy[i].Ydirc);
		}
	}

// drawing invaders
	for (int i = 0; i <55; i++)
	{
		if (Invaders[i].Visible == true)
		{
		Invaders[i].Graphic->CopyTo(m_Screen,Invaders[i].Xpos,Invaders[i].Ypos);
		}
	}

	// lives
	if (Player.alive == false && Player.lives <= 0)
	{
		m_Screen->Print("You have lost all of your lives and are dead, press escape to exit!", 10, 10, 0xffffff);
	}

	if (Player.lives == 1)
	{
		Player.Graphic->CopyTo(m_Screen,5,5);
	}

	if (Player.lives == 2)
	{
		Player.Graphic->CopyTo(m_Screen,5,5);
		Player.Graphic->CopyTo(m_Screen,40,5);
	}


	// drawning player
	if (Player.alive == true)
	{
		Player.Graphic->CopyTo(m_Screen,Player.Xdir,Player.Ydir);
	}

// player movement
		if (keyleft == true)
	{
		Player.Xdir=Player.Xdir-2;
	}

		if (keyright == true)
	{
		Player.Xdir=Player.Xdir+2;
	}
	
int retval = 0;
int change = 0;

	// movement invaders
	for (int i = 0; i <55; i++)
	{
	 if (retval = Update(&Invaders[i],Down))
	 {
		 change = 1;
	 }
	}

	if	(change == 1)
	{
		for		(int i  = 0; i <55; i++)
		{
			if (Invaders[i].Visible == true)
			{
			if (Invaders[i].Dir == LEFT) 
				Invaders[i].Dir = RIGHT;
			else
				Invaders[i].Dir = LEFT;
			}
		}
		change = 0;
	}
	// movement commanders
int retval2 = 0;
int change2 = 0;

	for (int i = 0; i < 5; i++)
	{
		if (retval2 = Update(&Enemy[i],Down))
		{
			change2 =  1;
		}
	}

	if (change2 == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			if (Enemy[i].xdirection == LEFT)
				Enemy[i].xdirection = RIGHT;
			else
				Enemy[i].xdirection = LEFT;
		}
		change2 = 0;
	}



}

// key movement
	void Game::KeyUp( unsigned int code )
	{
			keyleft = false;
			keyright = false;
			shoot = false;
	}

	void Game::KeyDown( unsigned int code )
	{
		switch(code)
		{
		case KEY_LEFT:
			keyleft = true;
			break;
		case KEY_RIGHT:
			keyright = true;
			break;
		case SPACE:
			if (Bullet.flying == false && Player.alive == true) 
			{
				Bullet.flying = true;
				Bullet.Xmove = Player.Xdir + 1;
				Bullet.Ymove = Player.Ydir;
			}

		}
	}

int Game::Update(Commander* Ene, int GoDown)
{
	int retval2 = 0;
	//if (Ene->State==MOVELEFTRIGHT)
	//{
	//if (Ene->xdirection == LEFT)
	//{
	//	Ene->Xdirc ++;
	//	if (Ene->Xdirc > 640-64)
	//	{
	//		retval2 = 1;
	//	}
	//}

	//if (Ene->xdirection == RIGHT)
	//{
	//	Ene->Xdirc --;
	//	if (Ene->Xdirc < 34)
	//	{
	//		retval2 = 1;
	//	}
	//}
	//}
	if (Ene->xdirection == LEFT)
	{
		Ene->Walkx ++;
		if (Ene->Walkx > 640-64)
		{
			retval2 = 1;
		}
	}

	if (Ene->xdirection == RIGHT)
	{
		Ene->Walkx --;
		if (Ene->Walkx < 34)
		{
			retval2 = 1;
		}
	}
	return retval2;
}

	// invadwers going left right
int Game::Update(Invader* Inv, int GoDown)
{
	int retval = 0;

	if	(Inv->Dir == LEFT && Inv->Visible == true)
	{
		Inv->Xpos --;
		if	(Inv->Xpos < 2) 
		{
			retval = 1;
		}
	}

	if	(Inv->Dir == RIGHT && Inv->Visible == true)
	{
		Inv->Xpos ++;
		if	(Inv->Xpos > 640-32) 
		{
			retval = 1;
		}
	}
	return retval;
};



///Invader Functions

void Invader::Tick(float a_DT)
{

}

// enemy shooting execute
void EnemyBullet::Tick(float DT,Game* game)
{
	if(active == true)
	{
		Graphic->CopyTo(game->m_Screen,XAttack,YAttack);
		YAttack=YAttack+3;

		if(YAttack >=SCRHEIGHT)
		{
			active = false;
		}
	}
}

	// commander (arcing invaders)
void Commander::Tick(float DT,Game* game)
{ 
	for (int i = 0; i < 5; i++)
	{
		if (Bullet.Ymove - 16 <= Enemy[i].Ydirc && Bullet.Ymove + 16 >= Enemy[i].Ydirc && Bullet.Xmove + 16 >= Enemy[i].Xdirc && Bullet.Xmove - 16 <= Enemy[i].Xdirc && Bullet.flying == true && Enemy[i].visible2 == true)
		{
			Enemy[i].visible2 = false;
			Bullet.flying = false;
			Player.invadersalive = Player.invadersalive - 1;
		}
	}

if (State == MOVELEFTRIGHT)
{
	Xdirc = Walkx;
	Ydirc = Walky;
}

if (State == ARC)
{
	if(stepCounter < 180.0)
	{
		if(stepCounter <=1.0)
		{
			arcPosX = Xdirc-Arcradius;
			arcPosY = Ydirc;
		}
		stepCounter++;
		float costemp = cos(stepCounter/180.0f*PI);
		float sintemp = sin(-stepCounter/180.0f*PI);
		Xdirc = costemp*Arcradius + arcPosX;
		Ydirc = sintemp*Arcradius + arcPosY;
	}
	else
	{
		State = FLY;
		Xvel = (Player.Xdir - Xdirc)/300;
		Yvel = (Player.Ydir - Ydirc)/300;

		//Normalized speed
		/*
		vector3 vec(Xvel,Yvel,0);
		float length = vec.Length();
		Xvel /= length;
		Yvel /= length;
		*/
	}
}else if (State == FLY)
{
	Xdirc += Xvel;
	Ydirc += Yvel;
	if (Ydirc >=310)
	{
		State = SHOOT;
		shootarc = true;
		bulletactive  = true;
	}
}else if (State == SHOOT)
{
	if(shootarc == true)
	{
		bullety = Ydirc;
		bulletx = Xdirc;
		shootarc = false;
	}
	if (bulletactive == true && visible2 == true)
	{
	Laser->Graphic->CopyTo(game->m_Screen,bulletx,bullety);
	bullety=bullety+3;
	}
	if(bullety >=SCRHEIGHT)
	{
		bulletactive = false;
	}

	// colision losing lives
	if (bullety <= Player.Ydir && bullety >= Player.Ydir - 10 && bulletx >= Player.Xdir && bulletx - 26 <= Player.Xdir && Player.alive == true)
	{
		Player.alive = false;
		Laser[20].active = false;
		printf("colision succes \n");
		Player.lives = Player.lives - 1;
	}

	if ( Ydirc >= SCRHEIGHT)
	{
		Ydirc = 0;
		State = GOBACK;
	}
	Xdirc ++;
	Ydirc ++;
}else if (State == GOBACK)
{
	Ydirc = Ydirc + (Walky - Ydirc)/50;
	Xdirc = Xdirc + (Walkx - Xdirc)/50;
	if (Ydirc >= Walky - 2 && Xdirc <= Walkx + 2 && Xdirc >= Walkx - 2)
	{
		State = MOVELEFTRIGHT;
	}
}
}

			//siny = (sin(-a)*(180.0/PI)) - Invaders[i].Ypos;
			//cosx = (cos(a)*(180.0/PI)) - Invaders[i].Xpos;