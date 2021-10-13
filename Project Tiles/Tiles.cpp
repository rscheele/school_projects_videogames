#include "Tiles.h"


using namespace Tmpl8;

Tiles::Tiles(void)
{
}

Tiles::Tiles(Surface* tempTile,int x,int y)
{
	tile = tempTile;
	xPos = x;
	yPos = y;
}

Tiles::~Tiles(void)
{
}


