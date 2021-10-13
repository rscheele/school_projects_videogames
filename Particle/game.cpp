// Template, major revision 3
// IGAD/NHTV - Jacco Bikker - 2006-2009

#include "string.h"
#include "game.h"
#include "stdlib.h"
#include "template.h"
#include "sand.h"
#include "water.h"

using namespace Tmpl8;

int mouseX, mouseY;

void Game::Init()
{
	lmbup = false;
	rmbup = false;
	SpawnSand = false;
}

void Game::Tick( float a_DT )
{
	m_Screen->Clear( 0 );  
	char FPS[500];
	sprintf(FPS,"%f",1000/a_DT);
	m_Screen->Print(FPS,10,10,0xFF00FF);

	for (int i = 0; i < Particles.size(); i++)
	{
		Particles[i]->MoveMe(m_Screen,a_DT);
		Particles[i]->Draw(m_Screen);
	}

	if (lmbup)
		SpawnSand = true;
	if (!lmbup)
		SpawnSand = false;

	if(SpawnSand)
	{
		Particles.push_back(new Sand(mouseX,mouseY,0xE5C357 ));
		Particles.push_back(new Sand(mouseX+5,mouseY+3,0xE5C357 ));
		Particles.push_back(new Sand(mouseX-5,mouseY-3,0xE5C357 ));
	}

	if (rmbup)
		SpawnWater = true;
	if (!rmbup)
		SpawnWater = false;

	if(SpawnWater)
	{
		Particles.push_back(new Water(mouseX,mouseY,0x3BE8FF ));
		Particles.push_back(new Water(mouseX+5,mouseY+3,0x3BE8FF ));
		Particles.push_back(new Water(mouseX-5,mouseY-3,0x3BE8FF ));
	}

	m_Screen->Line(1,470,639,470,0xFFFFFF);

}

void Game::MouseMove( unsigned int x, unsigned int y )
{
	mouseX = x;
	mouseY = y;
}

void Game::MouseUp( unsigned int button )
{
	lmbup = false;
	rmbup = false;
}

void Game::MouseDown( unsigned int button )
{
	switch(button)
	{
	case 1:
		lmbup = true;
		break;
	case 3:
		rmbup = true;
		break;
	}
}