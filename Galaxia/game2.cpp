#include "string.h"
#include "surface.h"
#include "stdlib.h"
#include "template.h"
#include "game.h"
#include <ctime>

#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACE 57

bool keyleft = false;
bool keyright = false;
bool draw = true;
bool shoot = false;
int attack;
float delay = 578.154;
float arcdelay = 5784.55;

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

int TargetX = 0;
int TargetY = 200;
int TargetHDir = RIGHT;
int TargetVDir = DOWN;
int	Down = 0;

using namespace Tmpl8;
bool Visible = true;

Surface* Target = new Surface("assets/invader.tga");
Surface* Ship = new Surface("assets/turret.tga");
Surface* Pew = new Surface("assets/bullet.tga");
Surface* Enemybullet = new Surface("assets/bulletenemy.tga");
Surface* Superinvader = new Surface("assets/Commander.tga");

Invader Invaders[55];
Spaceship Player;
Ball Bullet;
EnemyBullet Laser[20];
CommanderEnemy Commander[3];

void Game::Init()
{
srand(time(0));
int counter = 0;

// drawing the player and rest
Player.Graphic = Ship;
Bullet.Graphic = Pew;
Player.Xdir = 300;
Player.Ydir = 450;
Commander[3].Graphic = Superinvader;

// drawing bullet
for (int l = 0; l < 20; l++)
{
	Laser[l].Graphic = Enemybullet;
	Laser[l].active = false;
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
	for (int i = 0; i <20 ; i++) // force a repeat of the clear screen to slow things down
		m_Screen->Clear( 0 ); 

	bool arcstart = true;
	float siny = 0;
	float cosx = 0;
	float a = 0;

	Invaders[i].Xpos=Commander[i].xplace;
	Invaders[i].Ypos=Commander[i].yplace;

	// arc movement attacking
	if (arcdelay < 17.35235)
	{
	arcstart = true;
		if (arcstart == true)
		{
			for (int i = 0; i < 1; i++)
			{
				if (arcstart == true)
				{
					siny = (sin(-a)*(180.0/PI)) - Commander[i].yplace;
					cosx = (cos(a)*(180.0/PI)) - Commander[i].xplace; 
					Commander[i].yplace = cosx;
					Commander[i].xplace = siny;
					a=a+0.1;
					if (a >= 18)
					{
						printf("i hit 180 \n");
						a = 0.0;
						arcstart = false;
					}
				}
			}
		}
	}

	if (delay >= 2.0)
	{
		delay = delay - a_DT;
	}

	if (arcdelay >= 3.0)
	{
		arcdelay = arcdelay - a_DT;
	}

	// making the player bullet colision with the enemy spaceships
	for (int i = 0; i < 55; ++i)
	{
		if (Bullet.Ymove < Invaders[i].Ypos && Bullet.Ymove > Invaders[i].Ypos - 16 && Bullet.Xmove > Invaders[i].Xpos && Bullet.Xmove < Invaders[i].Xpos + 22 && Bullet.flying == true)
		{
			if (Invaders[i].Visible == false)
			{
			Bullet.flying = true;
			}
			else
			{
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

//Updating bullets
for(int i = 0; i<20; i++)
{
	Laser[i].Tick(a_DT,this);
}

// drawing invaders
	for (int i = 0; i <55; i++)
	{
		if (Invaders[i].Visible == true)
		{
		Invaders[i].Graphic->CopyTo(m_Screen,Invaders[i].Xpos,Invaders[i].Ypos);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (Commander[i].alive == true)
		{
		Commander[i].Graphic->CopyTo(m_Screen,Commander[i].xplace,Commander[i].yplace);
		}
	}

	// drawning player
Player.Graphic->CopyTo(m_Screen,Player.Xdir,Player.Ydir);

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

	// important shit don't touch or you'll break it again
	for (int i = 0; i <55; i++)
	{
	 if (retval = Update(&Invaders[i],Down))
	 {
		 change = 1; //(or true)
	 }
	}


	if	(change == 1 && Down == 0)
	{
		Down = 0 ; // ok we hit the edge and there was no down flag so let him move down
	}
	else if (change == 1 && Down ==1)
	{
		Down = 0;
	}

	if	(change == 1 && Down == 0)
	{
		for		(int i  = 0; i <55; i++)
		{
		 if		(Invaders[i].Dir == LEFT) 
				Invaders[i].Dir = RIGHT;
		 else
			Invaders[i].Dir = LEFT;
		}
		change = 0;
		Down = 0; 
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
			if (Bullet.flying == false) 
			{
				Bullet.flying = true;
				Bullet.Xmove = Player.Xdir + 1;
				Bullet.Ymove = Player.Ydir;
			}

		}
	}

	// invadwers going left right
int Game::Update(Invader* Inv, int GoDown)
{
	int retval = 0;
	if	(Inv->Dir == LEFT)
	{
		Inv->Xpos --;
		if	(Inv->Xpos < 2) 
		{
			retval = 1;
		}
	}

	if	(Inv->Dir == RIGHT)
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

	if (delay < 11.3451)
    {

	if((int)Rand(987) <= 12)
	{
		CanIShoot = true;
	}
	// random shooting
		if(CanIShoot == true)
		{
			for(int i = 0; i< 20; i++)
			{
				if(Laser[i].active == false)
				{
					for (int l = 0; l < 55; l++)
					{
						if((int)Rand(100) <= 10 && Invaders[l].Visible == true)
						{
							Laser[i].XAttack = Invaders[l].Xpos;
							Laser[i].YAttack = Invaders[l].Ypos;
						}
					}
					Laser[i].active = true;
					delay = 745.26145;
					break;
				}
			}
		}
	}
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
	// colision 2 bullets
	if(XAttack + 12 >= Bullet.Xmove && XAttack - 12 <= Bullet.Xmove && YAttack + 12 >= Bullet.Ymove && XAttack - 12 <= Bullet.Ymove)
	{
		if(active == true && Bullet.flying == true)
		{
		active = false;
		Bullet.flying = false;
		}
	}
}