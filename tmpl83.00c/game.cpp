// Template, major revision 3
// IGAD/NHTV - Jacco Bikker - 2006-2009

#include "string.h"
#include "surface.h"
#include "stdlib.h"
#include "template.h"
#include "game.h"

using namespace Tmpl8;

Surface* Target = new Surface("assets/target.tga");

Invader Invaders[55];

void Game::Init()
{
	// put your initialization code here; will be executed once
int counter = 0;

for (int k = 0; k <5 ; k++)
{
	for (int i = 0; i <11 ; i++)
	{
		Invaders[counter].Graphic = Target;
		Invaders[counter].Ypos = 100+(k*32);
		Invaders[counter].Xpos = 32*i+64;
		Invaders[counter].Dir = RIGHT;
		counter++;
	}
}	
}

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3


int Xpos = 200;

int TargetX = 0;
int TargetY = 200;

int TargetHDir = RIGHT;
int TargetVDir = DOWN;
int	 Down = 0; // flag to indicate  do we want to move down

void Game::Tick( float a_DT )
{

	// render a single frame here

	for (int i = 0; i <20 ; i++) // force a repeat of the clear screen to slow things down
		m_Screen->Clear( 0 );  
	
	
	m_Screen->Print( "hello world hello pr1 class", Xpos, 2, 0xffffff );
int retval = 0;
int change = 0;


	for (int i = 0; i <55; i++)
	{

	 if (retval = Update(&Invaders[i],Down))
	 {
		 change = 1; //(or true)
	 }

		
	}


 // have we indicated a hit at the end which means next time we want to go down
	// down movment will always result in a change flag...

	if	(change == 1 && Down == 0)
	{
				Down = 1 ; // ok we hit the edge and there was no down flag so let him move down
	}
	else if (change == 1 && Down ==1)
	{
		Down = 0;
	}


	for (int i = 0; i <55; i++)
	{

		Invaders[i].Graphic->CopyTo(m_Screen,Invaders[i].Xpos,Invaders[i].Ypos);
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


int Game::Update(Invader* Inv, int GoDown)
{

	int retval = 0;


	if  (GoDown == 1)

	{ 	Inv->Ypos += 8;
		return 1 ; // force an early return to indicate a change has happened
	}
	


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

