// Template, major revision 3
// IGAD/NHTV - Jacco Bikker - 2006-2009

#include "string.h"
#include "surface.h"
#include "stdlib.h"
#include "template.h"
#include "game.h"
#include "player.h"

using namespace Tmpl8;

Surface* playerImage = new Surface("assets/player.png");

Sprite playerSprite(playerImage,1);

void Game::Init()
{

}

void Game::Tick( float a_DT )
{
	m_Screen->Clear( 0 );  
	playerSprite.DrawRotated(50,50,m_Screen,1);
}