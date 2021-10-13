#pragma once
#include "template.h"
#include "surface.h"
#include "FreeImage.h"

namespace Tmpl8
{
	class Tiles
	{
	public:
		Tiles(void);
		Tiles(Surface*tempTile,int x,int y);
		~Tiles(void);

		Surface* tile;
		int xPos;
		int yPos;
	private:
		
	};
}

